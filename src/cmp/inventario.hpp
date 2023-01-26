#pragma once
#include <cstdint>

struct InventarioCmp {
    
    //1 =  desbloqueada, 0 = no, 2 = arma actual
    size_t inventary [3] = {2,0,0}; //1 = pistola, 2 = ametralladora, 3 = escopeta

    static constexpr uint8_t id {5}; //0000100
};