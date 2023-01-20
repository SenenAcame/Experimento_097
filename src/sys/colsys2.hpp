#pragma once
#include "../util/types.hpp"

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2& p) {
                for(auto& a : EM.getStorage().getStorage<PhysicsCmp2>()) {
                    auto dx = p.x - a.x;
                    auto dy = p.y - a.y;
                    auto dz = p.z - a.z;
                    auto dist = std::sqrt(dx*dx+dy*dy+dz*dz);
                    if(dist <= 0.5 && dist!=0.0){
                        std::cout<<"Impacto\n";
                        //EM.destroyEntity(e);
                        //EM.removeComponent<RenderCmp2>(e);
                    }
                }
            }
        );
    }
};