#pragma once
#include <cstdint>

struct InventarioCmp {
    
    int equipada =0;
    //1 =  desbloqueada, 0 = no, 2 = arma actual
    size_t inventary [3] = {2,1,0}; //1 = pistola, 2 = escopeta, 3 = ametralladora
    
    //weapon1
    int ammo1 = 20;
    int magazine1=5;
    double cadenceWeapon1{1}; // 1 vez por segundo
    

    //weapon2
    int ammo2 = 10;
    int magazine2=2;
    double cadenceWeapon2 {0.2}; //5 veces por segundo

    //weapon3
    int ammo3 = 200;
    int magazine3=25;
    double cadenceWeapon3 {0.4}; //5 veces por segundo
    

    double clockCadence{};

    static constexpr uint8_t id {5}; //0000100000
};