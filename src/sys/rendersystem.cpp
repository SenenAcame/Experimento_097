#include "rendersystem.hpp"

void RenderSystem::update(EntityManager<Entity>& EM, TheEngine& GFX){
    EM.forall([](Entity& e) {
        auto& phy {e.physics};
        e.render.node->setPosition({phy->x, phy->y, phy->z});
    });
    GFX.beginScene();
    GFX.drawAll();
    GFX.endScene();
}