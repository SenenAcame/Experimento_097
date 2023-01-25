#pragma once
#include "../util/types.hpp"
#include <cmath>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& a, PhysicsCmp2& p) {
                if(!a.enable) return;

                p.v_ang = p.v_lin = 0;

                auto vox   { a.ox - p.x };
                auto voy   { a.oy - p.y };
                auto voz   { a.oz - p.z };
                auto volin { std::sqrt(vox*vox + voy*voy + voz*voz) };

                //std::cout<<volin<<"\n";
                
                if(volin < p.kEpsil){
                    a.enable = false;
                    return;
                }

                p.v_lin = irr::core::clamp(volin, -p.kMxLin, p.kMxLin);

                auto oorien = std::atan2(voz, vox);
                if( oorien < 0) oorien += 2*M_PI;

                auto oang { oorien - p.orien };
                p.v_ang = irr::core::clamp(oang, -p.kMxAng, p.kMxAng);
            }
        );
    }
};