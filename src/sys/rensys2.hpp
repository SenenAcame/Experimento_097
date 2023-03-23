#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include <irrlicht/aabbox3d.h>
#include <irrlicht/irrMath.h>

struct RenSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, RenderCmp2>;
    using BOXCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& GFX) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& ent, PhysicsCmp2 const& phy, RenderCmp2& rend){
                if(ent.hasTAG<TEnemy>()){
                    float giro = (-phy.orieny)*180/irr::core::PI+360;
                    rend.n->setRotation({rend.n->getRotation().X,giro,rend.n->getRotation().Z});
                }
                //if(ent.hasCMP<EstadoCmp>()){
                //    auto& state = EM.getComponent<EstadoCmp>(ent);
                //    auto vd = GFX.getDevice()->getVideoDriver();
                //    irr::core::aabbox3df box = {
                //        {phy.x-state.width, phy.y-state.height, phy.z-state.depth}, 
                //        {phy.x+state.width, phy.y+state.height, phy.z+state.depth}
                //    };
                //    vd->draw3DBox(box);
                //}
                rend.n->setPosition({static_cast<float>(phy.x), static_cast<float>(phy.y), static_cast<float>(phy.z)});
            }
        );
        GFX.beginScene();
        GFX.drawAll();
        drawBBox(EM, GFX);
        GFX.endScene();
    };

    void drawAll(TheEngine& GFX) {
        GFX.beginScene();
        GFX.drawAll();
        GFX.endScene();
    }

    void drawBBox(EntyMan& EM, TheEngine& GFX) {
        auto vd = GFX.getDevice()->getVideoDriver();
        vd->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
        EM.foreach<BOXCMPs, SYSTAGs>(
            [&](Enty& ent, PhysicsCmp2 const& phy, EstadoCmp const& state){
                vd->draw3DBox({
                    { (float)phy.x-state.width, (float)phy.y-state.height, (float)phy.z-state.depth }, 
                    { (float)phy.x+state.width, (float)phy.y+state.height, (float)phy.z+state.depth }
                });
            }
        );
    }
};