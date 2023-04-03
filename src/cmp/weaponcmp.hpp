#pragma once
#include <cstddef>
#include <cstdint>

struct WeaponCmp {
   
    size_t typeWe      {}; 
    int ammo           {};
    int magazine       {};
    double reload      {};

    double Reload {0};

    size_t pickIt      =0; //0 = no pick ,1 = pick
    
    double clockForAmmo {0};
    double AmmoSpawn    {10};

    static constexpr uint8_t id {12}; 
};