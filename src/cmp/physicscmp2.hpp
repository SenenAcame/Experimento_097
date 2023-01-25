#pragma once
#include <cstdint>
#include <numbers>

struct PhysicsCmp2 {
    double  x{0},  y{0},  z{0};
    double vx{0}, vy{0}, vz{0};

    double orien {0};
    double v_lin {0};
    double v_ang {0};

    static constexpr double kMxLin {10.0};
    static constexpr double kMxAng {3 * std::numbers::pi};
    static constexpr double kEpsil {0.1};
    static constexpr uint8_t id {0};
};