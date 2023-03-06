#pragma once
#include <cstddef>
#include <cstdint>

struct WeaponCmp {
   
    size_t typeWe      {}; 
    int ammo           {};
    int magazine       {};
    double reload      {};

    double Reload {0};

    static constexpr uint8_t id {12}; 
};