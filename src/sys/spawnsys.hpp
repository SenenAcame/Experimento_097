#pragma once
#include "../util/types.hpp"

struct SpawnSystem {
    using SYSCMPs = MP::Typelist<PhysicsCmp2,EstadoCmp>;
    using SYSTAGs = MP::Typelist<TSpawn>;

    void update(EntyMan& EM, TheEngine& dev, SoundSystem_t& SouSys) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2& p, EstadoCmp& est) {
                for(auto& a : EM.getEntities()){
                    if(est.numEnem >0){
                        //create enemy
                        Enty& enemy = EM.createEntity();
                        EM.addComponent<PhysicsCmp2>    (enemy, PhysicsCmp2{.x=p.x, .y=p.y, .z=p.z});
                        EM.addComponent<RenderCmp2>     (enemy, dev.createModel("assets/models/enemy.obj","assets/textures/faerie2.bmp"));
                        EM.addComponent<AICmp>          (enemy, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .cooldown=0.5 });
                        EM.addComponent<SoundCmp>       (enemy, SouSys.createinstance(7));
                        EM.addComponent<EstadisticaCmp> (enemy, EstadisticaCmp{.hitpoints=100.f, .damage=10.f, .speed=2.f});
                        EM.addComponent<EstadoCmp>      (enemy);
                        EM.addTag      <TEnemy>         (enemy);

                        est.numEnem--;   
                    }
                }
            }
        );
    }
};