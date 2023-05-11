#include "spawnsys.hpp"
#include "../eng/engine2.hpp"
#include "../man/levelman.hpp"

void SpawnSystem::update(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, std::size_t player_ID, std::size_t map_ID, double const dt) {
    auto& EM = LM.getEM();

    updateAliveEnem(EM);

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

void SpawnSystem::updateAliveEnem(EntyMan& EM) {
    EM.foreach<ENECMPs, ENETAGs>(
        [&](Enty& enemy) {
            if(enemy.getDestroy()) waves.aliveEnem--;
        }
    );
}

void SpawnSystem::aumentDifficult() {
    difficult.life.extra += difficult.life.aument_extra;
    difficult.damg.extra += difficult.damg.aument_extra;
    difficult.sped.extra += difficult.sped.aument_extra;
}

//void SpawnSystem::activeRespawn(Enty& player, Enty& spawn, Enty& map, EntyMan& EM){
//
//    //Recoger la sala donde esta el jugador
//
//    //Calcular los respawn más cercanos
//
//    //Activarlos
//
//}

//void SpawnSystem::createEnemy(size_t type, EntyMan& EM, TheEngine& eng, SoundSystem_t& ss, SpawnCmp& spwCMP, Enty& spwEnty){
//    //Enty& enem1 = EM.createEntity();
//    switch(type) {
//        case 0: 
//        //create enemy normal
//            //EM.addComponent<PhysicsCmp2>   (enem1, PhysicsCmp2{ .x=EM.getComponent<PhysicsCmp2>(spwEnty).x, .z=EM.getComponent<PhysicsCmp2>(spwEnty).z });
//            //EM.addComponent<RenderCmp2>    (enem1, eng.createModel("assets/models/enemy.obj","assets/textures/portal1.bmp"));
//            //EM.addComponent<AICmp>         (enem1, AICmp{ .arrivalRadius=5.0, .timeArrive=2.0, .behaviour=SB::Arrive, .cooldown=0.1 });
//            //EM.addComponent<EstadisticaCmp>(enem1, EstadisticaCmp{.hitpoints=100.f, .damage=10.f, .speed=2.f});
//            //EM.addComponent<SoundCmp>      (enem1, ss.createinstance(7));
//            //EM.addComponent<EstadoCmp>     (enem1); 
//            //EM.addTag      <TEnemy>        (enem1);
//        break;
//
//        case 1:
//        break;
//
//        default: break;
//    }
//    spwCMP.numEnem--; //numEnemysPerRound
//}