#pragma once
#include "../util/types.hpp"
#include "../util/keyboard.hpp"
#include "../util/mouse.hpp"
#include <irrlicht/IEventReceiver.h>

struct TheEngine;
struct LevelMan;
struct SoundSystem_t;

struct InpSys2 : public irr::IEventReceiver {
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2, PhysicsCmp2, InventarioCmp, EstadisticaCmp>;
    using SYSTAGs = MP::Typelist<>;

    using SYSCMP_Weapon = MP::Typelist<SoundCmp>;
    using SYSTAG_Weapon = MP::Typelist<TWeapon>;

    void update(LevelMan& LM, TheEngine& eng, SoundSystem_t& SS, double const dt);
    virtual bool OnEvent(const irr::SEvent& event);
    void checkPressed(const irr::SEvent& event, KeySym k);

private:
    //metodos del input
    void movementMouse(TheEngine& eng, RenderCmp2& rend, PhysicsCmp2& phy);
    void shoot(LevelMan& LM, Enty& player, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment);
    void digonalMove(PhysicsCmp2& phy, float const speed, bool const up, bool const down);
    void reload(LevelMan& LM, TheEngine& dev, InventarioCmp& equipment);
    void changeWeapon(LevelMan& LM, InventarioCmp& p_invent, RenderCmp2& playerRender, size_t equip, TheEngine& eng);
    //void interact(EntyMan& EM, Enty& player, KeySym key);
    void unlockAll(size_t* invent);
    void reloadAll(EntyMan& EM, InventarioCmp& equip);

    //metodos auxiliares
    //void addKeyToInventary(EntyMan& EM, Enty& player);
    //void openDoor(EntyMan& EM, Enty& player, Enty& door);
    void reloadProcess(LevelMan& LM, TheEngine& dev, InventarioCmp& p_invent, int currentAmmo, int& ammo, int& magazine, int maxAmmo);
    void iAmReloading(InventarioCmp& equipment) { equipment.reloading = 1; }
    void notReloading(InventarioCmp& equipment) { equipment.reloading = 0; }
    void createBullet(LevelMan& LM, Enty& player, double cadenciaWeapon, TheEngine& eng, SoundSystem_t& SS);
    void soundWeapon(EntyMan& EM);

    static void onkeypressed(KeySym k)  { keyboard.keyPressed(k);  }
    static void onkeyreleased(KeySym k) { keyboard.keyReleased(k); }

    inline static Keyboard keyboard {};
    inline static Mouse mouse {};
};