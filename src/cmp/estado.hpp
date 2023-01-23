#pragma once
#include <cstdint>

struct EstadoCmp {
    
    size_t colision = 0; //0 no he colisionado 1 si 
    size_t entityCol = 0; //con que he colisio

    static constexpr uint8_t id {3};
};