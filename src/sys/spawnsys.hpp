#pragma once
#include "../util/types.hpp"
#include "soundsystem.hpp"

struct SpawnSystem {
    using SYSCMPs = MP::Typelist<SpawnCmp>;
    using SYSTAGs = MP::Typelist<TSpawn>;

    void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& ss) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty&, SpawnCmp& spw){
                if(spw.numEnem != 0) {
                    Enty& enem = EM.createEntity();
                    EM.addComponent<PhysicsCmp2>   (enem, PhysicsCmp2{ .x=-10.f, .z=20.f });
                    EM.addComponent<RenderCmp2>    (enem, eng.createModel("assets/models/enemy.obj","assets/textures/portal1.bmp"));
                    EM.addComponent<AICmp>         (enem, AICmp{ .arrivalRadius=5.0, .timeArrive=2.0, .behaviour=SB::Arrive, .cooldown=0.1 });
                    EM.addComponent<EstadisticaCmp>(enem, EstadisticaCmp{.hitpoints=100.f, .damage=10.f, .speed=2.f});
                    EM.addComponent<SoundCmp>      (enem, ss.createinstance(7));
                    EM.addComponent<EstadoCmp>     (enem); 
                    EM.addTag      <TEnemy>        (enem);
                    
                    spw.numEnem--;
                }
            }
        );
    }

};