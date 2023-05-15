#include "spawnsys.hpp"
#include "../eng/engine2.hpp"
#include "../man/levelman.hpp"

void SpawnSystem::update(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, size_t player_ID, double const dt) {
    auto& EM = LM.getEM();

    updateAliveEnem(EM);

    updateSpawnEnem(LM, GE, SouSys, player_ID, dt);

    updateWave(LM, GE, SouSys, dt);    
}

void SpawnSystem::updateAliveEnem(EntyMan& EM) {
    EM.foreach<VOICMPs, ENETAGs>(
        [&](Enty& enemy) {
            if(enemy.getDestroy()) wave.aliveEnem--;
        }
    );
}

void SpawnSystem::updateSpawnEnem(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, size_t player_ID, double const dt) {
    auto& EM = LM.getEM();

    Enty& player = EM.getEntityById(player_ID);
    auto& room_ply = EM.getComponent<SalaCmp>(player);

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& entity, SpawnCmp& spawn, PhysicsCmp2& phy, SalaCmp& room) {
            spawn.clock += dt;

            bool posible_spawn {
                spawn.clock        >= spawn.timer    && 
                wave.total.reserve >  0              && 
                wave.aliveEnem     <  wave.maximEnem &&
                room_ply.sala      != room.sala
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
    deleteWeapons(LM, GE, SouSys);

    createWeapons(LM, GE, SouSys);
}

void SpawnSystem::deleteWeapons(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys) {
    auto& EM = LM.getEM();
    EM.foreach<VOICMPs, WPNTAGs>(
        [&](Enty& weapon) {
            weapon.setDestroy();
        }
    );
}

void SpawnSystem::createWeapons(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys) {
    int pos {};
    W_Type weapons[] = {W_Type::Pistol, W_Type::Shotgun, W_Type::Fusil};

    std::vector<Vec3> positions;
    //positions.push_back(Vec3 { -30,  2.8, -13 }); // Sala 0
    positions.push_back(Vec3 { -58,  2.8, -31 }); // Sala 3
    positions.push_back(Vec3 { -77,  2.8, 4   }); // Sala 6
    positions.push_back(Vec3 { -100, 2.8, -35 }); // Sala 11
    positions.push_back(Vec3 { -57,  2.8, -78 }); // Sala 13
    positions.push_back(Vec3 { -60,  2.8, 32  }); // Sala X (patio)

    for(int i = 0; i < 3; i++) {
        pos = rand() % positions.size();
        LM.createWeapon2(GE, positions.at(pos),weapons[i],  SouSys);
        positions.erase(positions.begin() + pos);
    }

    // MANUAL
    //LM.createWeapon2(GE, Vec3 { -30, 2.8, -13 }, W_Type::Pistol,  SouSys); // Sala 0
    //LM.createWeapon2(GE, Vec3 { -77, 2.8, 4   }, W_Type::Shotgun, SouSys); // Sala 6
    //LM.createWeapon2(GE, Vec3 { -58, 2.8, -31 }, W_Type::Fusil,   SouSys); // Sala 3
    // (-100, 2.8, -35) Sala 11
    // ( -57, 2.8, -78) Sala 13
    // ( -60, 2.8,  32) Sala X (patio)
}