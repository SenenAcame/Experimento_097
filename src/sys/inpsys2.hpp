#pragma once
#include "../util/keyboard.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include <cmath>
#include <iostream>

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& eng) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty&, InputCmp2& i, RenderCmp2& r) {
                if(keyboard.isKeyPressed(i.key_shot)){
                    //cambiar por funcion de disparo en funcion de inventario array y el modelo arma
                    Enty& bullet = EM.createEntity();
                    EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{.damage=50.f, .speed=0.4f});
                    EM.addComponent<PhysicsCmp2>(
                        bullet, PhysicsCmp2{
                            .x =r.n->getParent()->getPosition().X,
                            .y =r.n->getParent()->getPosition().Y,
                            .z =r.n->getParent()->getPosition().Z,
                            .vx= sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * 0.4f,
                            .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * 0.4f,
                            .vz= cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * 0.4f
                        }
                    );
                    EM.addComponent<RenderCmp2>(bullet, eng.createSphere(0.5));
                    EM.addComponent<EstadoCmp> (bullet);
                    EM.addTag<TBullet>(bullet);
                    keyboard.keyReleased(i.key_shot);
                }
                if(keyboard.isKeyPressed(i.key_sound1)){
                    
                }
                if(keyboard.isKeyPressed(i.key_sound2)){
                    
                }
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
                case irr::KEY_ESCAPE:
                    exit(0);
                    break;
                default:
                    break;
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
    static void onkeypressed(KeySym k) {
        keyboard.keyPressed(k);
    }

    static void onkeyreleased(KeySym k) {
        keyboard.keyReleased(k);
    }

    inline static Keyboard keyboard {};
};