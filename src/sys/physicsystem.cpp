#include "physicsystem.hpp"

void PhysicsSystem::update(EntityManager<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>>& EM){
    EM.forall([](Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>& e) {
        e.c1->x += e.c1->vx;
        e.c1->y += e.c1->vy;
        e.c1->z += e.c1->vz;
    });
}