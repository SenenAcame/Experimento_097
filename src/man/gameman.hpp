#pragma once
#include "../man/levelman.hpp"

struct SoundSystem_t;
struct RenSys2;
struct InpSys2;

struct GameMan {
    void static game();
    void static initial_menu(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys);
    bool static loop_game(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys, bool abandon);
    bool static dead(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys, bool abandon);
    
    void static controls(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys);
    void static init_config(TheEngine& dev);
    void static init_map(LevelMan& LM, TheEngine& dev, SoundSystem_t& SouSys);
};