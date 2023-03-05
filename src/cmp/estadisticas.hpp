#pragma once
#include <cstdint>

struct EstadisticaCmp {
    float hitpoints{}, damage{}, speed{};
    float bulletRad{}; 

    double attackSpeedEnemy{1};
    double ClockAttackEnemy{1};
   
    static constexpr uint8_t id {6}; //0001000
};