#pragma once
#include "../man/levelman.hpp"

struct SoundSystem_t;

struct GameMan {
    void static game();
    void static init_config(GraphicEngine& GE);
    size_t static init_map(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys);
};