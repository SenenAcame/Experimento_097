#pragma once
#include "../util/types.hpp"
#include <iostream>

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2& p) {
                //if(e.hasTAG<TPlayer>()){
                //    auto& r = EM.getComponent<RenderCmp2>(e);
                //    p.x = r.n->getParent()->getPosition().X;
                //    p.y = r.n->getParent()->getPosition().Y;
                //    p.z = r.n->getParent()->getPosition().Z;
                //    std::cout<<p.x<<" "<<p.y<<" "<<p.z<<" "<<"\n";
                //}
                //else{
                    //std::cout<<"oe\n";
                    p.x += p.vx;
                    p.y += p.vy;
                    p.z += p.vz;
                //}
            }
        );
    }
};