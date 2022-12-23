#include "collisionsystem.hpp"
#include "physicsystem.hpp"
#include <iostream>

void CollisionSystem::update(EntityManager<Entity>& EM){
    auto& phyCMP = EM.getPhysicsComponents();

    EM.forall(phyCMP);
}