#pragma once
#include <cstdint>
#include <vector>

struct puerta{
    float x{}, z{};
};
struct sala {
    float  x{}, z{};
    float  tamx{}, tamz{};
    std::vector<puerta> puertas;
};

struct NodoCmp {
    std::vector<sala> salas;

    static constexpr uint8_t id {8};
};