#pragma once
#include "../util/keyboard.hpp"
#include "../util/mouse.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include <X11/X.h>
#include <cstddef>
#include <iostream>
#include <irrlicht/IEventReceiver.h>

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2, PhysicsCmp2, InventarioCmp, EstadisticaCmp>;
    using SYSTAGs = MP::Typelist<>;

    using SYSCMP_Weapon = MP::Typelist<SoundCmp>;
    using SYSTAG_Weapon = MP::Typelist<TWeapon>;

    void update(LevelMan& LM, TheEngine& eng, SoundSystem_t& SS, double const dt) {
        auto& EM = LM.getEM();
        auto& bb = EM.getBoard();
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& player, InputCmp2& input, RenderCmp2& rend, PhysicsCmp2& phy, InventarioCmp& equipment, EstadisticaCmp& stats) {
                double reloadTimer = 0;
                bool arriba = false;
                bool abajo  = false;

                if(equipment.reloading == 1) { equipment.clockReload += dt; }
                equipment.clockCadence += dt;
                phy.v_lin = phy.v_ang = 0;
                
                movementMouse(player, eng, rend, phy);
                if(mouse.isLeftPressed()) { shoot(LM, player, eng, SS, equipment, reloadTimer); }

                if(keyboard.isKeyPressed(input.key_up))    { phy.v_lin =  stats.speed; arriba = true;}
                if(keyboard.isKeyPressed(input.key_down))  { phy.v_lin = -stats.speed; abajo  = true;}
                if(keyboard.isKeyPressed(input.key_right)) { diagonalMovement(phy, stats.speed, arriba, abajo); }
                if(keyboard.isKeyPressed(input.key_left))  { diagonalMovement(phy, -stats.speed, abajo, arriba); }
                if(keyboard.isKeyPressed(input.key_reloadCurrentAmmo)) { reload(EM, equipment);}
                if(keyboard.isKeyPressed(input.key_weapon1))           { changeWeapon(equipment, rend, 0, eng); }
                if(keyboard.isKeyPressed(input.key_weapon2) && equipment.inventary[1] != 0) { changeWeapon(equipment, rend, 1, eng); }
                if(keyboard.isKeyPressed(input.key_weapon3) && equipment.inventary[2] != 0) { changeWeapon(equipment, rend, 2, eng); }
                //if(keyboard.isKeyPressed(input.key_interaction)){ interact(EM, player, input.key_interaction); }

                if(keyboard.isKeyPressed(input.key_unlockAll))     { unlockAll(equipment.inventary); }
                if(keyboard.isKeyPressed(input.key_reloadALLAmmo)) { reloadAll(EM, equipment); }
                
                bb = { phy.x, phy.z, true, true , player.getID()};
            }
        );
    } 

    virtual bool OnEvent(const irr::SEvent& event) {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT){
            switch (event.KeyInput.Key) {
                case irr::KEY_KEY_W:
                    checkPressed(event, XK_W);
                    break;
                case irr::KEY_KEY_A:
                    checkPressed(event, XK_A);
                    break;
                case irr::KEY_KEY_S:
                    checkPressed(event, XK_S);
                    break;
                case irr::KEY_KEY_D:
                    checkPressed(event, XK_D);
                    break;
                case irr::KEY_KEY_E:
                    checkPressed(event, XK_E);
                    break;
                case irr::KEY_KEY_P:
                    checkPressed(event, XK_P);
                    break;
                case irr::KEY_KEY_R:
                    checkPressed(event, XK_R);
                    break;
                case irr::KEY_KEY_F:
                    checkPressed(event, XK_F);
                    break;
                case irr::KEY_KEY_1:
                    checkPressed(event,XK_1);
                    break;
                case irr::KEY_KEY_2:
                    checkPressed(event,XK_2);
                    break;
                case irr::KEY_KEY_3:
                    checkPressed(event,XK_3);
                    break;
                case irr::KEY_KEY_L:
                    checkPressed(event,XK_L);
                    break;
                case irr::KEY_ESCAPE:
                    exit(0);
                    break;
                default:
                    break;
            }
        }
        else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
            switch(event.MouseInput.Event) {
                case irr::EMIE_LMOUSE_PRESSED_DOWN:
                    mouse.pressLeft();
                    break;
                case irr::EMIE_LMOUSE_LEFT_UP:
                    mouse.releaseLeft();
                    break;
                default: break;
            }
        }
        return false;
    }

    void checkPressed(const irr::SEvent& event, KeySym k) {
        if(event.KeyInput.PressedDown) { keyboard.keyPressed(k);  }
        else                           { keyboard.keyReleased(k); }
    }

private:
    //metodos del input
    void movementMouse(Enty& player, TheEngine& eng, RenderCmp2& rend, PhysicsCmp2& phy) {
        auto centerWidth  = static_cast<irr::s32>(eng.getWidth()/2);
        auto centerHeight = static_cast<irr::s32>(eng.getHeight()/2);
        auto cursor       = eng.getDevice()->getCursorControl();
        auto ray_traced   = eng.getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates({ cursor->getPosition().X, cursor->getPosition().Y });
        auto angy = eng.getCamera()->getRotation().Y * std::numbers::pi / 180;
        auto angx = eng.getCamera()->getRotation().X * std::numbers::pi / 180;

        eng.getCamera()->setTarget({ ray_traced.end.X, ray_traced.end.Y, ray_traced.end.Z });
        rend.n->setRotation({
            eng.getCamera()->getRotation().X, 
            eng.getCamera()->getRotation().Y, 
            0
        });
        cursor->setPosition(centerWidth, centerHeight);

        phy.orieny = angy;
        phy.orienx = angx;
    }
    
    void shoot(LevelMan& LM, Enty& player, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment, double reloadTimer) {
        auto& EM = LM.getEM();
        int ammo = 0;
        double weaponCadence = 0;
        switch (equipment.equipada) {
            case 0: ammo = equipment.magazine1;
                    reloadTimer = equipment.reloadTime1;
            break;
            case 1: ammo = equipment.magazine2;
                    reloadTimer = equipment.reloadTime2;
            break;
            case 2: ammo = equipment.magazine3;
                    reloadTimer = equipment.reloadTime3;
                    weaponCadence = equipment.cadenceWeapon3;
            break;
            default: break;
        }
        
        if(equipment.reloading == 1 && equipment.clockReload <= reloadTimer) { return; }
        equipment.clockReload = 0;
        notReloading(equipment);
        
        if(ammo > 0) { createBullet(LM, player, weaponCadence, eng, SS); }
        else if(ammo == 0) { reload(EM, equipment); }

        if(equipment.equipada == 0 || equipment.equipada ==1){ mouse.releaseLeft(); }
    }
    
    void diagonalMovement(PhysicsCmp2& p, float const speed, bool const up, bool const down) {
        p.v_lin = speed;
        p.v_ang = 90;
        if(up)        p.v_ang = 45;
        else if(down) p.v_ang = 135;
    }

    void reload(EntyMan& EM, InventarioCmp& equipment) {
        int currentAmmo = 0;
        switch (equipment.equipada) {
            case 0:
                reloadProcess(equipment, currentAmmo, equipment.ammo1, equipment.magazine1, 5);
            break;
            case 1:
                reloadProcess(equipment, currentAmmo, equipment.ammo2, equipment.magazine2, 2);
            break;
            case 2:
                reloadProcess(equipment, currentAmmo, equipment.ammo3, equipment.magazine3, 25);
            break;
            default: break;
        }
        soundWeapon(EM);
    }

    void changeWeapon(InventarioCmp& p_invent, RenderCmp2& playerRender, size_t equip, TheEngine& eng) {
        playerRender.n->remove();
        
        if(p_invent.reloading == 1) {
            switch (p_invent.equipada) {
                case 0: p_invent.clockReload1 = p_invent.clockReload;
                    break;
                case 1: p_invent.clockReload2 = p_invent.clockReload;
                    break;
                case 2: p_invent.clockReload3 = p_invent.clockReload;
                    break;
                default: break;
            }
        }
        
        p_invent.inventary[p_invent.equipada] = 1;
        p_invent.equipada = equip;
        p_invent.inventary[equip] = 2;

        switch (p_invent.equipada) {
            case 0:
                playerRender.n=eng.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp");
                p_invent.clockReload = p_invent.clockReload1;
                if(p_invent.clockReload >= p_invent.reloadTime1) { notReloading(p_invent); }
                else { iAmReloading(p_invent); }
                break;

            case 1:
                playerRender.n=eng.createPlayer("assets/models/armas/escopeta.obj","assets/textures/fire.bmp");
                p_invent.clockReload = p_invent.clockReload2;
                if(p_invent.clockReload >= p_invent.reloadTime2) { notReloading(p_invent); }
                else { iAmReloading(p_invent); }
                break;

            case 2:
                playerRender.n=eng.createPlayer("assets/models/armas/subfusil.obj","assets/textures/fire.bmp");
                p_invent.clockReload = p_invent.clockReload3;
                if(p_invent.clockReload >= p_invent.reloadTime3) { notReloading(p_invent); }
                else { iAmReloading(p_invent); }
                break;

            default: break;
        }
    }

    //void interact(EntyMan& EM, Enty& player, KeySym key) {
    //    auto& col = EM.getComponent<EstadoCmp>(player);
    //    if(col.colision != 0){
    //        auto& col_entity = EM.getEntityById(col.entityCol);
    //        if(col_entity.hasTAG<TWeapon>()){
    //            //std::cout<<"Recoger arma\n";
    //        }
    //        else if(col_entity.hasTAG<TDoor>()) {
    //            //std::cout<<"Abrir puerta\n";
    //            openDoor(EM, player, col_entity);
    //        }
    //        else if(col_entity.hasTAG<TKey>()) {
    //            //std::cout<<"Recoger llave\n";
    //            addKeyToInventary(EM, player);
    //            col_entity.setDestroy();
    //        }
    //    }
    //    keyboard.keyReleased(key);
    //}
    
    void unlockAll(size_t* invent) {
        for(int i=0; i<3; i++) {
            if(invent[i]!=2) invent[i]=1;
        }
    }

    void reloadAll(EntyMan& EM, InventarioCmp& equip) {
        equip.ammo1 = 20;
        equip.ammo2 = 10;
        equip.ammo3 = 100;
        soundWeapon(EM);
    }

    //metodos auxiliares
    //void addKeyToInventary(EntyMan& EM, Enty& player) {
    //    auto& inventay = EM.getComponent<InventarioCmp>(player);
    //    inventay.keys_inv[0] = 1;
    //    //std::cout<<"Llave guardada\n";
    //}
    //
    //void openDoor(EntyMan& EM, Enty& player, Enty& door) {
    //    auto& inventay = EM.getComponent<InventarioCmp>(player);
    //    if(inventay.keys_inv[0]) {
    //        //std::cout<<"Puerta abierta\n";
    //        door.setDestroy();
    //    }
    //    else {
    //        //std::cout<<"Puerta cerrada\n";
    //    }
    //}

    void reloadProcess(InventarioCmp& p_invent, int currentAmmo, int& ammo, int& magazine, int maxAmmo) {
        currentAmmo = maxAmmo - magazine; //0 is magazine complete
        if((ammo-currentAmmo) > 0){
            ammo = ammo-currentAmmo;
            magazine = magazine + currentAmmo;
        }
        else{
            ammo = 0;
            magazine = ammo;
        }
        iAmReloading(p_invent);
    }

    void iAmReloading(InventarioCmp& equipment){ equipment.reloading = 1; }

    void notReloading(InventarioCmp& equipment){ equipment.reloading = 0; }

    void createBullet(LevelMan& LM, Enty& player, double cadenciaWeapon, TheEngine& eng, SoundSystem_t& SS) {
        auto& EM = LM.getEM();
        auto& equipment  = EM.getComponent<InventarioCmp>(player);
        auto& phy_player = EM.getComponent<PhysicsCmp2>(player);

        if(equipment.clockCadence <= cadenciaWeapon) { return; }
        //Cadencia alcanzada
        equipment.clockCadence = 0 ;

        if(equipment.equipada == 0){ //pistola
            LM.createBullet(phy_player, eng, SS, 18., 5., 0.1, 9.);
            equipment.magazine1 -= 1;
        }
        else if (equipment.equipada == 1){ //escopeta
            for(float i = -0.4; i < 0.5; i += 0.2){
                float posx = i*cos(phy_player.orieny);
                float posz = i*-sin(phy_player.orieny);

                LM.createBullet(phy_player, eng, SS, 8., 4., 0.15, 0.4, posx, 0,     posz);
                LM.createBullet(phy_player, eng, SS, 8., 4., 0.15, 0.4, posx, 2*0.2, posz);
                if(i>-0.4 && i<0.4) LM.createBullet(phy_player, eng, SS, 8., 4., 0.15, 0.4, posx, 1*0.2, posz);
            }
            equipment.magazine2 -= 1;
        }
        else if(equipment.equipada == 2){ //ametralladora
            LM.createBullet(phy_player, eng, SS, 15., 4., 0.1, 1.5);
            equipment.magazine3 -= 1;
        }
    }

    void soundWeapon(EntyMan& EM) {
        for(auto& a : EM.getEntities()){
            if(a.hasTAG<TWeapon>()){
                auto& sound = EM.getComponent<SoundCmp>(a);
                EM.changeSound(sound, 1);
            }
        }
    }

    static void onkeypressed(KeySym k)  { keyboard.keyPressed(k);  }
    static void onkeyreleased(KeySym k) { keyboard.keyReleased(k); }

    inline static Keyboard keyboard {};
    inline static Mouse mouse {};
};