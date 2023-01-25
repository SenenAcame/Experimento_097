#pragma once
#include <cmath>
#include <cstdint>

struct PhysicsCmp2 {
    double  x{0},  y{0},  z{0};
    double vx{0}, vy{0}, vz{0};
    double v_lin {0};
    double v_ang {0};
    double orien {0};

    static constexpr double kMxLin {5.0};
    static constexpr double kMxAng {6 * M_PI};
    static constexpr double kEpsil {0.5};
    static constexpr uint8_t id {0};
};