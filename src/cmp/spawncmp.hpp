#pragma once
#include <cstdint>

struct SpawnCmp {
    std::size_t numEnem { 1 };
    std::size_t active  { 0 }; //0 is not active 1 is active
    std::size_t sala    { 0 }; //sala en el que esta

    static constexpr uint8_t id { 10 }; //10000000000
};