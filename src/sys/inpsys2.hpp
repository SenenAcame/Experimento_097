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
            [&](Enty& player, InputCmp2& input, RenderCmp2& rend, PhysicsCmp2& phy, InventarioCmp& equip, EstadisticaCmp& stats) {
                bool up = false, down = false;

                
                double weaponReloadTimer = 0;
                double maxMagazine = 0;
                double retroceso = 0;
                int magazine = 0;

                equip.clockCadence += dt;
                phy.v_lin = phy.v_ang = 0;

                switch (equip.equipada) {
                    case 0: 
                        weaponReloadTimer = equip.reloadTime1;
                        magazine = equip.magazine1;
                        maxMagazine = equip.Maxmagazine1;
                        retroceso = equip.retroceso1;
                    break;

                    case 1: 
                        weaponReloadTimer = equip.reloadTime2;
                        magazine = equip.magazine2;
                        maxMagazine = equip.Maxmagazine2;
                        retroceso = equip.retroceso2;
                    break;

                    case 2: 
                        weaponReloadTimer = equip.reloadTime3; 
                        magazine = equip.magazine3;
                        maxMagazine = equip.Maxmagazine3;
                        retroceso = equip.retroceso3;
                    break;

                    default: break;
                }
                
                if(equip.reloading == 1 && equip.clockReload >= weaponReloadTimer){
                    notReloading(LM, eng, equip); 
                    equip.clockReload = 0;
                }
                else if(equip.reloading == 1){

                    equip.clockReload+=dt;
                }

                if(mouse.isLeftPressed()) { 
                    
                    if(equip.reloading == 0 && magazine > 0){
                        
                        movementMouse(eng, rend, phy, retroceso); 
                        shoot(LM, player, eng, SS, equip);
                            
                    }
                    else if (magazine == 0 && equip.reloading == 0){
                        
                        movementMouse(eng, rend, phy, 0);
                        reload(LM, eng, equip); 
                        
                    }
                    else{
                        movementMouse(eng, rend, phy, 0);
                    }
                }
                else{
                    
                    movementMouse(eng, rend, phy, 0);

                }

                if(keyboard.isKeyPressed(input.key_up))         { phy.v_lin =  stats.speed; up = true;}
                if(keyboard.isKeyPressed(input.key_down))       { phy.v_lin = -stats.speed; down  = true;}
                if(keyboard.isKeyPressed(input.key_right))      { digonalMove(phy, stats.speed, up, down); }
                if(keyboard.isKeyPressed(input.key_left))       { digonalMove(phy, -stats.speed, down, up); }
                if(keyboard.isKeyPressed(input.key_rldCrrAmmo)) { 
                    keyboard.keyReleased(input.key_rldCrrAmmo);
                    reload(LM, eng, equip); 
                }
                if(keyboard.isKeyPressed(input.key_weapon1))    { 
                    keyboard.keyReleased(input.key_weapon1);
                    changeWeapon(LM, equip, rend, 0, eng); 
                }
                if(keyboard.isKeyPressed(input.key_weapon2) && equip.inventary[1] != 0) {
                    keyboard.keyReleased(input.key_weapon2); 
                    changeWeapon(LM, equip, rend, 1, eng); 
                }
                if(keyboard.isKeyPressed(input.key_weapon3) && equip.inventary[2] != 0) { 
                    keyboard.keyReleased(input.key_weapon3);
                    changeWeapon(LM, equip, rend, 2, eng); 
                }
                //if(keyboard.isKeyPressed(input.key_interaction)) { interact(EM, player, input.key_interaction); }

                if(keyboard.isKeyPressed(input.key_unlockAll))  { unlockAll(equip.inventary); }
                if(keyboard.isKeyPressed(input.key_rldALLAmmo)) { reloadAll(EM, equip); }
                
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
    void movementMouse(TheEngine& eng, RenderCmp2& rend, PhysicsCmp2& phy, double retroceso) {
        auto centerWidth  = static_cast<irr::s32>(eng.getWidth() /2);
        auto centerHeight = static_cast<irr::s32>(eng.getHeight()/2);
        auto cursor       = eng.getDevice()->getCursorControl();
        auto ray_traced   = eng.getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates({ cursor->getPosition().X, cursor->getPosition().Y + retroceso });
        auto angx = eng.getCamera()->getRotation().X * std::numbers::pi / 180;
        auto angy = eng.getCamera()->getRotation().Y * std::numbers::pi / 180;
        
        eng.getCamera()->setTarget({ ray_traced.end.X, ray_traced.end.Y, ray_traced.end.Z });
        rend.n->setRotation({
            eng.getCamera()->getRotation().X, 
            eng.getCamera()->getRotation().Y, 
            0,
        });
        cursor->setPosition(centerWidth, centerHeight);

        phy.orieny = angy;
        phy.orienx = angx;
    }
    
    void shoot(LevelMan& LM, Enty& player, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment) {
        
        double weaponCadence = 0;
        double reloadTimer = 0;
        int magazine = 0;

        switch (equipment.equipada) {
            case 0: 
                    reloadTimer = equipment.reloadTime1;
                    magazine = equipment.magazine1;
                    
            break;
            case 1: 
                    reloadTimer = equipment.reloadTime2;
                    magazine = equipment.magazine2;
                    
            break;
            case 2: 
                    reloadTimer = equipment.reloadTime3;
                    weaponCadence = equipment.cadenceWeapon3;
                    magazine = equipment.magazine3;
                    
            break;
            default: break;
        }
        
        if(equipment.reloading == 1 && equipment.clockReload <= reloadTimer) { return; }
        
        //std::cout<<"DISPARO\n";
        auto &EM = LM.getEM();
        createBullet(LM, player, weaponCadence, eng, SS);
        LM.updateInterfaceMag(eng, magazine-1);
           
    
        if(equipment.equipada == 0 || equipment.equipada ==1){ mouse.releaseLeft(); }
    }
    
    void digonalMove(PhysicsCmp2& phy, float const speed, bool const up, bool const down) {
        phy.v_lin = speed;
        phy.v_ang = 90;
        if(up)        phy.v_ang = 45;
        else if(down) phy.v_ang = 135;
    }

    void reload(LevelMan& LM, TheEngine& dev, InventarioCmp& equipment) {

        auto& EM = LM.getEM();
        iAmReloading(equipment);
        soundWeapon(EM);
        
    }

    void changeWeapon(LevelMan& LM, InventarioCmp& equip, RenderCmp2& playerRender, size_t Wequip, TheEngine& eng) {
        
        int magazine {}, ammo{};
        playerRender.n->remove();

        if(equip.reloading == 1) {
            switch (equip.equipada) {
                case 0: equip.clockReload1 = equip.clockReload;
                
                    break;
                case 1: equip.clockReload2 = equip.clockReload;
                
                    break;
                case 2: equip.clockReload3 = equip.clockReload;
                
                    break;
                default: break;
            }
        }
        
        equip.inventary[equip.equipada] = 1;
        equip.equipada = Wequip;
        equip.inventary[Wequip] = 2;

        switch (equip.equipada) {
            case 0: 
                playerRender.n = eng.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp");
                if(equip.magazine1 > 0){
                    equip.reloading = 0;
                    
                }
                else{
                    equip.reloading = 1;
                }
                magazine = equip.magazine1;
                ammo = equip.ammo1;
                equip.clockReload = equip.clockReload1;
            
            break;
            case 1: 
                playerRender.n = eng.createPlayer("assets/models/armas/escopeta.obj","assets/textures/fire.bmp");
                if(equip.magazine2 > 0){
                    equip.reloading = 0;
                    
                }
                else{
                    equip.reloading = 1;
                }
                magazine = equip.magazine2;
                ammo = equip.ammo2;
                equip.clockReload = equip.clockReload2;
                break;
            case 2: 
                playerRender.n = eng.createPlayer("assets/models/armas/subfusil.obj","assets/textures/fire.bmp");
                if(equip.magazine3 > 0){
                    equip.reloading = 0;
                    
                }
                else{
                    equip.reloading = 1;
                }
                magazine = equip.magazine3;
                ammo = equip.ammo3;
                equip.clockReload = equip.clockReload3;
                break;
            default: break;
        }

        LM.updateInterfaceWhenReload(eng, magazine, ammo);
     
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

    void notReloading(LevelMan& LM, TheEngine& dev, InventarioCmp& equip) {
        
        int ammo = 0;
        int magazine = 0;
        int maxAmmo = 0;
        int needIt = 0;
        switch (equip.equipada) {
            case 0: 
                    
                    ammo = equip.ammo1;
                    magazine = equip.magazine1;
                    maxAmmo = equip.Maxmagazine1;
                    needIt = maxAmmo - magazine;
                    if((ammo-needIt) > 0){
                        equip.magazine1 = maxAmmo;
                        equip.ammo1 = ammo-needIt;
                    }
                    else {
                        equip.magazine1 = ammo;
                        equip.ammo1 = 0;
                    }
                    LM.updateInterfaceWhenReload(dev, equip.magazine1, equip.ammo1);
                    
            break;
            case 1: 
                    
                    ammo = equip.ammo2;
                    magazine = equip.magazine2;
                    maxAmmo = equip.Maxmagazine2;
                    needIt = maxAmmo - magazine;
                    if((ammo-needIt) > 0){
                        equip.magazine2 = maxAmmo;
                        equip.ammo2 = ammo-needIt;
                    }
                    else {
                        equip.magazine2 = ammo;
                        equip.ammo2 = 0;
                    }
                    LM.updateInterfaceWhenReload(dev, equip.magazine2, equip.ammo2);
                    
            break;
            case 2: 
                    
                    ammo = equip.ammo3;
                    magazine = equip.magazine3;
                    maxAmmo = equip.Maxmagazine3;
                    needIt = maxAmmo - magazine;
                    if((ammo-needIt) > 0){
                        equip.magazine3 = maxAmmo;
                        equip.ammo3 = ammo-needIt;
                    }
                    else {
                        equip.magazine3 = ammo;
                        equip.ammo3 = 0;
                    }
                    LM.updateInterfaceWhenReload(dev, equip.magazine3, equip.ammo3);
                    
            break;
            default: break;
        }

        equip.reloading = 0;
        
    }

    void iAmReloading(InventarioCmp& equipment){ equipment.reloading = 1; }


    void createBullet(LevelMan& LM, Enty& player, double cadenciaWeapon, TheEngine& eng, SoundSystem_t& SS) {
        auto& EM = LM.getEM();
        auto& equipment  = EM.getComponent<InventarioCmp>(player);
        auto& phy_player = EM.getComponent<PhysicsCmp2>(player);
        //int ammo {};

        if(equipment.clockCadence <= cadenciaWeapon) { return; }
        //Cadencia alcanzada
        equipment.clockCadence = 0 ;

        if(equipment.equipada == 0){ //pistola
            LM.createBullet(phy_player, eng, SS, 19., 5., 0.1, 9.);
            equipment.magazine1 -= 1;
            //ammo = equipment.magazine1;
        }
        else if (equipment.equipada == 1){ //escopeta
            LM.createShotgunBullets(phy_player, eng, SS, 24., 3., 0.15, 0.4, 10);
            equipment.magazine2 -= 1;
            //ammo = equipment.magazine1;
        }
        else if(equipment.equipada == 2){ //ametralladora
            LM.createBullet(phy_player, eng, SS, 22., 4., 0.1, 1.5);
            equipment.magazine3 -= 1;
            //ammo = equipment.magazine1;
        }
        //return ammo;
        return;
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