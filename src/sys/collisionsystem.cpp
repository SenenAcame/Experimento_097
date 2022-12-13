#include "collisionsystem.hpp"
#include <iostream>

void CollisionSystem::update(EntityManager<Entity>& EM){
    auto& phyCMP = EM.getPhysicsComponents();

    for(auto& phy : phyCMP){
        for(auto& phy2 : phyCMP){
            //Obtener id de entidad a partir del componente para que
            //dependiendo del tipo de entidad haga una cosa u otra
            //phy.entityID;
            //phy2.entityID;
            if(phy.componentID!=phy2.componentID){
                if(phy.x < -50.0 || abs(phy.x - phy2.x) <= 1 || phy.x > 50.0){
                    if(/*phy.x < phy2.x*/(phy.vx>0 && phy2.vx>0) || (phy.vx<0 && phy2.vx<0)){
                        if(abs(phy.vx)>abs(phy2.vx)){
                            phy.x -= phy.vx;
                            phy.vx = -phy.vx;
                        }
                    }
                    else{
                        phy.x -= phy.vx;
                        phy.vx = -phy.vx;
                    }
                }

            }

        }
    }

//    auto bounce = [](Entity& e) {
//        if(e.physics->x > 40.0 || e.physics->x < -40.0) {
//            e.physics->x -= e.physics->vx; 
//            e.physics->vx = -e.physics->vx;
//        }
//        if(e.physics->y > 100.0 || e.physics->y < 0.0) {
//            e.physics->y -= e.physics->vy; 
//            e.physics->vy = -e.physics->vy;
//        }
//        if(e.physics->z > 100.0 || e.physics->z < 0.0) {
//            e.physics->z -= e.physics->vz; 
//            e.physics->vz = -e.physics->vz;
//        }
//    };
//
//    EM.forall(bounce);
}

void CollisionSystem::bounce(float& coor, float& vel){
    coor -= vel;
    vel = -vel;
}