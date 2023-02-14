#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"

struct RenSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, RenderCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& GFX) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2 const& p, RenderCmp2& r){
                r.n->setPosition({static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z)});
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