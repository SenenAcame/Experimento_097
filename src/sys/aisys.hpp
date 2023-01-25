#pragma once
#include "../util/types.hpp"
#include <numbers>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& a, PhysicsCmp2& p) {
                if(!a.enable) return;
                p.v_ang = p.v_lin = 0;

                auto vox   { a.ox - p.x };
                auto voz   { a.oz - p.z };
                auto volin { std::sqrt(vox*vox + voz*voz) };
                if(volin < p.kEpsil){
                    a.enable = false;
                    std::cout<<"He llegado\n";
                    return;
                }
                if(volin > p.kMxLin) volin = p.kMxLin;
                p.v_lin = volin;

                auto oorien = std::atan2(voz, vox);
                if      (oorien < 0) oorien += 2*std::numbers::pi;
                auto oang { oorien - p.orien };
                if      (oang >  std::numbers::pi) oang -= 2*std::numbers::pi;
                else if (oang < -std::numbers::pi) oang += 2*std::numbers::pi;
                p.v_ang = irr::core::clamp(oang, -p.kMxAng, p.kMxAng);
            }
        );
    }
};