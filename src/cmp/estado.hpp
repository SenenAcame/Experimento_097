#pragma once
#include <cstdint>

struct EstadoCmp {
    float width  { 0 }; //anchura
    float height { 0 }; //altura
    float depth  { 0 }; //profundidad

    std::size_t colision  { 0 }; //he colisionado o no
    std::size_t entityCol { 0 }; //con que he colisionado

    bool        wall_collision {false};

    static constexpr uint8_t id {3}; //0000001000
};