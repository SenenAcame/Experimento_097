#pragma once
#include "../util/types.hpp"
#include "soundsystem.hpp"
#include <cstddef>

struct SpawnSystem {
    using SYSCMPs = MP::Typelist<SpawnCmp>;
    using SYSTAGs = MP::Typelist<TSpawn>;

    void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& ss, Enty& player, Enty& map) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& spwEnty, SpawnCmp& spwCMP){
                if(spwCMP.active == 1 && spwCMP.numEnem != 0 /*numEnemysPerRound >0*/) {
                    size_t type = 0;
                    //createEnemy(type, EM, eng, ss, spwCMP, spwEnty);
                   
                }
            }
        );
    }

    //void activeRespawn(Enty& player, Enty& spawn, Enty& map, EntyMan& EM){
//
    //    //Recoger la sala donde esta el jugador
    //    
//
    //    //Calcular los respawn más cercanos
//
    //    //Activarlos
//
    //}

    void createEnemy(size_t type, EntyMan& EM, TheEngine& eng, SoundSystem_t& ss, SpawnCmp& spwCMP, Enty& spwEnty){
        
        Enty& enem1 = EM.createEntity();
        switch (type) {
            
            case 0: 
            //create enemy normal
                
                //EM.addComponent<PhysicsCmp2>   (enem1, PhysicsCmp2{ .x=EM.getComponent<PhysicsCmp2>(spwEnty).x, .z=EM.getComponent<PhysicsCmp2>(spwEnty).z });
                //EM.addComponent<RenderCmp2>    (enem1, eng.createModel("assets/models/enemy.obj","assets/textures/portal1.bmp"));
                //EM.addComponent<AICmp>         (enem1, AICmp{ .arrivalRadius=5.0, .timeArrive=2.0, .behaviour=SB::Arrive, .cooldown=0.1 });
                //EM.addComponent<EstadisticaCmp>(enem1, EstadisticaCmp{.hitpoints=100.f, .damage=10.f, .speed=2.f});
                //EM.addComponent<SoundCmp>      (enem1, ss.createinstance(7));
                //EM.addComponent<EstadoCmp>     (enem1); 
                //EM.addTag      <TEnemy>        (enem1);
                
                
            break;

            case 1:
            break;

            default:
            break;
            
            spwCMP.numEnem--; //numEnemysPerRound
        
        }
        
    }

};

