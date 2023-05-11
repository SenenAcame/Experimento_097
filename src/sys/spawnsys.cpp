#include "spawnsys.hpp"
#include "../eng/engine2.hpp"
#include "../man/levelman.hpp"

void SpawnSystem::update(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, std::size_t player_ID, std::size_t map_ID, double const dt) {
    auto& EM = LM.getEM();
    updateAliveEnem(EM);
    updateSpawnEnem(LM, GE, SouSys, dt);
}

void SpawnSystem::updateAliveEnem(EntyMan& EM) {
    EM.foreach<ENECMPs, ENETAGs>(
        [&](Enty& enemy) {
            if(enemy.getDestroy()) waves.aliveEnem--;
        }
    );
}

void SpawnSystem::updateSpawnEnem(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt) {
    auto& EM = LM.getEM();

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& entity, SpawnCmp& spawn, PhysicsCmp2& phy){
            spawn.clock += dt;
            bool posible_spawn {
                spawn.clock     >= spawn.timer && 
                waves.numEnem   >  0           && 
                waves.aliveEnem <  waves.maxEnem
            };
            
            if(posible_spawn) {
                spawn.clock = 0;
                waves.numEnem--;
                waves.aliveEnem++;
                LM.createNormalEnemy(GE, Vec3{ phy.x, 2.8, phy.z }, SouSys);
            }
        }
    );
}

void SpawnSystem::aumentDifficult() {
    difficult.life.extra += difficult.life.aument_extra;
    difficult.damg.extra += difficult.damg.aument_extra;
    difficult.sped.extra += difficult.sped.aument_extra;
}