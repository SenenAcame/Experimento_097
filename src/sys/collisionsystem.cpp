#include "collisionsystem.hpp"
//#include <iostream>

void CollisionSystem::update(EntityManager<Entity>& EM){
    auto bounce = [](Entity& e) {
        if(e.physics->x > 40.0 || e.physics->x < -40.0) {
            e.physics->x -= e.physics->vx; 
            e.physics->vx = -e.physics->vx;
        }
        if(e.physics->y > 100.0 || e.physics->y < 0.0) {
            e.physics->y -= e.physics->vy; 
            e.physics->vy = -e.physics->vy;
        }
        if(e.physics->z > 100.0 || e.physics->z < 0.0) {
            e.physics->z -= e.physics->vz; 
            e.physics->vz = -e.physics->vz;
        }
    };

    EM.forall(bounce);
}

void CollisionSystem::bounce(float& coor, float& vel){
    coor -= vel;
    vel = -vel;
}