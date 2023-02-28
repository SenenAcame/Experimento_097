#pragma once
#include "../util/keyboard.hpp"
#include "../util/mouse.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    using SYSCMP_Weapon = MP::Typelist<SoundCmp>;
    using SYSTAG_Weapon = MP::Typelist<TWeapon>;

    void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& SS, double const dt) {
        auto& bb = EM.getBoard();
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& player, InputCmp2& i, RenderCmp2& r, PhysicsCmp2& p) {

                movementMouse(player, eng, r, p);
                auto& equipment = EM.getComponent<InventarioCmp>(player);
                double reloadTimer = 0;

                EM.getComponent<InventarioCmp>(player).clockCadence += dt;

                p.v_lin = p.v_ang = 0;
                bool arriba=false;
                bool abajo=false;

                if(keyboard.isKeyPressed(i.key_up))    { p.v_lin =  1; arriba=true;}
                if(keyboard.isKeyPressed(i.key_down))  { p.v_lin = -1; abajo=true;}
                if(keyboard.isKeyPressed(i.key_right)) { p.v_lin =  1; if(arriba){ p.v_ang =45;} else if(abajo){p.v_ang =-45; p.v_lin =  -1;}else{p.v_ang =  90;} }
                if(keyboard.isKeyPressed(i.key_left))  { p.v_lin = -1; if(arriba){ p.v_ang =-45; p.v_lin =  1;} else if(abajo){p.v_ang =45;}else{p.v_ang =  90;} }
                
                if(keyboard.isKeyPressed(i.key_shot)){;
                    int ammo = 0;
                    double weaponCadence = 0;
                    size_t weapon = 0;
                    switch (EM.getComponent<InventarioCmp>(player).equipada) {
                        case 0: ammo = EM.getComponent<InventarioCmp>(player).magazine1;
                                reloadTimer = EM.getComponent<InventarioCmp>(player).reloadTime1;
                        break;
                        case 1: ammo = EM.getComponent<InventarioCmp>(player).magazine2;
                                reloadTimer = EM.getComponent<InventarioCmp>(player).reloadTime2;
                        break;
                        case 2: ammo = EM.getComponent<InventarioCmp>(player).magazine3;
                                weaponCadence = EM.getComponent<InventarioCmp>(player).cadenceWeapon3;
                                reloadTimer = EM.getComponent<InventarioCmp>(player).reloadTime3;
                        break;
                        default: break;
                    }

                    if(EM.getComponent<InventarioCmp>(player).reloading ==1 && EM.getComponent<InventarioCmp>(player).clockReload <= reloadTimer){
                        EM.getComponent<InventarioCmp>(player).clockReload += dt;
                        return;
                    }

                    notReloading(EM, player);
                    
                    if(ammo > 0) { 
                        createBullet(EM, player, ammo, weaponCadence, r, eng, SS, dt);
                    }
                    if(EM.getComponent<InventarioCmp>(player).equipada == 0 || EM.getComponent<InventarioCmp>(player).equipada ==1){
                        keyboard.keyReleased(i.key_shot);
                    }
                }
                
                if(keyboard.isKeyPressed(i.key_weapon1)) { changeWeapon(EM, player, 0); }
                if(keyboard.isKeyPressed(i.key_weapon2) && EM.getComponent<InventarioCmp>(player).inventary[1] != 0) { changeWeapon(EM, player, 1); }
                if(keyboard.isKeyPressed(i.key_weapon3) && EM.getComponent<InventarioCmp>(player).inventary[2] != 0) { changeWeapon(EM, player, 2); }

                if(keyboard.isKeyPressed(i.key_unlockAll)){
                    for(int i=0;i<3;i++){
                        if(EM.getComponent<InventarioCmp>(player).inventary[i]!=2){
                            EM.getComponent<InventarioCmp>(player).inventary[i]=1;
                        }
                    }
                }
                if(keyboard.isKeyPressed(i.key_reloadALLAmmo)) {
                    EM.getComponent<InventarioCmp>(player).ammo1 = 20;
                    EM.getComponent<InventarioCmp>(player).ammo2 = 10;
                    EM.getComponent<InventarioCmp>(player).ammo3 = 100;
                    for(auto& a : EM.getEntities()){
                        if(a.hasTAG<TWeapon>()){
                            EM.getComponent<SoundCmp>(a).parametro=1;
                            EM.getComponent<SoundCmp>(a).cambia=true;
                            EM.getComponent<SoundCmp>(a).play=true;
                        }
                    }
                }
                if(keyboard.isKeyPressed(i.key_reloadCurrentAmmo)) {
                    InventarioCmp& ammos = EM.getComponent<InventarioCmp>(player);
                    int currentAmmo=0;
                    switch (ammos.equipada) {
                        case 0:
                            currentAmmo = 5-ammos.magazine1; //0 is magazine complete
                            
                            if((ammos.ammo1-currentAmmo)>0){
                                ammos.ammo1 = ammos.ammo1-currentAmmo;
                                ammos.magazine1=ammos.magazine1 + currentAmmo;
                                iAmReloading(EM, player);
                            }
                            else{
                                ammos.ammo1 = 0;
                                ammos.magazine1=ammos.ammo1;
                                iAmReloading(EM, player);
                            }
                        break;
                        case 1:
                            currentAmmo = 2-ammos.magazine2; //0 is magazine complete
                            
                            if((ammos.ammo2-currentAmmo)>0){
                                ammos.ammo2 = ammos.ammo2-currentAmmo;
                                ammos.magazine2=ammos.magazine2 + currentAmmo;
                                iAmReloading(EM, player);
                            }
                            else{
                                ammos.ammo2 = 0;
                                ammos.magazine2=ammos.ammo2;
                                iAmReloading(EM, player);
                            }
                        break;

                        case 2:
                            currentAmmo = 25-ammos.magazine3; //0 is magazine complete
                            
                            if((ammos.ammo3-currentAmmo)>0){
                                ammos.ammo3 = ammos.ammo3-currentAmmo;
                                ammos.magazine3=ammos.magazine3 + currentAmmo;
                                iAmReloading(EM, player);
                            }
                            else{
                                ammos.ammo3 = 0;
                                ammos.magazine3=ammos.ammo3;
                                iAmReloading(EM, player);
                            }
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

                if(keyboard.isKeyPressed(i.key_interaction)){
                    interact(EM, player);
                    keyboard.keyReleased(i.key_interaction);
                }

                

                bb = { p.x, p.z, true , true };
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
                    irr::SEvent ev;
                    ev.KeyInput.PressedDown = true;
                    checkPressed(ev, XK_P);
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
        auto& col_entity = EM.getEntityById(col.entityCol);

        if(col.colision != 0 && (col_entity.hasTAG<TWeapon>() || col_entity.hasTAG<TDoor>())){
            col_entity.setDestroy();
        }
    }

    void movementMouse(Enty& player, TheEngine& eng, RenderCmp2& r, PhysicsCmp2& p) {
        auto centerWidth  = static_cast<irr::s32>(eng.getWidth()/2);
        auto centerHeight = static_cast<irr::s32>(eng.getHeight()/2);
        auto cursor           = eng.getDevice()->getCursorControl();
        auto ray_traced       = eng.getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates({ cursor->getPosition().X, cursor->getPosition().Y });
        eng.getCamera()->setTarget({ ray_traced.end.X, ray_traced.end.Y, ray_traced.end.Z });
        r.n->setRotation({
            eng.getCamera()->getRotation().X, 
            eng.getCamera()->getRotation().Y, 
            0
        });
        cursor->setPosition(centerWidth, centerHeight);

        auto ang = eng.getCamera()->getRotation().Y * std::numbers::pi / 180;
        auto angx = eng.getCamera()->getRotation().X * std::numbers::pi / 180;
        p.orieny = ang;
        p.orienx = angx;
    }

    //void shoot(EntyMan& EM, Enty& player, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment) {
    //    int ammo = 0;
    //    switch (equipment.equipada) {
    //        case 0:  ammo = equipment.ammo1; break;
    //        case 1:  ammo = equipment.ammo2; break;
    //        default: break;
    //    }
    //    if(ammo > 0) { createBullet(EM, player, ammo, r, eng, SS); }
    //}

    void reload(EntyMan& EM, InventarioCmp& equipment) {
        equipment.ammo1 = 10;
        equipment.ammo2 = 5;
        EM.foreach<SYSCMP_Weapon, SYSTAG_Weapon>(
            [&](Enty& gun, SoundCmp& snd){
                EM.changeSound(snd, 1);
            }
        );
    }

    void iAmReloading(EntyMan& EM, Enty& player){
        EM.getComponent<InventarioCmp>(player).reloading=1;  
    }

    void notReloading(EntyMan& EM, Enty& player){
        EM.getComponent<InventarioCmp>(player).reloading=0;
    }

    void createBullet(EntyMan& EM, Enty& player, int ammo, double cadenciaWeapon, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS, double const dt) {
        if(EM.getComponent<InventarioCmp>(player).clockCadence <= cadenciaWeapon){
            return;
        }
        //Cadencia alcanzada
        EM.getComponent<InventarioCmp>(player).clockCadence =0 ;

        if(EM.getComponent<InventarioCmp>(player).equipada == 0){ //pistol
            Enty& bullet = EM.createEntity();
            statsBullet(EM, bullet, ammo, 20.f, 0.8f, 0.1f);
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
            EM.addComponent<SelfDestCmp>(bullet,SelfDestCmp{.cooldown=10});
            EM.addTag<TBullet>(bullet);
            EM.getComponent<InventarioCmp>(player).magazine1-=1;
        }
        else if (EM.getComponent<InventarioCmp>(player).equipada == 1){ //escopeta
        
            for(float i=-0.4;i<0.5;i+=0.2){
                Enty& bullet = EM.createEntity();
                statsBullet(EM, bullet, ammo, 50.f, 0.8f, 0.1f);
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
                EM.addComponent<SelfDestCmp>(bullet, SelfDestCmp{.cooldown=0.4f});
                EM.addTag<TBullet>(bullet);
                

                if(i>-0.4 && i<0.4){
                    Enty& bullet2 = EM.createEntity();
                    statsBullet(EM, bullet2, ammo, 50.f, 0.8f, 0.1f);
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
                    EM.addComponent<SelfDestCmp>(bullet2, SelfDestCmp{.cooldown=0.4f});
                    EM.addTag<TBullet>(bullet2);
                    
                }
                Enty& bullet3 = EM.createEntity();
                statsBullet(EM, bullet3, ammo, 50.f, 0.8f, 0.1f);
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
                EM.addComponent<SelfDestCmp>(bullet3, SelfDestCmp{.cooldown=0.4f});
                EM.addTag<TBullet>(bullet3);
                
            }
            EM.getComponent<InventarioCmp>(player).magazine2-=1;
        }

        else if(EM.getComponent<InventarioCmp>(player).equipada == 2){ //ametralladora
            Enty& bullet = EM.createEntity();
            statsBullet(EM, bullet, ammo, 20.f, 1.0f, 0.5f);
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
            EM.addComponent<SelfDestCmp>(bullet);
            EM.addTag<TBullet>(bullet);
            EM.getComponent<InventarioCmp>(player).magazine3-=1;
        }
    }

    void changeWeapon(EntyMan& EM, Enty& player, size_t equip) {
        auto& p_invent = EM.getComponent<InventarioCmp>(player);
        p_invent.inventary[p_invent.equipada] = 1;
        p_invent.equipada = equip;
        p_invent.inventary[equip] = 2;
    }

    void statsBullet(EntyMan& EM, Enty& bullet, int ammo, float dmg, float spd, float rad) {
        EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{ .damage = dmg, .speed = spd, .bulletRad = rad });
        ammo-=1;
    } 

    static void onkeypressed(KeySym k)  { keyboard.keyPressed(k);  }
    static void onkeyreleased(KeySym k) { keyboard.keyReleased(k); }

    inline static Keyboard keyboard {};
};