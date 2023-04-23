#include "inpsys2.hpp"
#include "../man/levelman.hpp"
#include "soundsystem.hpp"
#include <iostream>
#include <irrlicht/Keycodes.h>


void InpSys2::update(LevelMan& LM, TheEngine& eng, SoundSystem_t& SS, double const dt) {
    auto& EM = LM.getEM();
    auto& bb = EM.getBoard();
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& player, InputCmp2& input, RenderCmp2& rend, PhysicsCmp2& phy, InventarioCmp& equip, EstadisticaCmp& stats) {
            bool up { false }, down { false };

            if(equip.reloading == 1) { equip.clockReload += dt; }
            equip.clockCadence += dt;
            phy.v_lin = phy.v_ang = 0;
            
            movementMouse(eng, rend, phy);
            if(mouse.isLeftPressed()) { shoot(LM, player, eng, SS, equip); }

            if(keyboard.isKeyPressed(input.key_up))         { phy.v_lin =  stats.speed; up   = true; }
            if(keyboard.isKeyPressed(input.key_down))       { phy.v_lin = -stats.speed; down = true; }
            if(keyboard.isKeyPressed(input.key_right))      { digonalMove(phy, stats.speed, up, down); }
            if(keyboard.isKeyPressed(input.key_left))       { digonalMove(phy, -stats.speed, down, up); }
            if(keyboard.isKeyPressed(input.key_rldCrrAmmo)) { reload(LM, eng, equip); }
            if(keyboard.isKeyPressed(input.key_weapon1))    { changeWeapon(LM, equip, rend, 0, eng); }
            if(keyboard.isKeyPressed(input.key_weapon2) && equip.inventary[1] != 0) { changeWeapon(LM, equip, rend, 1, eng); }
            if(keyboard.isKeyPressed(input.key_weapon3) && equip.inventary[2] != 0) { changeWeapon(LM, equip, rend, 2, eng); }
            //if(keyboard.isKeyPressed(input.key_interaction)) { interact(EM, player, input.key_interaction); }

            if(keyboard.isKeyPressed(input.key_unlockAll))  { unlockAll(equip.inventary); }
            if(keyboard.isKeyPressed(input.key_rldALLAmmo)) { reloadAll(EM, equip); }
            
            exit(eng);
            bb = { phy.x, phy.z, true, true , player.getID()};
        }
    );
}

bool InpSys2::update_menu(TheEngine& dev) {
    if(keyboard.isKeyPressed(XK_KP_Enter)) return false;
    exit(dev);

    return true;
}

bool InpSys2::update_pause(TheEngine& dev, bool pause) {
    if(keyboard.isKeyPressed(XK_KP_Space)) {
        keyboard.keyReleased(XK_KP_Space);
        if(!pause) dev.getDevice()->getCursorControl()->setVisible(true);
        else       dev.getDevice()->getCursorControl()->setVisible(false);

        return !pause;
    }
    exit(dev);

    return pause;
}

void InpSys2::exit(TheEngine& dev) {
    if(keyboard.isKeyPressed(XK_Escape)) dev.close();
}

bool InpSys2::OnEvent(const irr::SEvent& event) {
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
                checkPressed(event, XK_1);
                break;
            case irr::KEY_KEY_2:
                checkPressed(event, XK_2);
                break;
            case irr::KEY_KEY_3:
                checkPressed(event, XK_3);
                break;
            case irr::KEY_RETURN:
                checkPressed(event, XK_KP_Enter);
                break;
            case irr::KEY_SPACE:
                checkPressed(event, XK_KP_Space);
                break;
            case irr::KEY_ESCAPE:
                checkPressed(event, XK_Escape);
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

void InpSys2::checkPressed(const irr::SEvent& event, KeySym k) {
    if(event.KeyInput.PressedDown) { keyboard.keyPressed(k);  }
    else                           { keyboard.keyReleased(k); }
}

void InpSys2::movementMouse(TheEngine& eng, RenderCmp2& rend, PhysicsCmp2& phy) {
    auto centerWidth  = static_cast<irr::s32>(eng.getWidth() /2);
    auto centerHeight = static_cast<irr::s32>(eng.getHeight()/2);
    auto cursor       = eng.getDevice()->getCursorControl();
    auto ray_traced   = eng.getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates({ cursor->getPosition().X, cursor->getPosition().Y });
    auto angx = eng.getCamera()->getRotation().X * std::numbers::pi / 180;
    auto angy = eng.getCamera()->getRotation().Y * std::numbers::pi / 180;
    
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

void InpSys2::shoot(LevelMan& LM, Enty& player, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment) {
    int ammo = 0;
    double weaponCadence = 0;
    double reloadTimer = 0;
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
    
    if(ammo > 0) { 
        createBullet(LM, player, weaponCadence, eng, SS);
        LM.updateInterfaceMag(eng, ammo-1);
    }
    else if(ammo == 0) { reload(LM, eng, equipment); }

    if(equipment.equipada == 0 || equipment.equipada ==1){ mouse.releaseLeft(); }
}

void InpSys2::digonalMove(PhysicsCmp2& phy, float const speed, bool const up, bool const down) {
    phy.v_lin = speed;
    phy.v_ang = 90;
    if(up)        phy.v_ang = 45;
    else if(down) phy.v_ang = 135;
}

void InpSys2::reload(LevelMan& LM, TheEngine& dev, InventarioCmp& equipment) {
    auto& EM = LM.getEM();
    int currentAmmo = 0;
    switch (equipment.equipada) {
        case 0:
            reloadProcess(LM, dev, equipment, currentAmmo, equipment.ammo1, equipment.magazine1, 5);
        break;
        case 1:
            reloadProcess(LM, dev, equipment, currentAmmo, equipment.ammo2, equipment.magazine2, 2);
        break;
        case 2:
            reloadProcess(LM, dev, equipment, currentAmmo, equipment.ammo3, equipment.magazine3, 25);
        break;
        default: break;
    }
    soundWeapon(EM);
}

void InpSys2::changeWeapon(LevelMan& LM, InventarioCmp& p_invent, RenderCmp2& playerRender, int equip, TheEngine& eng) {
    int magazine {}, ammo{};
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
            playerRender.n = eng.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp");
            p_invent.clockReload = p_invent.clockReload1;
            if(p_invent.clockReload >= p_invent.reloadTime1) { notReloading(p_invent); }
            else { iAmReloading(p_invent); }
            magazine = p_invent.magazine1;
            ammo = p_invent.ammo1;
            break;

        case 1:
            playerRender.n = eng.createPlayer("assets/models/armas/escopeta.obj","assets/textures/fire.bmp");
            p_invent.clockReload = p_invent.clockReload2;
            if(p_invent.clockReload >= p_invent.reloadTime2) { notReloading(p_invent); }
            else { iAmReloading(p_invent); }
            magazine = p_invent.magazine2;
            ammo = p_invent.ammo2;
            break;

        case 2:
            playerRender.n = eng.createPlayer("assets/models/armas/subfusil.obj","assets/textures/fire.bmp");
            p_invent.clockReload = p_invent.clockReload3;
            if(p_invent.clockReload >= p_invent.reloadTime3) { notReloading(p_invent); }
            else { iAmReloading(p_invent); }
            magazine = p_invent.magazine3;
            ammo = p_invent.ammo3;
            break;

        default: break;
    }
    LM.updateInterfaceWhenReload(eng, magazine, ammo);
}

//void InpSys2::interact(EntyMan& EM, Enty& player, KeySym key) {
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

void InpSys2::unlockAll(size_t* invent) {
    for(int i=0; i<3; i++) {
        if(invent[i]!=2) invent[i]=1;
    }
}

void InpSys2::reloadAll(EntyMan& EM, InventarioCmp& equip) {
    equip.ammo1 = 20;
    equip.ammo2 = 10;
    equip.ammo3 = 100;
    soundWeapon(EM);
}

//void InpSys2::addKeyToInventary(EntyMan& EM, Enty& player) {
//    auto& inventay = EM.getComponent<InventarioCmp>(player);
//    inventay.keys_inv[0] = 1;
//}

//void InpSys2::openDoor(EntyMan& EM, Enty& player, Enty& door) {
//    auto& inventay = EM.getComponent<InventarioCmp>(player);
//    if(inventay.keys_inv[0]) {
//        //std::cout<<"Puerta abierta\n";
//        door.setDestroy();
//    }
//    else {
//        //std::cout<<"Puerta cerrada\n";
//    }
//}

void InpSys2::reloadProcess(LevelMan& LM, TheEngine& dev, InventarioCmp& p_invent, int currentAmmo, int& ammo, int& magazine, int maxAmmo) {
    currentAmmo = maxAmmo - magazine; //0 is magazine complete
    if((ammo-currentAmmo) > 0){
        ammo = ammo - currentAmmo;
        magazine = magazine + currentAmmo;
    }
    else {
        magazine = ammo;
        ammo = 0;
    }
    iAmReloading(p_invent);
    LM.updateInterfaceWhenReload(dev, magazine, ammo);
}

void InpSys2::createBullet(LevelMan& LM, Enty& player, double cadenciaWeapon, TheEngine& eng, SoundSystem_t& SS) {
    auto& EM = LM.getEM();
    auto& equipment  = EM.getComponent<InventarioCmp>(player);
    auto& phy_player = EM.getComponent<PhysicsCmp2>(player);
    //int ammo {};

    if(equipment.clockCadence <= cadenciaWeapon) { return; }
    //Cadencia alcanzada
    equipment.clockCadence = 0 ;

    if(equipment.equipada == 0){ //pistola
        LM.createBullet(phy_player, eng, SS, 18., 5., 0.1f, 9.);
        equipment.magazine1 -= 1;
        //ammo = equipment.magazine1;
    }
    else if (equipment.equipada == 1){ //escopeta
        LM.createShotgunBullets(phy_player, eng, SS, 8., 3., 0.15f, 0.4f, 10);
        equipment.magazine2 -= 1;
        //ammo = equipment.magazine1;
    }
    else if(equipment.equipada == 2){ //ametralladora
        LM.createBullet(phy_player, eng, SS, 15., 4., 0.1f, 1.5);
        equipment.magazine3 -= 1;
        //ammo = equipment.magazine1;
    }
    //return ammo;
    return;
}

void InpSys2::soundWeapon(EntyMan& EM) {
    for(auto& a : EM.getEntities()){
        if(a.hasTAG<TWeapon>() && a.hasCMP<SoundCmp>()) {
            auto& sound = EM.getComponent<SoundCmp>(a);
            EM.changeSound(sound, 1);
        }
    }
}