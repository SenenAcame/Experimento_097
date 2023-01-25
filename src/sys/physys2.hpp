#pragma once
#include "../util/types.hpp"
#include <cmath>
#include <numbers>
//#include <iostream>

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    constexpr static double dt = 1.0/60;
    static constexpr double PI { std::numbers::pi };

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2& p) {
                if(e.hasTAG<TBullet>()){
                    p.x += p.vx;
                    p.y += p.vy;
                    p.z += p.vz;
                }
                else{
                    p.orien += dt * p.v_ang;
                    if      (p.orien > 2*PI) p.orien -= 2*PI;
                    else if (p.orien < 0)    p.orien += 2*PI;

                    p.vx =  p.v_lin * std::cos(p.orien);
                    p.vz =  p.v_lin * std::sin(p.orien);

                    p.x += dt * p.vx;
                    p.z += dt * p.vz;
                }
            }
        );
    }
};