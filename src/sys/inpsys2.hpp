#pragma once
#include "../util/keyboard.hpp"
#include "../util/mouse.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include <iostream>
#include <irrlicht/IEventReceiver.h>

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    using SYSCMP_Weapon = MP::Typelist<SoundCmp>;
    using SYSTAG_Weapon = MP::Typelist<TWeapon>;

    void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& SS, double const dt) {
        auto& bb = EM.getBoard();
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& player, InputCmp2& i, RenderCmp2& r, PhysicsCmp2& p) {
                auto& equipment = EM.getComponent<InventarioCmp> (player);
                auto& stats     = EM.getComponent<EstadisticaCmp>(player);
               
                double reloadTimer = 0;
                bool arriba = false;
                bool abajo  = false;

                if(equipment.reloading == 1){
                    
                    equipment.clockReload += dt; 
                    //std::cout<< "RELOJES ARMAS: Pistola: " << equipment.clockReload1 << " .Escopeta: "<<
                    //equipment.clockReload2 << " .Ametralladora: "<< equipment.clockReload3 << "ACTUAL:" << equipment.clockReload<<"\n";
                }
                equipment.clockCadence += dt;
                p.v_lin = p.v_ang = 0;
                
                movementMouse(player, eng, r, p);
                if(keyboard.isKeyPressed(i.key_up))    { p.v_lin =  stats.speed; arriba = true;}
                if(keyboard.isKeyPressed(i.key_down))  { p.v_lin = -stats.speed; abajo  = true;}
                if(keyboard.isKeyPressed(i.key_right)) { 
                    p.v_lin = stats.speed; 
                    if(arriba){ 
                        p.v_ang = 45;
                    } 
                    else if(abajo){
                        p.v_ang = -45; 
                        p.v_lin = -stats.speed;
                    }
                    else{
                        p.v_ang = 90;
                    }
                }
                if(keyboard.isKeyPressed(i.key_left)) { 
                    p.v_lin = -stats.speed; 
                    if(arriba){ 
                        p.v_ang = -45; 
                        p.v_lin =  stats.speed;
                    } 
                    else if(abajo){
                        p.v_ang = 45;
                    }
                    else {
                        p.v_ang = 90;
                    }
                }

                if(mouse.isLeftPressed()) { shoot(EM, player, r, eng, SS, equipment, reloadTimer, dt); }
                if(keyboard.isKeyPressed(i.key_weapon1)) { changeWeapon(EM, player, 0, eng); }
                if(keyboard.isKeyPressed(i.key_weapon2) && equipment.inventary[1] != 0) { changeWeapon(EM, player, 1, eng); }
                if(keyboard.isKeyPressed(i.key_weapon3) && equipment.inventary[2] != 0) { changeWeapon(EM, player, 2, eng); }

                if(keyboard.isKeyPressed(i.key_unlockAll)){
                    for(int i=0;i<3;i++){
                        if(equipment.inventary[i]!=2){
                            equipment.inventary[i]=1;
                        }
                    }
                }
                if(keyboard.isKeyPressed(i.key_reloadALLAmmo)) {
                    equipment.ammo1 = 20;
                    equipment.ammo2 = 10;
                    equipment.ammo3 = 100;
                    for(auto& a : EM.getEntities()){
                        if(a.hasTAG<TWeapon>()){
                            EM.getComponent<SoundCmp>(a).parametro=1;
                            EM.getComponent<SoundCmp>(a).cambia=true;
                            EM.getComponent<SoundCmp>(a).play=true;
                        }
                    }
                }
                if(keyboard.isKeyPressed(i.key_reloadCurrentAmmo)) { reload(EM, player, equipment);}

                if(keyboard.isKeyPressed(i.key_interaction)){
                    interact(EM, player);
                    keyboard.keyReleased(i.key_interaction);
                }

                bb = { p.x, p.z, true, true , player.getID()};
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
    void interact(EntyMan& EM, Enty& player) {
        auto& col = EM.getComponent<EstadoCmp>(player);
        
        if(col.colision != 0){
            auto& col_entity = EM.getEntityById(col.entityCol);
            if(col_entity.hasTAG<TWeapon>()){
                std::cout<<"Recoger arma\n";
            }
            else if(col_entity.hasTAG<TDoor>()) {
                std::cout<<"Abrir puerta\n";
                openDoor(EM, player, col_entity);
            }
            else if(col_entity.hasTAG<TKey>()) {
                std::cout<<"Recoger llave\n";
                addKeyToInventary(EM, player);
                col_entity.setDestroy();
            }
        }
    }

    void addKeyToInventary(EntyMan& EM, Enty& player) {
        auto& inventay = EM.getComponent<InventarioCmp>(player);
        inventay.keys_inv[0] = 1;
        std::cout<<"Llave guardada\n";
    }

    void openDoor(EntyMan& EM, Enty& player, Enty& door) {
        auto& inventay = EM.getComponent<InventarioCmp>(player);
        if(inventay.keys_inv[0]) {
            std::cout<<"Puerta abierta\n";
            door.setDestroy();
        }
        else {
            std::cout<<"Puerta cerrada\n";
        }
    }

    void movementMouse(Enty& player, TheEngine& eng, RenderCmp2& r, PhysicsCmp2& p) {
        auto centerWidth  = static_cast<irr::s32>(eng.getWidth()/2);
        auto centerHeight = static_cast<irr::s32>(eng.getHeight()/2);
        auto cursor       = eng.getDevice()->getCursorControl();
        auto ray_traced   = eng.getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates({ cursor->getPosition().X, cursor->getPosition().Y });
        auto angy = eng.getCamera()->getRotation().Y * std::numbers::pi / 180;
        auto angx = eng.getCamera()->getRotation().X * std::numbers::pi / 180;

        eng.getCamera()->setTarget({ ray_traced.end.X, ray_traced.end.Y, ray_traced.end.Z });
        r.n->setRotation({
            eng.getCamera()->getRotation().X, 
            eng.getCamera()->getRotation().Y, 
            0
        });
        cursor->setPosition(centerWidth, centerHeight);

        p.orieny = angy;
        p.orienx = angx;
    }

    void shoot(EntyMan& EM, Enty& player, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment, double reloadTimer, double dt) {
        
        int ammo = 0;
        double weaponCadence = 0;
        size_t weapon = 0;
        switch (equipment.equipada) {
            case 0: ammo = equipment.magazine1;
                    reloadTimer = equipment.reloadTime1;
                    
            break;
            case 1: ammo = equipment.magazine2;
                    reloadTimer = equipment.reloadTime2;
                    
            break;
            case 2: ammo = equipment.magazine3;
                    weaponCadence = equipment.cadenceWeapon3;
                    reloadTimer = equipment.reloadTime3;
                    
            break;
            default: break;
        }
        //std::cout<<"Intento disparar RELOAD ES: " << reloadTimer << " y mi arma es: "<<equipment.equipada<<" CON RELOJ: " << equipment.clockReload <<
        //"ESTOY CON LA RECARGA EN: "<<equipment.reloading<< "\n";
        
        if(equipment.reloading == 1 && equipment.clockReload <= reloadTimer){ return; }
        equipment.clockReload = 0;
        notReloading(EM, player);
        
        if(ammo > 0) { 
            //std::cout<<"Disparo\n";
            createBullet(EM, player, ammo, weaponCadence, r, eng, SS, dt); }
        else if(ammo == 0){
            
            reload(EM, player, equipment);
        }
        if(equipment.equipada == 0 || equipment.equipada ==1){ mouse.releaseLeft(); }
    }

    void reload(EntyMan& EM, Enty& player, InventarioCmp& equipment) {
        int currentAmmo = 0;
        
        switch (equipment.equipada) {
            case 0:
                reloadProcess(EM, player, currentAmmo, equipment.ammo1, equipment.magazine1, 5);
                
            break;
            case 1:
                reloadProcess(EM, player, currentAmmo, equipment.ammo2, equipment.magazine2, 2);
            break;
            case 2:
                reloadProcess(EM, player, currentAmmo, equipment.ammo3, equipment.magazine3, 25);
            break;
            default: break;
        }
        for(auto& a : EM.getEntities()){
            if(a.hasTAG<TWeapon>()){
                EM.getComponent<SoundCmp>(a).parametro=1;
                EM.getComponent<SoundCmp>(a).cambia=true;
                EM.getComponent<SoundCmp>(a).play=true;
            }
        }
        
    }

    void reloadProcess(EntyMan& EM, Enty& player, int currentAmmo, int& ammo, int& magazine, int maxAmmo) {
        currentAmmo = maxAmmo - magazine; //0 is magazine complete
        if((ammo-currentAmmo) > 0){
            ammo = ammo-currentAmmo;
            magazine = magazine + currentAmmo;
            iAmReloading(EM, player);
        }
        else{
            ammo = 0;
            magazine = ammo;
            iAmReloading(EM, player);
        }
        
        
    }

    void iAmReloading(EntyMan& EM, Enty& player){ EM.getComponent<InventarioCmp>(player).reloading = 1; }
    void notReloading(EntyMan& EM, Enty& player){ EM.getComponent<InventarioCmp>(player).reloading = 0; }

    void createBullet(EntyMan& EM, Enty& player, int ammo, double cadenciaWeapon, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS, double const dt) {
        auto& equipment = EM.getComponent<InventarioCmp>(player);
        if(equipment.clockCadence <= cadenciaWeapon){ return; }
        //Cadencia alcanzada
        equipment.clockCadence = 0 ;

        if(equipment.equipada == 0){ //pistol
            Enty& bullet = EM.createEntity();
            statsBullet(EM, bullet, ammo, 18.f, 5.f, 0.1f);
            auto speed = EM.getComponent<EstadisticaCmp>(bullet).speed;
            EM.addComponent<PhysicsCmp2>(
            bullet, PhysicsCmp2{
                    .x =EM.getComponent<PhysicsCmp2>(player).x,
                    .y =EM.getComponent<PhysicsCmp2>(player).y,
                    .z =EM.getComponent<PhysicsCmp2>(player).z,
                    .vx=  sin(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                    .vy= -sin(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                    .vz=  cos(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed
                }
            );
            EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
            EM.addComponent<EstadoCmp>  (bullet);
            EM.addComponent<SoundCmp>   (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
            EM.addComponent<SelfDestCmp>(bullet, 9.);
            EM.addTag<TBullet>          (bullet);
            EM.addTag<TInteract>        (bullet);
            equipment.magazine1 -= 1;
        }
        else if (EM.getComponent<InventarioCmp>(player).equipada == 1){ //escopeta
            for(float i=-0.4;i<0.5;i+=0.2){
                Enty& bullet = EM.createEntity();
                statsBullet(EM, bullet, ammo, 8.f, 4.f, 0.15f);
                auto speed = EM.getComponent<EstadisticaCmp>(bullet).speed;
            
                EM.addComponent<PhysicsCmp2>(
                bullet, PhysicsCmp2{
                        .x =EM.getComponent<PhysicsCmp2>(player).x+(i * cos(EM.getComponent<PhysicsCmp2>(player).orieny)),
                        .y =EM.getComponent<PhysicsCmp2>(player).y ,
                        .z =EM.getComponent<PhysicsCmp2>(player).z+(i * -sin(EM.getComponent<PhysicsCmp2>(player).orieny)),
                        .vx=  sin(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                        .vy= -sin(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                        .vz=  cos(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed
                    }
                );
                
                EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
                EM.addComponent<EstadoCmp>  (bullet);
                EM.addComponent<SoundCmp>   (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
                EM.addComponent<SelfDestCmp>(bullet, 0.4f);
                EM.addTag      <TBullet>    (bullet);
                EM.addTag<TInteract>        (bullet);
                

                if(i>-0.4 && i<0.4){
                    Enty& bullet2 = EM.createEntity();
                    statsBullet(EM, bullet2, ammo, 8.f, 4.f, 0.15f);
                    EM.addComponent<PhysicsCmp2>(
                    bullet2, PhysicsCmp2{
                            .x =EM.getComponent<PhysicsCmp2>(player).x+(i*cos(EM.getComponent<PhysicsCmp2>(player).orieny)),
                            .y =EM.getComponent<PhysicsCmp2>(player).y+(1*0.2),
                            .z =EM.getComponent<PhysicsCmp2>(player).z+(i *-sin(EM.getComponent<PhysicsCmp2>(player).orieny)),
                            .vx=  sin(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                            .vy= -sin(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                            .vz=  cos(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed
                        }
                    );
                    EM.addComponent<RenderCmp2> (bullet2, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
                    EM.addComponent<EstadoCmp>  (bullet2);
                    EM.addComponent<SoundCmp>   (bullet2, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
                    EM.addComponent<SelfDestCmp>(bullet2, 0.4f);
                    EM.addTag      <TBullet>    (bullet2);
                    EM.addTag      <TInteract>        (bullet2);
                    
                }
                Enty& bullet3 = EM.createEntity();
                statsBullet(EM, bullet3, ammo, 8.f, 4.f, 0.15f);
                EM.addComponent<PhysicsCmp2>(
                bullet3, PhysicsCmp2{
                        .x =EM.getComponent<PhysicsCmp2>(player).x+(i*cos(EM.getComponent<PhysicsCmp2>(player).orieny)),
                        .y =EM.getComponent<PhysicsCmp2>(player).y+(2*0.2),
                        .z =EM.getComponent<PhysicsCmp2>(player).z+(i * -sin(EM.getComponent<PhysicsCmp2>(player).orieny)),
                        .vx=  sin(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                        .vy= -sin(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                        .vz=  cos(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed
                    }
                );
                EM.addComponent<RenderCmp2> (bullet3, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
                EM.addComponent<EstadoCmp>  (bullet3);
                EM.addComponent<SoundCmp>   (bullet3, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
                EM.addComponent<SelfDestCmp>(bullet3, 0.4);
                EM.addTag      <TBullet>    (bullet3);
                EM.addTag<TInteract>        (bullet3);
                
            }
            equipment.magazine2 -= 1;
        }

        else if(EM.getComponent<InventarioCmp>(player).equipada == 2){ //ametralladora
            Enty& bullet = EM.createEntity();
            statsBullet(EM, bullet, ammo, 15.f, 4.0f, 0.1f);
            auto speed = EM.getComponent<EstadisticaCmp>(bullet).speed;
            EM.addComponent<PhysicsCmp2>(
            bullet, PhysicsCmp2{
                    .x =EM.getComponent<PhysicsCmp2>(player).x,
                    .y =EM.getComponent<PhysicsCmp2>(player).y,
                    .z =EM.getComponent<PhysicsCmp2>(player).z,
                    .vx=  sin(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                    .vy= -sin(EM.getComponent<PhysicsCmp2>(player).orienx) * speed,
                    .vz=  cos(EM.getComponent<PhysicsCmp2>(player).orieny) * cos(EM.getComponent<PhysicsCmp2>(player).orienx) * speed
                }
            );
            EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
            EM.addComponent<EstadoCmp>  (bullet);
            EM.addComponent<SoundCmp>   (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
            EM.addComponent<SelfDestCmp>(bullet, 1.5f);
            EM.addTag      <TBullet>    (bullet);
            EM.addTag<TInteract>        (bullet);
            equipment.magazine3 -= 1;
        }
    }

    void changeWeapon(EntyMan& EM, Enty& player, size_t equip, TheEngine& eng) {
        auto& p_invent = EM.getComponent<InventarioCmp>(player);
        auto& playerRender = EM.getComponent<RenderCmp2>(player);
        playerRender.n->remove();
        
        switch (p_invent.equipada) {
            
            case 0:
                if(p_invent.reloading == 1){
                    p_invent.clockReload1 = p_invent.clockReload;
                }
                
            break;

            case 1:
                 if(p_invent.reloading == 1){
                    p_invent.clockReload2 = p_invent.clockReload;
                }
                
            break;

            case 2:
                 if(p_invent.reloading == 1){
                    p_invent.clockReload3 = p_invent.clockReload;
                }
            break;

            default:
            break;
        }
        
        p_invent.inventary[p_invent.equipada] = 1;
        p_invent.equipada = equip;
        p_invent.inventary[equip] = 2;
        

        switch (p_invent.equipada) {
            
            case 0:
            
                playerRender.n=eng.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp");
                p_invent.clockReload = p_invent.clockReload1;
                if(p_invent.clockReload >= p_invent.reloadTime1){
                    
                    notReloading(EM, player);
                }
                else{
                    
                    iAmReloading(EM, player);
                }
                
            break;

            case 1:
                
                playerRender.n=eng.createPlayer("assets/models/armas/escopeta.obj","assets/textures/fire.bmp");
                p_invent.clockReload = p_invent.clockReload2;
                if(p_invent.clockReload >= p_invent.reloadTime2){
                    notReloading(EM, player);
                }
                else{
                    
                    iAmReloading(EM,player);
                }
                
            break;

            case 2:
                playerRender.n=eng.createPlayer("assets/models/armas/subfusil.obj","assets/textures/fire.bmp");
                p_invent.clockReload = p_invent.clockReload3;
                if(p_invent.clockReload >= p_invent.reloadTime3){
                    notReloading(EM, player);
                }
                else{
                    iAmReloading(EM, player);
                }
                
            break;

            default:
            break;
        
        }
        //std::cout<< "CAMBIO ARMA RELOJES ARMAS: Pistola: " << p_invent.clockReload1 << " .Escopeta: "<<
        //p_invent.clockReload2 << " .Ametralladora: "<< p_invent.clockReload3 << "ACTUAL:" << p_invent.clockReload<<"\n";
    }

    void statsBullet(EntyMan& EM, Enty& bullet, int ammo, float dmg, float spd, float rad) {
        EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{ .damage = dmg, .speed = spd, .bulletRad = rad });
        ammo-=1;
    } 

    static void onkeypressed(KeySym k)  { keyboard.keyPressed(k);  }
    static void onkeyreleased(KeySym k) { keyboard.keyReleased(k); }

    inline static Keyboard keyboard {};
    inline static Mouse mouse {};
};