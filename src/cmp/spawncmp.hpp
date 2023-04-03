#pragma once
#include <cstdint>

struct SpawnCmp {
    size_t numEnem = 1;

    size_t active = 0; //0 is not active 1 is active

    size_t sala = 0; //sala en el que esta

    double clockSpawn {0};
    double SpawnTimer {0.5};

    static constexpr uint8_t id {10}; //10000000000
};