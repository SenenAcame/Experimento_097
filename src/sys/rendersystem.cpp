#include "rendersystem.hpp"

void RenderSystem::update(EntityManager<Entity>& EM, TheEngine& GFX){
    auto lambda = [](Entity& e) {
        //auto& phy {e.physics};
        //if(e.tipo=='p'){
        //    e.render->node->getParent()->setPosition({phy->x, phy->y, phy->z-10});
        //}
        //else{
        //    e.render->node->setPosition({e.render->node->getPosition().X,
        //    e.render->node->getPosition().Y, 
        //    e.render->node->getPosition().Z});
        ////}
    };
    
    EM.forall(lambda);
    
    GFX.beginScene();
    GFX.drawAll();
    GFX.endScene();
}