#include "collisionsystem.hpp"
#include "physicsystem.hpp"
#include <iostream>

void CollisionSystem::update(EntityManager<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>>& EM){
    auto& phyCMP = EM.getPhysicsComponents();
    
    //auto lambda = [&](Entity& e) {};

    EM.forall(phyCMP);
}