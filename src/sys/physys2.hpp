#pragma once
#include "../util/types.hpp"
#include <cmath>
#include <numbers>

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr double PI { std::numbers::pi };

    void update(EntyMan& EM, double dt) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& en, PhysicsCmp2& p) {
                if(en.hasTAG<TPlayer>() || en.hasTAG<TEnemy>() || en.hasTAG<TDistEnemy>()) {
                    if(en.hasCMP<AICmp>() && EM.getComponent<AICmp>(en).behaviour==SB::Shoot){}
                    p.orieny += dt * p.v_ang;
                    if      (p.orieny > 2*PI) p.orieny -= 2*PI;
                    else if (p.orieny < 0)    p.orieny += 2*PI;

                    if(en.hasTAG<TPlayer>()){
                        p.vx =  p.v_lin * std::sin(p.orieny);
                        p.vz =  p.v_lin * std::cos(p.orieny);
                    }
                    else{
                        p.vx =  p.v_lin * std::cos(p.orieny);
                        p.vz =  p.v_lin * std::sin(p.orieny);
                    }

                    p.x += dt * p.vx;
                    p.z += dt * p.vz;

                    p.v_lin += dt * p.a_lin;
                    p.v_ang += dt * p.a_ang;
                    p.v_lin = irr::core::clamp(p.v_lin, -p.kMxVLin, p.kMxVLin);
                    p.v_ang = irr::core::clamp(p.v_ang, -p.kMxVAng, p.z);

                    auto roz = dt * std::fabs(p.v_lin) * (p.kRoz);
                    if(p.v_lin > 0) p.v_lin -= roz;
                    else            p.v_lin += roz;
                }
                if(!en.hasTAG<TEnemy>() && !en.hasTAG<TDistEnemy>()){
                    p.x += p.vx;
                    p.y += p.vy;
                    p.z += p.vz;
                }
            }
        );
    }
};