#pragma once
#include <cstdint>
#include <vector>

struct nodo {
        float  x{}, z{};
        float  tamx{}, tamz{};
        std::vector<nodo> nodos;
        nodo(){
            x=0;
            z=0;
            tamx=0;
            tamz=0;
        }
        nodo(float posx, float posz, float tamax, float tamaz){
            x=posx;
            z=posz;
            tamx=tamax;
            tamz=tamaz;
        };

};

struct NodoCmp {
    std::vector<nodo> nodos;

    static constexpr uint8_t id {5};
};