#include "spawnsys.hpp"
#include "../eng/engine2.hpp"
#include "../man/levelman.hpp"

void SpawnSystem::update(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt) {
    auto& EM = LM.getEM();

    updateAliveEnem(EM);

    updateSpawnEnem(LM, GE, SouSys, dt);

    updateWave(LM, GE, SouSys, dt);    
}

void SpawnSystem::updateAliveEnem(EntyMan& EM) {
    auto&& bb = EM.getBoard();

    EM.foreach<VOICMPs, ENETAGs>(
        [&](Enty& enemy) {
            if(enemy.getDestroy()) {
                bb.wave.aliveEnem--;
                bb.wave.kills++;
            }
        }
    );
}

void SpawnSystem::updateSpawnEnem(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt) {
    auto& EM      = LM.getEM();
    auto& bb      = EM.getBoard();
    auto& wave    = bb.wave;
    auto& spw_wpn = bb.restart_weapons;

    Enty& player = EM.getEntityById(bb.entyID);
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

    spw_wpn.cooldwn += dt;

    if(spw_wpn.cooldwn >= spw_wpn.time)
        spawnWeapons(LM, GE, SouSys);
}

void SpawnSystem::updateWave(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt) {
    auto& bb      = LM.getEM().getBoard();
    auto& progres = bb.progres;
    auto& wave    = bb.wave;
    
    bool finished_wave { 
        progres.inRound         && 
        wave.total.reserve == 0 && 
        wave.aliveEnem     == 0 
    };

    if(finished_wave) {
        progres.inRound = false;
        LM.getEM().foreach<SoundCMP, SYSTAG_Ronda>(
            [&](Enty&, SoundCmp& voice){
                LM.getEM().changeSound(voice, 0);
            }
        );
    }

    else if(!progres.inRound) {
        //Tiempo entre oleadas
        progres.clockNextWave += dt;

        bool toNextWave = progres.clockNextWave >= progres.timeBtwWaves;

        if(toNextWave) { 
            nextWave(bb);
            spawnWeapons(LM, GE, SouSys);
        }
    }
}

CuantityEnemies SpawnSystem::refill(CuantityEnemies type) {
    type.num     += type.plus;
    type.reserve =  type.num;
    return type;
}

void SpawnSystem::aumentDifficult(BlackBoardCmp& black_b) {
    auto& stats = black_b.difficult;

    stats.life.extra += stats.life.aument_extra;
    stats.damg.extra += stats.damg.aument_extra;
    stats.sped.extra += stats.sped.aument_extra;
}

void SpawnSystem::spawnProcess(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, SpawnCmp& spawn, PhysicsCmp2& phy) {
    auto& bb   = LM.getEM().getBoard();
    auto& wave = bb.wave;
    
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

    LM.createEnemy(GE, Vec3{ phy.x, phy.y, phy.z }, SouSys, type, bb.difficult);
}

void SpawnSystem::nextWave(BlackBoardCmp& black_b) {
    auto& progres = black_b.progres;
    auto& wave        = black_b.wave;
    //Comienza siguiente oleada
    progres.clockNextWave = 0;
    progres.inRound       = true;
    progres.actualWave++;

    bool tankWave = progres.actualWave % progres.tanksBtwWaves == 0;
    bool distWave = progres.actualWave % progres.distsBtwWaves == 0;

    if(tankWave) wave.tank = refill(wave.tank);
    if(distWave) wave.disp = refill(wave.disp);
    wave.total = refill(wave.total);

    aumentDifficult(black_b);
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
    auto& EM = LM.getEM();
    auto& bb = EM.getBoard();

    Enty& player = EM.getEntityById(bb.entyID);
    auto& room_ply = EM.getComponent<SalaCmp>(player);

    W_Type weapons[] = {W_Type::Pistol, W_Type::Shotgun, W_Type::Fusil};
    std::vector<size_t> spawns;

    EM.foreach<SALCMPs, W_STAGs>(
        [&](Enty& spw, SalaCmp& room, SpawnCmp& spw_cmp) {
            if(room_ply.sala != room.sala)  
                spawns.push_back(spw.getID());
        }
    );

    for(int i = 0; i < 3; i++) {
        int pos = rand() % spawns.size();

        auto& spw = EM.getEntityById(spawns.at(pos));
        auto& phy = EM.getComponent<PhysicsCmp2>(spw);

        LM.createWeapon2(GE, { phy.x, 2.8, phy.z }, weapons[i], SouSys);
            
        spawns.erase(spawns.begin() + pos);
    }
    
    bb.restart_weapons.cooldwn = 0;
}