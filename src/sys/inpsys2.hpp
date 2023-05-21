#pragma once
#include "../util/types.hpp"
#include "../util/keyboard.hpp"
#include "../util/mouse.hpp"
#include "UIsys.hpp"
#include "../util/munition_aux.hpp"
#include <GLFW/glfw3.h>
#include <cstddef>

struct LevelMan;
struct SoundSystem_t;
struct GraphicEngine;
struct GLFWwindow;

struct InpSys2 {
    //using EXACMPs = MP::Typelist<InputCmp2, PhysicsCmp2>;
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2, PhysicsCmp2, InventarioCmp, EstadisticaCmp>;
    using SYSTAGs = MP::Typelist<>;

    using SOUNDCMP = MP::Typelist<SoundCmp>;
    //using SYSTAG_Weapon = MP::Typelist<TWeapon>;

    /*NUEVO*/ void update2(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt, UIsys& UI);
    /*NUEVO*/ bool checkKeyboard(GLFWwindow* window);
    /*NUEVO*/ void checkPressed(int k, int GL_k, int actual);
    /*NUEVO*/ void    static changeWeapon2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, RenderCmp2& rend, size_t equip);
    /*NUEVO*/ void    static changeWeaponMethod(GraphicEngine& GE, InventarioCmp& invent, size_t new_, size_t old_);
    /*NUEVO*/ Mag_Amm static changeWeaponProcess(GraphicEngine& GE, InventarioCmp& invent, std::string file, Weapon& wpn);

private:
    /*NUEVO*/ int  previousKeyStatus  (int k, int actual, int prev, int lock);
    /*NUEVO*/ int  previousMouseStatus(int k, int actual, int prev, int lock);
    /*NUEVO*/ void updateStateWeapon(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, double const dt);
    /*NUEVO*/ void reload2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent);
    /*NUEVO*/ void reloadProcess2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, Weapon& wpn);
    /*NUEVO*/ void shoot2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, PhysicsCmp2& phy, SoundSystem_t& SouSys);
    /*NUEVO*/ Mag_Tim_Cad valuesWeapon(Weapon& wpn);
    /*NUEVO*/ void createBullet2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, PhysicsCmp2& phy, SoundSystem_t& SouSys, double cadenciaWeapon);
    
    void bulletProcess(LevelMan& LM, GraphicEngine& GE, ECamera* cam, Weapon& wpn, 
        PhysicsCmp2& phy, SoundSystem_t& SouSys, double extra, bool is_shot = false, int lock = 0);

    void recoil(EntyMan& EM, GraphicEngine& GE, ECamera* cam, double desv);
    void digonalMove(PhysicsCmp2& phy, float const speed, bool const up, bool const down);
    void soundWeapon(EntyMan& EM);
    static void onkeypressed(KeySym k)  { keyboard.keyPressed(k);  }
    static void onkeyreleased(KeySym k) { keyboard.keyReleased(k); }

    inline static Keyboard keyboard {};
    inline static Mouse mouse {};

    int prev_Left { GLFW_RELEASE }, lock_Left { 0 };

    int prev_Esc { GLFW_RELEASE }, lock_Esc { 0 };
    int prev_W { GLFW_RELEASE }, lock_W { 1 };
    int prev_S { GLFW_RELEASE }, lock_S { 1 };
    int prev_A { GLFW_RELEASE }, lock_A { 1 };
    int prev_D { GLFW_RELEASE }, lock_D { 1 };
    int prev_R { GLFW_RELEASE }, lock_R { 0 };
    int prev_1 { GLFW_RELEASE }, lock_1 { 0 };
    int prev_2 { GLFW_RELEASE }, lock_2 { 0 };
    int prev_3 { GLFW_RELEASE }, lock_3 { 0 };
};