#pragma once
#include "../util/keyboard.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include "soundsystem.hpp"

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& SS) {
        auto& bb = EM.getBoard();
        auto cam   = eng.getCamera();
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& player, InputCmp2& i, RenderCmp2& r) {
                if(keyboard.isKeyPressed(i.key_shot)){
                    //cambiar por funcion de disparo en funcion de inventario array y el modelo arma
                    //std::cout<<"Arma equipada: " <<EM.getComponent<InventarioCmp>(player).equipada<<
                    //"\n";
                    int ammo = 0;
                    switch (EM.getComponent<InventarioCmp>(player).equipada) {
                        case 0:  ammo = EM.getComponent<InventarioCmp>(player).ammo1; break;
                        case 1:  ammo = EM.getComponent<InventarioCmp>(player).ammo2; break;
                        default: break;
                    }
                    if(ammo > 0) { createBullet(EM, player, ammo, r, eng, SS); }
                    keyboard.keyReleased(i.key_shot);
                }
                if(keyboard.isKeyPressed(i.key_weapon1)) { changeWeapon(EM, player, 0); }
                if(keyboard.isKeyPressed(i.key_weapon2) && EM.getComponent<InventarioCmp>(player).inventary[1] != 0) { changeWeapon(EM, player, 1); }
                if(keyboard.isKeyPressed(i.key_reloadALLAmmo)) {
                    EM.getComponent<InventarioCmp>(player).ammo1 = 10;
                    EM.getComponent<InventarioCmp>(player).ammo2 = 5;
                    for(auto& a : EM.getEntities()){
                        if(a.hasTAG<TWeapon>()){
                            EM.getComponent<SoundCmp>(a).parametro=1;
                            EM.getComponent<SoundCmp>(a).cambia=true;
                            EM.getComponent<SoundCmp>(a).play=true;
                        }
                    }
                }
                bb = { cam->getPosition().X, cam->getPosition().Z, true , true };
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
                case irr::KEY_KEY_B:
                    checkPressed(event, XK_B);
                    break; 
                case irr::KEY_KEY_N:
                    checkPressed(event, XK_N);
                    break; 
                case irr::KEY_KEY_M:
                    checkPressed(event, XK_M);
                    break; 
                case irr::KEY_KEY_P:
                    checkPressed(event, XK_P);
                    break;
                case irr::KEY_KEY_R:
                    checkPressed(event, XK_R);
                    break;
                case irr::KEY_KEY_1:
                    checkPressed(event,XK_1);
                    break;
                    case irr::KEY_KEY_2:
                    checkPressed(event,XK_2);
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
                    irr::SEvent ev ;
                    ev.KeyInput.PressedDown = true;
                    checkPressed( ev, XK_P);
                break;
                default: break;
            }
        }
        return false;
    }

    void checkPressed(const irr::SEvent& event, KeySym k) {
        if(event.KeyInput.PressedDown){
            keyboard.keyPressed(k);
        }
        else{
            keyboard.keyReleased(k);
        }
    }

private:
    void createBullet(EntyMan& EM, Enty& player, int ammo, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS) {
        Enty& bullet = EM.createEntity();
        if(EM.getComponent<InventarioCmp>(player).equipada == 0){ //pistol
            statsBullet(EM, bullet, ammo, 20.f, 0.8f, 0.1f);
            EM.getComponent<InventarioCmp>(player).ammo1-=1;
        }
        else if (EM.getComponent<InventarioCmp>(player).equipada == 1){ //escopeta
            statsBullet(EM, bullet, ammo, 50.f, 0.4f, 0.5f);
            EM.getComponent<InventarioCmp>(player).ammo2-=1;
        }
        auto speed = EM.getComponent<EstadisticaCmp>(bullet).speed;
        EM.addComponent<PhysicsCmp2>(
            bullet, PhysicsCmp2{
                .x =r.n->getParent()->getPosition().X,
                .y =r.n->getParent()->getPosition().Y,
                .z =r.n->getParent()->getPosition().Z,
                .vx=  sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * speed,
                .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * speed,
                .vz=  cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * speed
            }
        );
        EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
        EM.addComponent<EstadoCmp>  (bullet);
        EM.addComponent<SoundCmp>  (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
        EM.addComponent<SelfDestCmp>(bullet);
        EM.addTag<TBullet>(bullet);
        
    }

    void changeWeapon(EntyMan& EM, Enty& player, size_t equip) {
        EM.getComponent<InventarioCmp>(player).inventary[EM.getComponent<InventarioCmp>(player).equipada] = 1;
        EM.getComponent<InventarioCmp>(player).equipada = equip;
        EM.getComponent<InventarioCmp>(player).inventary[equip] = 2;
    }

    void statsBullet(EntyMan& EM, Enty& bullet, int ammo, float dmg, float spd, float rad) {
        EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{ .damage = dmg, .speed = spd, .bulletRad = rad });
        ammo-=1;
    } 

    static void onkeypressed(KeySym k) {
        keyboard.keyPressed(k);
    }

    static void onkeyreleased(KeySym k) {
        keyboard.keyReleased(k);
    }

    inline static Keyboard keyboard {};
};