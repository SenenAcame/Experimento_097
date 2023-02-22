#pragma once
#include <cstdint>

struct EstadoCmp {
    float width  { 0 }; //anchura
    float height { 0 }; //altura
    float depth  { 0 }; //profundidad

    std::size_t colision  { 0 }; //0 no he colisionado 1 
    std::size_t entityCol { 0 }; //con que he colisio

    static constexpr uint8_t id {3}; //0000001000
};