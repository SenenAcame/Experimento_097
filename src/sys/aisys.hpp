#pragma once
#include "../util/types.hpp"

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& a, PhysicsCmp2& p) {
                //std::cout<<e.getID()<<"\n";
                auto dx = p.x - a.x;
                auto dy = p.y - a.y;
                auto dz = p.z - a.z;
                //std::cout<<dx<<" "<<dy<<" "<<dz<<" "<<"\n";
                auto dist = std::sqrt(dx*dx+dy*dy+dz*dz);
                std::cout<<dist<<"\n";
                p.vx = dx/dist;
                p.vy = dy/dist;
                p.vz = dz/dist;
                //std::cout<<p.vx<<" "<<p.vy<<" "<<p.vz<<" "<<"\n";
            }
        );
    }
};