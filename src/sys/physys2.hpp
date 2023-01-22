#pragma once
#include "../util/types.hpp"

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<PhysicsCmp2>(
            [&](PhysicsCmp2& p) {
                p.x += p.vx;
                p.y += p.vy;
                p.z += p.vz;
            }
        );
    }
};