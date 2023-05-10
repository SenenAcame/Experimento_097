#pragma once
#include <cstdint>

enum class W_Type {
    Pistol  = 0,
    Shotgun = 1,
    Fusil   = 2
};

struct Weapon {
    W_Type type {};
    int maxMagazine {};
    int magazine {}, ammo {};
    
    double reload_T {}, clock_R {};
    double cadence {};
};

struct InventarioCmp {
    static constexpr int numWeapons { 3 };

    int equipada { 0 };

    W_Type actual = W_Type::Pistol;
    //1 =  desbloqueada, 0 = no, 2 = arma actual
    std::size_t inventary [3] = { 1, 0, 2 }; //0 = pistola, 1 = escopeta, 2 = ametralladora
    
    Weapon gun {
        W_Type::Pistol,
        5,
        5,
        100,
        0.8,
        0.8,
        0
    };

    Weapon shot {
        W_Type::Shotgun,
        2,
        2,
        20,
        3,
        1.5,
        0
    };

    Weapon rifle {
        W_Type::Fusil,
        25,
        25,
        200,
        1.1,
        1.1,
        0.05
    };

    //weapon1
    int ammo1           { 100 };
    int magazine1       { 5 };
    double reloadTime1  { 0.8 };
    double clockReload1 { 0.8 };
    //double cadenceWeapon1{1}; // 1 vez por segundo
    
    //weapon2
    int ammo2           { 20 };
    int magazine2       { 2 };
    double reloadTime2  { 3 };
    double clockReload2 { 1.5 };
    //double cadenceWeapon2 {0.2}; //5 veces por segundo

    //weapon3
    int ammo3             { 200 };
    int magazine3         { 25 };
    double reloadTime3    { 1.1 };
    double clockReload3   { 1.1 };
    double cadenceWeapon3 { 0.05 }; 
    
    std::size_t reloading { 0 }; //0 not reloading 1 reloading
    double clockCadence   {};
    double clockReload    { 3 }; //always start to the hightes reload of weapon or the initial weapon

    static constexpr uint8_t id { 5 }; //0000100000
};