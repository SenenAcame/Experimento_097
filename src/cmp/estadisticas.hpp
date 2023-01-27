#pragma once
#include <cstdint>

struct EstadisticaCmp {
     
    float hitpoints{}, damage{}, speed{};
    float  bulletRad{}; 
    

    static constexpr uint8_t id {6}; //0001000
};