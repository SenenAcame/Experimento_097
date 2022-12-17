#include "rendersystem.hpp"

void RenderSystem::update(EntityManager<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>>& EM, TheEngine& GFX){
    EM.forall([](Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>& e) {
        auto& phy {e.c1};
        e.c2->node->setPosition({phy->x, phy->y, phy->z});
    });
    GFX.beginScene();
    GFX.drawAll();
    GFX.endScene();
}