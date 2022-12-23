#include "rendersystem.hpp"

void RenderSystem::update(EntityManager<Entity>& EM, TheEngine& GFX){
    //auto lambda = [](Entity& e) {
    //    auto& phy {e.physics};
    //    
    //    const irr::core::vector3df& newpos = {phy->x, phy->y, phy->z};
//
    //    e.render->node->setPosition(newpos);
    //};
    //
    //EM.forall(lambda);
//  
    for(auto& e : EM.getEntities()){

        auto& phy {e.physics};

        const irr::core::vector3df newpos = {phy->x, phy->y, phy->z};

        auto& a = e.render;

        auto& b = a->node;
        //std::cout<<b->getParent()->getID()<<"\n";
        b->setPosition(newpos);
        //e.render->node->setPosition(newpos);
    }
    GFX.beginScene();
    GFX.drawAll();
    GFX.endScene();
}