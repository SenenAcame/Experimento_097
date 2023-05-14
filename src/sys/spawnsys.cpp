#include "spawnsys.hpp"
#include "../eng/engine2.hpp"
#include "../man/levelman.hpp"

void SpawnSystem::update(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, std::size_t player_ID, std::size_t map_ID, double const dt) {
    auto& EM = LM.getEM();

    updateAliveEnem(EM);

    updateSpawnEnem(LM, GE, SouSys, dt);

    updateWave(LM, GE, SouSys, dt);    
}

void SpawnSystem::updateAliveEnem(EntyMan& EM) {
    EM.foreach<VOICMPs, ENETAGs>(
        [&](Enty& enemy) {
            if(enemy.getDestroy()) wave.aliveEnem--;
        }
    );
}

void SpawnSystem::updateSpawnEnem(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt) {
    auto& EM = LM.getEM();

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& entity, SpawnCmp& spawn, PhysicsCmp2& phy) {
            spawn.clock += dt;
            bool posible_spawn {
                spawn.clock        >= spawn.timer && 
                wave.total.reserve >  0           && 
                wave.aliveEnem     <  wave.maximEnem
            };
            
            if(posible_spawn) spawnProcess(LM, GE, SouSys, spawn, phy);
        }
    );
}

void SpawnSystem::updateWave(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt) {
    bool finished_wave { 
        progres.inRound         && 
        wave.total.reserve == 0 && 
        wave.aliveEnem     == 0 
    };

    if(finished_wave) progres.inRound = false;

    else if(!progres.inRound) {
        //Tiempo entre oleadas
        progres.clockNextWave += dt;

        bool toNextWave = progres.clockNextWave >= progres.timeBtwWaves;

        if(toNextWave) { 
            nextWave();
            spawnWeapons(LM, GE, SouSys);
        }
    }
}

CuantityEnemies SpawnSystem::refill(CuantityEnemies type) {
    type.num     += type.plus;
    type.reserve =  type.num;
    return type;
}

void SpawnSystem::aumentDifficult() {
    difficult.life.extra += difficult.life.aument_extra;
    difficult.damg.extra += difficult.damg.aument_extra;
    difficult.sped.extra += difficult.sped.aument_extra;
}

void SpawnSystem::spawnProcess(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, SpawnCmp& spawn, PhysicsCmp2& phy) {
    Type_Enemy type = Type_Enemy::Normal;

    spawn.clock = 0;
    wave.total.reserve--;
    wave.aliveEnem++;

    if(wave.tank.reserve) {
        wave.tank.reserve--;
        type = Type_Enemy::Tank;
    }
    else if(wave.disp.reserve) {
        wave.disp.reserve--;
        type = Type_Enemy::Distance;
    }

    LM.createEnemy(GE, Vec3{ phy.x, phy.y, phy.z }, SouSys, type, difficult);
}

void SpawnSystem::nextWave() {
    //Comienza siguiente oleada
    progres.clockNextWave = 0;
    progres.inRound       = true;
    progres.actualWave++;

    bool tankWave = progres.actualWave % progres.tanksBtwWaves == 0;
    bool distWave = progres.actualWave % progres.distsBtwWaves == 0;

    if(tankWave) wave.tank = refill(wave.tank);
    if(distWave) wave.disp = refill(wave.disp);
    wave.total = refill(wave.total);

    aumentDifficult();
}

void SpawnSystem::spawnWeapons(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys) {
    auto& EM = LM.getEM();
    EM.foreach<VOICMPs, WPNTAGs>(
        [&](Enty& weapon) {
            weapon.setDestroy();
        }
    );
    LM.createWeapon2(GE, Vec3 { -30, 2.8, -13 }, W_Type::Pistol,  SouSys);
    LM.createWeapon2(GE, Vec3 { -77, 2.8, 4   }, W_Type::Shotgun, SouSys);
    LM.createWeapon2(GE, Vec3 { -58, 2.8, -31 }, W_Type::Fusil,   SouSys);
}