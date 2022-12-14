#include "physicsystem.hpp"
#include <cmath>

void PhysicsSystem::update(EntityManager<Entity>& EM){
    auto lambda = [](Entity& e) {
        e.physics->x += e.physics->vx;
        e.physics->y += e.physics->vy;
        e.physics->z += e.physics->vz;
    };
    
    EM.forall(lambda);
}