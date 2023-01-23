#pragma once
#include <cstdint>

struct EstadoCmp {
    //inicializa a 00000000, colision es bit 00000001
    size_t colision = 0; //0 no he colisionado 1 
    size_t entityCol = 0; //con que he colisio

    static constexpr uint8_t id {3}; //0000100
};