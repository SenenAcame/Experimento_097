#pragma once
#include <cstdint>

enum class W_Type {
    Pistol  = 0,
    Shotgun = 1,
    Fusil   = 2
};

struct Weapon {
    W_Type type {};
    int maxMagazine {}, maxAmmo {};
    int magazine {}, ammo {};
    
    double reload_T {}, clock_R {};
    double cadence  {}, recoil  {};
};

struct InventarioCmp {
    static constexpr int numWeapons { 3 };

    int equipada { 0 }; //0 = pistola, 1 = escopeta, 2 = ametralladora
    W_Type actual = W_Type::Pistol;
    std::size_t inventary [3] = { 2, 0, 0 }; //1 = desbloqueada, 0 = no, 2 = arma actual
    
    Weapon gun {
        W_Type::Pistol,
        5,
        100,
        5,
        100,
        0.8,
        0.8,
        0,
        1.
    };

    Weapon shot {
        W_Type::Shotgun,
        2,
        20,
        2,
        20,
        1.5,
        1.5,
        0,
        5.
    };

    Weapon rifle {
        W_Type::Fusil,
        25,
        200,
        25,
        200,
        1.1,
        1.1,
        0.05,
        1.
    };
    
    std::size_t reloading { 0 }; //0 not reloading 1 reloading
    double clockCadence   {};
    double clockReload    { 3 }; //always start to the hightes reload of weapon or the initial weapon

    static constexpr uint8_t id { 5 }; //0000100000
};