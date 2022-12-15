#include "rendersystem.hpp"

void RenderSystem::update(EntityManager<Entity>& EM, TheEngine& GFX){
    auto lambda = [](Entity& e) {
        auto& phy {e.physics};
        e.render->node->setPosition({phy->x, phy->y, phy->z});
    };
    
    EM.forall(lambda);

    GFX.beginScene();
    GFX.drawAll();
    GFX.endScene();
}