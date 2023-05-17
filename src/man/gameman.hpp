#pragma once
#include "../man/levelman.hpp"

struct SoundSystem_t;
struct RenSys2;
struct InpSys2;
struct UIsys;


struct GameMan {
    void static game();
    void static init_config(TheEngine& dev);
    void static init_map(LevelMan& LM, TheEngine& dev, SoundSystem_t& SouSys);

    //for menus
    void static bucleInicio(RenSys2 &RenSys, GraphicEngine &GE, UIsys &UISys);
    bool static bucleJuego(LevelMan& LM, GraphicEngine& GE, RenSys2& RenSys, InpSys2& InpSys, SoundSystem_t& SouSys, bool abandon, std::size_t player_ID, UIsys &UISys);
    bool static bucleDead(LevelMan& LM, GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys);
   // bool static loop_game(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys, bool abandon);
   // bool static dead(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys, bool abandon);
   // 
   // void static controls(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys);
};