#pragma once
#include "../util/types.hpp"

struct PhySys2 {
    void update(EntyMan& EM) {
        auto lambda = [&](Enty& e) {
            auto& p = EM.getComponent<PhysicsCmp2>(e);
            p.x += p.vx;
            p.y += p.vy;
            p.z += p.vz;
        };
        EM.forall(lambda);
    }
};