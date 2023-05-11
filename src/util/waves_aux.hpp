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
    int actualWave = 1;
    int numEnem    = 20;
    int aliveEnem  = 0;
    int maxEnem    = 10; 
    //int extraEnemys  = 1;
};