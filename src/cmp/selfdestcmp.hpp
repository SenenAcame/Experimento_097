#pragma once
#include <cstdint>

struct SelfDestCmp {
    double cooldown      { 1.0 };
    double time          { 0.0 };

    static constexpr uint8_t id     {9}; //00000001
};