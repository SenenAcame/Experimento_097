#include "physicsystem.hpp"

void PhysicsSystem::update(EntityManager<Entity>& EM){
    auto lambda = [](Entity& e) {
        e.physics->x += e.physics->vx;
        e.physics->y += e.physics->vy;
        e.physics->z += e.physics->vz;
        //if(e.tipo == 'p'){
        //    irr::core::vector3df PlayerPos = e.render->node->getAbsolutePosition();
        //    e.physics->x += e.physics->vx;
        //    PlayerPos.X =e.physics->x;
        //    e.physics->y += e.physics->vy;
        //    PlayerPos.Y =e.physics->y;
        //    e.physics->z += e.physics->vz;
        //    PlayerPos.Z =e.physics->z;
        //
        //    e.render->node->setPosition(PlayerPos);
        //}
        //else{
        //    e.physics->x += e.physics->vx;
        //    e.physics->y += e.physics->vy;
        //    e.physics->z += e.physics->vz;
        //}
    };
    
    EM.forall(lambda);
}