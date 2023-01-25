#pragma once
#include "../util/types.hpp"
#include <cmath>
//#include <iostream>

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    constexpr static double factor = 1.0/60;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty&, PhysicsCmp2& p) {

                p.orien += factor * p.v_ang;

                if(p.orien > 2*M_PI) p.orien -= 2*M_PI;
                if(p.orien < 0)      p.orien += 2*M_PI;

                p.vx =  p.v_lin * std::sin(p.orien);
                p.vz =  p.v_lin * std::cos(p.orien);

                p.x += factor * p.vx;
                p.y += factor * p.vy;
                p.z += factor * p.vz;
            }
        );
    }
};