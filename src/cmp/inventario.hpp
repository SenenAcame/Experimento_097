#pragma once
#include <cstdint>

struct InventarioCmp {
    
    int equipada =-1;
    //1 =  desbloqueada, 0 = no, 2 = arma actual
    size_t inventary [3] = {2,1,0}; //1 = pistola, 2 = escopeta, 3 = ametralladora

    static constexpr uint8_t id {5}; //0000100
};