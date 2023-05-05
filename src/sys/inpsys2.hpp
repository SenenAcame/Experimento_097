#pragma once
#include "../util/types.hpp"
#include "../util/keyboard.hpp"
#include "../util/mouse.hpp"
#include <GLFW/glfw3.h>
//#include <irrlicht/IEventReceiver.h>

//struct TheEngine;
struct LevelMan;
struct SoundSystem_t;
struct GraphicEngine;
struct GLFWwindow;

struct Mag_Amm {
    int mag {}, amm {};
};

struct Mag_Tim_Cad {
    int mag {};
    double tim {}, cad {};
};

struct InpSys2 {
    using EXACMPs = MP::Typelist<InputCmp2, PhysicsCmp2>;
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2, PhysicsCmp2, InventarioCmp, EstadisticaCmp>;
    using SYSTAGs = MP::Typelist<>;

    using SYSCMP_Weapon = MP::Typelist<SoundCmp>;
    using SYSTAG_Weapon = MP::Typelist<TWeapon>;

    ///*VIEJO*/ void update (LevelMan& LM, TheEngine& eng, SoundSystem_t& SS, double const dt);
    /*NUEVO*/ void update2(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt);

    ///*VIEJO*/ virtual bool OnEvent(const irr::SEvent& event);
    /*NUEVO*/ bool checkKeyboard(GLFWwindow* window);

    ///*VIEJO*/ void checkPressed(const irr::SEvent& event, KeySym k);
    /*NUEVO*/ void checkPressed(int k, int GL_k, int actual);

private:
    /*NUEVO*/ int previousKeyStatus  (int k, int actual, int prev, int lock);
    /*NUEVO*/ int previousMouseStatus(int k, int actual, int prev, int lock);

    //metodos del input
    ///*VIEJO*/ void movementMouse(TheEngine& eng, RenderCmp2& rend, PhysicsCmp2& phy);
    ///*VIEJO*/ void changeWeapon (LevelMan& LM, InventarioCmp& p_invent, RenderCmp2& playerRender, size_t equip, TheEngine& eng);

    /*NUEVO*/ void    changeWeapon2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, RenderCmp2& rend, size_t equip);
    /*NUEVO*/ Mag_Amm changeWeaponProcess(GraphicEngine& GE, InventarioCmp& invent, std::string file, Weapon& wpn);

    ///*VIEJO*/ void reload(LevelMan& LM, TheEngine& dev, InventarioCmp& equipment);
    ///*VIEJO*/ void reloadProcess(LevelMan& LM, TheEngine& dev, InventarioCmp& p_invent, int currentAmmo, int& ammo, int& magazine, int maxAmmo);

    /*NUEVO*/ void reload2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent);
    /*NUEVO*/ void reloadProcess2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, Weapon& wpn);

    ///*VIEJO*/ void shoot(LevelMan& LM, Enty& player, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment);
    ///*VIEJO*/ void createBullet(LevelMan& LM, Enty& player, double cadenciaWeapon, TheEngine& eng, SoundSystem_t& SS);

    /*NUEVO*/ void shoot2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, PhysicsCmp2& phy, SoundSystem_t& SouSys);
    /*NUEVO*/ Mag_Tim_Cad shootProcess(Weapon& wpn);
    /*NUEVO*/ void createBullet2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, PhysicsCmp2& phy, SoundSystem_t& SouSys, double cadenciaWeapon);

    void digonalMove(PhysicsCmp2& phy, float const speed, bool const up, bool const down);
    
    //void interact(EntyMan& EM, Enty& player, KeySym key);
    //void unlockAll(size_t* invent);
    //void reloadAll(EntyMan& EM, InventarioCmp& equip);

    //metodos auxiliares
    //void addKeyToInventary(EntyMan& EM, Enty& player);
    //void openDoor(EntyMan& EM, Enty& player, Enty& door);
    void iAmReloading(InventarioCmp& equipment) { equipment.reloading = 1; }
    void notReloading(InventarioCmp& equipment) { equipment.reloading = 0; }
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