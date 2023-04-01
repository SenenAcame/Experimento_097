#pragma once
#include "../eng/engine.hpp"
#include "../man/levelman.hpp"

struct SoundSystem_t;
struct GameMan {
    void game();
    void init_config(TheEngine& dev);
    void init_map(LevelMan& LM, TheEngine& dev, SoundSystem_t& SouSys);
};