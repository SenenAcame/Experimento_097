#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include <irrlicht/irrMath.h>

struct RenSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, RenderCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& GFX) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& ent, PhysicsCmp2 const& phy, RenderCmp2& rend){
                if(ent.hasTAG<TEnemy>()){
                    float giro = (-phy.orieny)*180/irr::core::PI+360;
                    rend.n->setRotation({0,giro,0});
                }
                rend.n->setPosition({static_cast<float>(phy.x), static_cast<float>(phy.y), static_cast<float>(phy.z)});
            }
        );
        drawAll(GFX);
    };

    void drawAll(TheEngine& GFX) {
        GFX.beginScene();
        GFX.drawAll();
        GFX.endScene();
    }
};