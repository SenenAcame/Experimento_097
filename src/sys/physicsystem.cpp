
#include "physicsystem.hpp"
//#include "../eng/engine.hpp"

void PhysicsSystem::update(EntityManager<Entity>& EM){
    auto lambda = [](Entity& e) {
        e.physics->x += e.physics->vx;
        e.physics->y += e.physics->vy;
        e.physics->z += e.physics->vz;
       // if(e.tipo == 'p'){
       //     
       //     e.physics->x += e.physics->vx;
       //     
       //     e.physics->y += e.physics->vy;
       //     
       //     e.physics->z += e.physics->vz;
       //     
       // 
       //     
//
       //     //poner lo de addVector en otro lado
       //     
       // }
       // else{
       //     e.physics->x += e.physics->vx;
       //     e.physics->y += e.physics->vy;
       //     e.physics->z += e.physics->vz;
       // }
    };
    
    EM.forall(lambda);
}