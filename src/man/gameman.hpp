#pragma once
#include "../man/levelman.hpp"

struct SoundSystem_t;
struct GameMan {
    void static game();
    void static init_config(TheEngine& dev);
    void static init_map(LevelMan& LM, TheEngine& dev, SoundSystem_t& SouSys);
    void static soundsEffects(EntyMan& EM, SoundSystem_t& SouSys);
};