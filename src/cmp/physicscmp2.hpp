#pragma once
#include <cstdint>

struct PhysicsCmp2 {
    float  x{},  y{},  z{};
    float vx{}, vy{}, vz{};

    static constexpr uint8_t id {0}; //00000001
};