#pragma once

struct Stat {
    float extra {}, aument_extra {};
};

struct ExtraStats {
    Stat life { 1.0f, 0.02f };
    Stat damg { 1.0f, 0.01f };
    Stat sped { 1.0f, 0.005f };
};

struct WaveInfo {
    int numBasicEnem  = 2;
    int aliveEnemys   = 0;
    int extraEnemys   = 1;
    int maxEnemysWave = 10; 
};