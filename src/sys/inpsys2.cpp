#include "inpsys2.hpp"
#include "../man/levelman.hpp"
#include "UIsys.hpp"
#include "rensys2.hpp"
#include "soundsystem.hpp"
#include "../eng/engine2.hpp"
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <X11/X.h>
#include <cstdint>
#include <glm/fwd.hpp>

/*NUEVO*/ void InpSys2::update2(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt, UIsys& UI) {
    auto& EM = LM.getEM();
    auto& bb = EM.getBoard();
    checkKeyboard(GE.getWindow());

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& player, InputCmp2& input, RenderCmp2& rend, PhysicsCmp2& phy, InventarioCmp& equip, EstadisticaCmp& stats) {
            bool up = false, down = false;

            if(equip.reloading == 1) { equip.clockReload += dt; }
            equip.clockCadence += dt;
            phy.v_lin = phy.v_ang = 0;

            if(mouse.isButtonPressed(LEFT_Button))          { shoot2(LM, GE, equip, phy, SouSys, player.getID()); }
            if(keyboard.isKeyPressed(input.key_up))         { phy.v_lin =  10; up   = true; }
            if(keyboard.isKeyPressed(input.key_down))       { phy.v_lin = -10; down = true; }
            if(keyboard.isKeyPressed(input.key_left))       { digonalMove(phy, -10, up, down); }
            if(keyboard.isKeyPressed(input.key_right))      { digonalMove(phy, 10, down, up); }
            if(keyboard.isKeyPressed(input.key_rldCrrAmmo)) { reload2(LM, GE, equip); }
            if(keyboard.isKeyPressed(input.key_weapon1))    { changeWeapon2(LM, GE, equip, rend, 0); }
            if(keyboard.isKeyPressed(input.key_weapon2) && equip.inventary[1] != 0) { changeWeapon2(LM, GE, equip, rend, 1); }
            if(keyboard.isKeyPressed(input.key_weapon3) && equip.inventary[2] != 0) { changeWeapon2(LM, GE, equip, rend, 2); }
            if(keyboard.isKeyPressed(XK_Escape))            { stats.hitpoints = 0; }
            
            bb.tx      = phy.x; 
            bb.tz      = phy.z; 
            bb.tactive = true; 
            bb.shoot   = true; 
            bb.entyID  = player.getID();
        }
    );
}

/*NUEVO*/ bool InpSys2::checkKeyboard(GLFWwindow* window) {
    unsigned int const size = 10;

    int GLFW_keys[size] {
        GLFW_MOUSE_BUTTON_LEFT, GLFW_KEY_W,      GLFW_KEY_S, GLFW_KEY_A, 
        GLFW_KEY_D,             GLFW_KEY_ESCAPE, GLFW_KEY_R, GLFW_KEY_1,
        GLFW_KEY_2,             GLFW_KEY_3
    };

    int keyboar_k[size] {
        LEFT_Button, XK_W, XK_S, XK_A, XK_D,
        XK_Escape,   XK_R, XK_1, XK_2, XK_3
    };

    int state = glfwGetMouseButton(window, GLFW_keys[0]);
    checkPressed(keyboar_k[0], GLFW_keys[0], state);
    
    for(unsigned int i = 1; i < size; i++) {
        int actual_state = glfwGetKey(window, GLFW_keys[i]);
        checkPressed(keyboar_k[i], GLFW_keys[i], actual_state);
    }
}

/*NUEVO*/ void InpSys2::checkPressed(int k, int GL_k, int actual) {
    switch(GL_k) {
        case GLFW_MOUSE_BUTTON_LEFT:
            prev_Left = previousMouseStatus(k, actual, prev_Left, lock_Left);
            break;
        case GLFW_KEY_W:
            prev_W    = previousKeyStatus(k, actual, prev_W, lock_W);
            break;
        case GLFW_KEY_S:
            prev_S    = previousKeyStatus(k, actual, prev_S, lock_S);
            break;
        case GLFW_KEY_A:
            prev_A    = previousKeyStatus(k, actual, prev_A, lock_A);
            break;
        case GLFW_KEY_D:
            prev_D    = previousKeyStatus(k, actual, prev_D, lock_D);
            break;
        case GLFW_KEY_R:
            prev_R    = previousKeyStatus(k, actual, prev_R, lock_R);
            break;
        case GLFW_KEY_1:
            prev_1    = previousKeyStatus(k, actual, prev_1, lock_1);
            break;
        case GLFW_KEY_2:
            prev_2    = previousKeyStatus(k, actual, prev_2, lock_2);
            break;
        case GLFW_KEY_3:
            prev_3    = previousKeyStatus(k, actual, prev_3, lock_3);
            break;
        case GLFW_KEY_ESCAPE:
            prev_Esc  = previousKeyStatus(k, actual, prev_Esc, lock_Esc);
            break;
    }
}

// Pasar funcion por parametro -> unificar metodos
/*NUEVO*/ int InpSys2::previousKeyStatus(int k, int actual, int prev, int lock) {
    if(!actual)      keyboard.keyReleased(k);   // Actual   state: Release
    else {                                      // Actual   state: Press
        if(!prev)    keyboard.keyPressed(k);    // Previous state: Release
        else {                                  // Previous state: Press
            if(lock) keyboard.keyPressed(k);    // Lock          : On
            else     keyboard.keyReleased(k);   // Lock          : Off
        }      
    }

    return actual;
}

// Pasar funcion por parametro -> unificar metodos
/*NUEVO*/ int InpSys2::previousMouseStatus(int k, int actual, int prev, int lock) {
    if(!actual)      mouse.releaseButton(k);      // Actual   state: Release
    else {                                          // Actual   state: Press
        if(!prev)    mouse.pressButton(k);        // Previous state: Release
        else {                                      // Previous state: Press
            if(lock) mouse.pressButton(k);        // Lock          : On
            else     mouse.releaseButton(k);      // Lock          : Off
        }
    }

    return actual;
}

/*NUEVO*/ void InpSys2::changeWeapon2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, RenderCmp2& rend, size_t equip) {
    if(invent.reloading == 1)
        switch (invent.equipada) {
            case 0: invent.gun.clock_R   = invent.clockReload; break;
            case 1: invent.shot.clock_R  = invent.clockReload; break;
            case 2: invent.rifle.clock_R = invent.clockReload; break;
        }

    changeWeaponMethod(GE, invent, equip, invent.equipada);
}

/*NUEVO*/ void InpSys2::changeWeaponMethod(GraphicEngine& GE, InventarioCmp& invent, size_t new_, size_t old_) {
    Mag_Amm bullets {};

    GE.playerModel->remove();
    
    invent.inventary[new_] = 2;
    invent.inventary[old_] = 1;
    invent.equipada        = new_;

    switch (invent.equipada) {
        case 0:
            bullets = changeWeaponProcess(GE, invent, "assets/models/armas/pistola.obj", invent.gun);
            break;
        case 1:
            bullets = changeWeaponProcess(GE, invent, "assets/models/armas/escopeta.obj", invent.shot);
            break;
        case 2:
            bullets = changeWeaponProcess(GE, invent, "assets/models/armas/subfusil.obj", invent.rifle);
            break;
    }
}

/*NUEVO*/ Mag_Amm InpSys2::changeWeaponProcess(GraphicEngine& GE, InventarioCmp& invent, std::string file, Weapon& wpn) {
    GE.createPlayerModel(file);
    invent.clockReload = wpn.clock_R;
    if(invent.clockReload >= wpn.reload_T) invent.reloading = 0;
    else                                   invent.reloading = 1;

    return { wpn.magazine, wpn.ammo };
}

/*NUEVO*/ void InpSys2::reload2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent) {
    auto& EM = LM.getEM();
    switch (invent.equipada) {
        case 0: reloadProcess2(LM, GE, invent, invent.gun);   break;
        case 1: reloadProcess2(LM, GE, invent, invent.shot);  break;
        case 2: reloadProcess2(LM, GE, invent, invent.rifle); break;
        default: break;
    }

    soundWeapon(EM);
}

/*NUEVO*/ void InpSys2::reloadProcess2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, Weapon& wpn) {
    int currentAmmo = wpn.maxMagazine - wpn.magazine; //0 is magazine complete

    if((wpn.ammo - currentAmmo) > 0) {
        wpn.magazine += currentAmmo;
        wpn.ammo     -= currentAmmo;
    }
    else {
        wpn.magazine = wpn.ammo;
        wpn.ammo     = 0;
    }

    invent.reloading = 1;
}

/*NUEVO*/ void InpSys2::shoot2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, PhysicsCmp2& phy, SoundSystem_t& SouSys, size_t player_ID) {
    Mag_Tim_Cad values {};
    
    switch (invent.equipada) {
        case 0: values = shootProcess(invent.gun);   break;
        case 1: values = shootProcess(invent.shot);  break;
        case 2: values = shootProcess(invent.rifle); break;
    }
    
    if(invent.reloading == 1 && invent.clockReload <= values.tim) return;

    invent.clockReload = 0;
    invent.reloading   = 0;
    
    if(values.mag > 0) createBullet2(LM, GE, invent, phy, SouSys, values.cad, player_ID);
    else               reload2(LM, GE, invent);
}

/*NUEVO*/ Mag_Tim_Cad InpSys2::shootProcess(Weapon& wpn) {
    return { wpn.magazine, wpn.reload_T, wpn.cadence };
}

/*NUEVO*/ void InpSys2::createBullet2(LevelMan& LM, GraphicEngine& GE, InventarioCmp& invent, 
PhysicsCmp2& phy, SoundSystem_t& SouSys, double cadenciaWeapon, size_t player_ID) {
    if(invent.clockCadence <= cadenciaWeapon) return;

    auto& EM = LM.getEM();
    auto* cam = GE.getCamera();

    auto& ply   = EM.getEntityById(player_ID);
    auto& stats = EM.getComponent<EstadisticaCmp>(ply);

    invent.clockCadence = 0 ;

    switch (invent.equipada) {
        case 0:
            bulletProcess(LM, GE, cam, player_ID, invent.gun, 
                phy, SouSys, stats.extra_dmg);
            break;
        case 1:
            bulletProcess(LM, GE, cam, player_ID, invent.shot, 
                phy, SouSys, stats.extra_dmg, true);
            break;
        case 2: 
            bulletProcess(LM, GE, cam, player_ID, invent.rifle, 
                phy, SouSys, stats.extra_dmg, false, 1);
            break;
    }
}

void InpSys2::bulletProcess(LevelMan& LM, GraphicEngine& GE, ECamera* cam, size_t player_ID, 
Weapon& wpn, PhysicsCmp2& phy, SoundSystem_t& SouSys, double extra, bool is_shot, int lock) {
    auto& EM = LM.getEM();

    lock_Left = lock;
    recoil(EM, GE, cam, player_ID, wpn.recoil);
    wpn.magazine--;

    if(is_shot)
        LM.createShotgunBullets2(
            GE, phy, 
            EstadisticaCmp { 
                .damage = static_cast<int>(5 * extra), 
                .speed  = 0.5f 
            }, 
            GE.getFrontCamera(), SouSys
        );
    else
        LM.createBullet2(
            GE, phy, 
            EstadisticaCmp { 
                .damage = static_cast<int>(5 * extra), 
                .speed  = 0.5f 
            }, 
            GE.getFrontCamera(), SouSys
        );
}

void InpSys2::recoil(EntyMan& EM, GraphicEngine& GE, ECamera* cam, size_t player_ID, double desv) {
    cam->Pitch += desv;
    RenSys2::updateCamera(EM, GE, player_ID);
}

void InpSys2::digonalMove(PhysicsCmp2& phy, float const speed, bool const up, bool const down) {
    phy.v_lin = speed;
    phy.v_ang = 90;
    if(up)        phy.v_ang = 135;
    else if(down) phy.v_ang = 45;
}

void InpSys2::soundWeapon(EntyMan& EM) {
    for(auto& a : EM.getEntities()){
        if(a.hasTAG<TWeapon>() && a.hasCMP<SoundCmp>()) {
            auto& sound = EM.getComponent<SoundCmp>(a);
            EM.changeSound(sound, 1);
        }
    }
}