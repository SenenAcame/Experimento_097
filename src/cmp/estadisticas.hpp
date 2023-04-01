#pragma once
#include <cstdint>

struct EstadisticaCmp {
    int hitpoints {}, damage {};
    float speed {};
    float bulletRad {}; 

    double attackSpeedEnemy { 1 };
    double ClockAttackEnemy { 1 };
   
    static constexpr uint8_t id { 6 }; //0001000
};