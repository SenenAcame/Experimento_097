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
    Stat life { .98f, 0.02f };
    Stat damg { .99f, 0.01f };
    Stat sped { .995f, 0.005f };
    //Stat cd   { 1.0f, 0.f };
    //Stat shot { 1.0f, 0.f };
};

struct WaveInfo {
    int maximEnem { 7 }; //maximos vivos en total
    int aliveEnem { 0 }; //numero vivos en total 

    CuantityEnemies total { 1, 0, 1};
    CuantityEnemies tank  { 0, 0, 1};
    CuantityEnemies disp  { 0, 0, 1};
};

struct WavesProgres {
    int    actualWave    { 0 };

    int    tanksBtwWaves { 3 };
    int    distsBtwWaves { 4 };

    double clockNextWave { 0 };
    double timeBtwWaves  { 3 };
    
    bool   inRound       { false };
};