#pragma once
#include "../util/keyboard.hpp"
#include "../util/mouse.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include "soundsystem.hpp"
#include <cstdint>
#include <iostream>
#include <irrlicht/IEventReceiver.h>

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    using SYSCMP_Weapon = MP::Typelist<SoundCmp>;
    using SYSTAG_Weapon = MP::Typelist<TWeapon>;

    float angX = 0;
    float angY = 0;

    void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& SS) {
        auto& bb = EM.getBoard();
        auto cam   = eng.getCamera();
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& player, InputCmp2& i, RenderCmp2& r, PhysicsCmp2& p) {
                p.vx=p.vz=0;
                auto& equipment = EM.getComponent<InventarioCmp>(player);

                if(keyboard.isKeyPressed(i.key_up)){
                    p.vz = 0.1;
                    //std::cout<<cam->getAbsolutePosition().X<<" "<<cam->getAbsolutePosition().Y<<" "<<cam->getAbsolutePosition().Z<<"\n";
                    //std::cout<<r.n->getPosition().X<<" "<<r.n->getPosition().Y<<" "<<r.n->getPosition().Z<<"\n";
                    //std::cout<<r.n->getAbsolutePosition().X<<" "<<r.n->getAbsolutePosition().Y<<" "<<r.n->getAbsolutePosition().Z<<"\n";
                    //cam->setPosition({r.n->getAbsolutePosition().X, r.n->getAbsolutePosition().Y, r.n->getAbsolutePosition().Z});
                }
                if(keyboard.isKeyPressed(i.key_down)){
                    p.vz = -0.1;
                    //std::cout<<cam->getAbsolutePosition().X<<" "<<cam->getAbsolutePosition().Y<<" "<<cam->getAbsolutePosition().Z<<"\n";
                    //std::cout<<r.n->getPosition().X<<" "<<r.n->getPosition().Y<<" "<<r.n->getPosition().Z<<"\n";
                    //std::cout<<r.n->getAbsolutePosition().X<<" "<<r.n->getAbsolutePosition().Y<<" "<<r.n->getAbsolutePosition().Z<<"\n";
                    //cam->setPosition({r.n->getAbsolutePosition().X, r.n->getAbsolutePosition().Y, r.n->getAbsolutePosition().Z});
                }
                if(keyboard.isKeyPressed(i.key_right)){
                    p.vx = 0.1;
                    //std::cout<<cam->getAbsolutePosition().X<<" "<<cam->getAbsolutePosition().Y<<" "<<cam->getAbsolutePosition().Z<<"\n";
                    //std::cout<<r.n->getPosition().X<<" "<<r.n->getPosition().Y<<" "<<r.n->getPosition().Z<<"\n";
                    //std::cout<<r.n->getAbsolutePosition().X<<" "<<r.n->getAbsolutePosition().Y<<" "<<r.n->getAbsolutePosition().Z<<"\n";
                    //cam->setPosition({r.n->getAbsolutePosition().X, r.n->getAbsolutePosition().Y, r.n->getAbsolutePosition().Z});
                }
                if(keyboard.isKeyPressed(i.key_left)){
                    p.vx = -0.1;
                    //std::cout<<cam->getAbsolutePosition().X<<" "<<cam->getAbsolutePosition().Y<<" "<<cam->getAbsolutePosition().Z<<"\n";
                    //std::cout<<r.n->getPosition().X<<" "<<r.n->getPosition().Y<<" "<<r.n->getPosition().Z<<"\n";
                    //std::cout<<r.n->getAbsolutePosition().X<<" "<<r.n->getAbsolutePosition().Y<<" "<<r.n->getAbsolutePosition().Z<<"\n";
                    //cam->setPosition({r.n->getAbsolutePosition().X, r.n->getAbsolutePosition().Y, r.n->getAbsolutePosition().Z});
                }



                if(keyboard.isKeyPressed(i.key_shot)){
                    shoot(EM, player, r, eng, SS, equipment);
                    keyboard.keyReleased(i.key_shot);
                }

                if(keyboard.isKeyPressed(i.key_weapon1)) { changeWeapon(EM, player, 0); }

                if(keyboard.isKeyPressed(i.key_weapon2) && equipment.inventary[1] != 0) { changeWeapon(EM, player, 1); }

                if(keyboard.isKeyPressed(i.key_reloadALLAmmo)) { reload(EM, equipment); }

                if(keyboard.isKeyPressed(i.key_interaction)){
                    interact();
                    keyboard.keyReleased(i.key_interaction);
                }

                if(mouse.getMove()) {
                    movementMouse(eng, r);
                    //std::cout<<"Posicion relativa del jugador: "<<r.n->getPosition().X<<" "<<r.n->getPosition().Y<<" "<<r.n->getPosition().Z<<"\n";
                    //std::cout<<"Posicion absoluta del jugador: "<<r.n->getAbsolutePosition().X<<" "<<r.n->getAbsolutePosition().Y<<" "<<r.n->getAbsolutePosition().Z<<"\n";
                    //std::cout<<"Posicion relativa de la camara: "<<cam->getPosition().X<<" "<<cam->getPosition().Y<<" "<<cam->getPosition().Z<<"\n";
                    //std::cout<<"Posicion absoluta de la camara: "<<cam->getAbsolutePosition().X<<" "<<cam->getAbsolutePosition().Y<<" "<<cam->getAbsolutePosition().Z<<"\n";
                    //r.n->setRotation({0,static_cast<float>(ang++),0});
                    //std::cout<<r.n->getPosition().X<<" "<<r.n->getPosition().Y<<" "<<r.n->getPosition().Z<<"\n";
                }

                bb = { cam->getPosition().X, cam->getPosition().Z, true , true };


                //if(angX>-85){ angX-=1; }
                //angY+=1;
                //r.n->setRotation({ angX, angY, 0});
                //cam->setRotation({ angX, angY, 0});
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
                    irr::SEvent ev;
                    ev.KeyInput.PressedDown = true;
                    checkPressed(ev, XK_P);
                break;
                case irr::EMIE_MOUSE_MOVED:
                    //std::cout<<mouse.getMove()<<"\n";
                    mouse.moved();
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
    void interact() {
        std::cout<<"Interact\n";
    }

    //void movementKeyboard() {
    //
    //
    //}

    void movementMouse(TheEngine& eng, RenderCmp2& r) {
        auto centerWidth  = static_cast<irr::s32>(eng.getWidth()/2);
        auto centerHeight = static_cast<irr::s32>(eng.getHeight()/2);
        auto cursor           = eng.getDevice()->getCursorControl();
        auto ray_traced       = eng.getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates({ cursor->getPosition().X, cursor->getPosition().Y });

        eng.getCamera()->setTarget({ ray_traced.end.X, ray_traced.end.Y, ray_traced.end.Z });
        r.n->setRotation({ eng.getCamera()->getRotation().X, eng.getCamera()->getRotation().Y, 0 });
        cursor->setPosition(centerWidth, centerHeight);
        std::cout<<r.n->getPosition().X<<" "<<r.n->getPosition().Y<<" "<<r.n->getPosition().X<<"\n";
        mouse.quiet();
    }

    void shoot(EntyMan& EM, Enty& player, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS, InventarioCmp& equipment) {
        int ammo = 0;
        switch (equipment.equipada) {
            case 0:  ammo = equipment.ammo1; break;
            case 1:  ammo = equipment.ammo2; break;
            default: break;
        }
        if(ammo > 0) { createBullet(EM, player, ammo, r, eng, SS); }
    }

    void reload(EntyMan& EM, InventarioCmp& equipment) {
        equipment.ammo1 = 10;
        equipment.ammo2 = 5;
        EM.foreach<SYSCMP_Weapon, SYSTAG_Weapon>(
            [&](Enty& gun, SoundCmp& snd){
                EM.changeSound(snd, 1);
            }
        );
    }

    void createBullet(EntyMan& EM, Enty& player, int ammo, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS) {
        auto& inventary = EM.getComponent<InventarioCmp>(player);

        Enty& bullet = EM.createEntity();
        if(inventary.equipada == 0){ //pistol
            statsBullet(EM, bullet, ammo, 20.f, 0.8f, 0.1f);
            inventary.ammo1-=1;
        }
        else if (inventary.equipada == 1){ //escopeta
            statsBullet(EM, bullet, ammo, 50.f, 0.4f, 0.5f);
            inventary.ammo2-=1;
        }
        auto& bullet_stats = EM.getComponent<EstadisticaCmp>(bullet);
        EM.addComponent<PhysicsCmp2>(
            bullet, PhysicsCmp2{
                .x =r.n->getParent()->getPosition().X,
                .y =r.n->getParent()->getPosition().Y,
                .z =r.n->getParent()->getPosition().Z,
                .vx=  sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * bullet_stats.speed,
                .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * bullet_stats.speed,
                .vz=  cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * bullet_stats.speed
            }
        );
        EM.addComponent<RenderCmp2> (bullet, eng.createSphere(bullet_stats.bulletRad));
        EM.addComponent<EstadoCmp>  (bullet);
        EM.addComponent<SoundCmp>   (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
        EM.addComponent<SelfDestCmp>(bullet);
        EM.addTag      <TBullet>    (bullet);
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

    static void onkeypressed(KeySym k) {
        keyboard.keyPressed(k);
    }

    static void onkeyreleased(KeySym k) {
        keyboard.keyReleased(k);
    }

    Mouse mouse {};
    inline static Keyboard keyboard {};
};