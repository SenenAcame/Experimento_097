#pragma once

struct Stat {
    float extra {}, aument_extra {};
};

struct ExtraStats {
    Stat life { 1.0f, 0.02f };
    Stat damg { 1.0f, 0.01f };
    Stat sped { 1.0f, 0.005f };
    //Stat cd { 1.0f, 0.f };
    //Stat shot { 1.0f, 0.f };
};

struct WaveInfo {
    int resrvEnem = 5;
    int aliveEnem = 0;
    int maximEnem = 10;
    //int numBasi = 0;
    //int numTank = 0;
    //int numDist = 0;
};

struct WavesProgression {
    int actualWave = 1;

    double clockNextWave = 0;
    double timeBtwWaves  = 4;

    bool inRound = false;
};