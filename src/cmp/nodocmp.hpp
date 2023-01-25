#pragma once
#include <cstdint>
#include <vector>

struct nodo {
        float  x{}, z{};
        float  tamx{}, tamz{};
        std::vector<nodo> nodos;
};

struct NodoCmp {
    std::vector<nodo> nodos;

    static constexpr uint8_t id {5};
};