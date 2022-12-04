#include "physicsystem.hpp"

void PhysicsSystem::update(EntityManager<Entity>& EM){
    EM.forall([](Entity& e) {
        e.physics->x += e.physics->vx;
        e.physics->y += e.physics->vy;
        e.physics->z += e.physics->vz;
    });
}