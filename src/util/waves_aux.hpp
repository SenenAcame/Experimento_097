#pragma once

struct Clock {
    double cooldwn {}, time {};
};

enum class Type_Enemy{
    Normal,
    Tank,
    Distance
};

struct CuantityEnemies {
    int num {}, reserve {}, plus {};
};

struct Stat {
    float extra {}, aument_extra {};
};

struct ExtraStats {
    Stat life { .95f, 0.15f };
    Stat damg { .98f, 0.02f };
    Stat sped { .99f, 0.06f };
};

struct WaveInfo {
    int kills     { 0 };
    int maximEnem { 12 }; //maximos vivos en total
    int aliveEnem { 0 }; //numero vivos en total 

    CuantityEnemies total { 4, 0, 1};
    CuantityEnemies tank  { 0, 0, 1};
    CuantityEnemies disp  { 0, 0, 2};
};

struct WavesProgres {
    int    actualWave    { 0 };

    int    tanksBtwWaves { 2 };
    int    distsBtwWaves { 3 };

    double clockNextWave { 0 };
    double timeBtwWaves  { 3 };

    int powerDamage       {0};
    int powerSpeed        {0};
    
    bool   inRound       { false };
};