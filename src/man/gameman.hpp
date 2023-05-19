#pragma once
#include "../man/levelman.hpp"
#include <cstddef>

struct SoundSystem_t;
struct RenSys2;
struct InpSys2;
struct UIsys;


struct GameMan {

    void static game();
    void static init_config(GraphicEngine& GE);
    size_t static init_map(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys);
    size_t static bucleInicio(RenSys2 &RenSys, GraphicEngine &GE, UIsys &UISys);
    size_t static bucleJuego(LevelMan& LM, GraphicEngine& GE, RenSys2& RenSys, InpSys2& InpSys, SoundSystem_t& SouSys, size_t abandon, std::size_t player_ID, UIsys &UISys);
    size_t static bucleDead(GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys);
    size_t static bucleControles(GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys);
    size_t static bucleSonido(GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys, SoundSystem_t& SouSys);
   // bool static loop_game(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys, bool abandon);
   // bool static dead(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys, bool abandon);
   // 
   // void static controls(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys);
};