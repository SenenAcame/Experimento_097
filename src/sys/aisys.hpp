#pragma once
#include "../util/types.hpp"
#include <irrlicht/irrMath.h>
#include <numbers>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    constexpr void arrive(AICmp& a, PhysicsCmp2& p) const noexcept{
        p.v_ang = p.a_lin = 0;

        auto vox   { a.ox - p.x };
        auto voz   { a.oz - p.z };
        auto odist { std::sqrt(vox*vox + voz*voz) };
        if(odist < a.arrivalRadius){
            a.enable = false;
            //std::cout<<"He llegado "<<e.getID()<<"\n";
            return;
        }
        auto ovel { irr::core::clamp(odist/a.timeArrive, -p.kMxVLin, p.kMxVLin) };
        p.a_lin = irr::core::clamp((ovel - p.v_lin)/a.timeArrive, -p.kMxALin, p.kMxALin);

        auto oorien = std::atan2(voz, vox);
        if      (oorien < 0) oorien += 2*std::numbers::pi;
        auto oang { oorien - p.orien };
        if      (oang >  std::numbers::pi) oang -= 2*std::numbers::pi;
        else if (oang < -std::numbers::pi) oang += 2*std::numbers::pi;
        p.v_ang = irr::core::clamp(oang/a.timeArrive, -p.kMxVAng, p.kMxVAng);
    }

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& a, PhysicsCmp2& p) {
                if(!a.enable) return;
                switch(a.behaviour){
                    case SB::Arrive: arrive(a,p); break;
                    case SB::Seek:   arrive(a,p); break;
                }
            }
        );
    }
};