#pragma once
#include <cstdint>

struct WeaponCmp {
   
    std::size_t typeWe      {}; 
    int ammo           {};
    int magazine       {};
    double reload      {};

    double Reload {0};

    std::size_t pickIt      =0; //0 = no pick ,1 = pick
    
    double clockForAmmo {0};
    double AmmoSpawn    {10};

    static constexpr uint8_t id {12}; 
};