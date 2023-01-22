#pragma once
#include "../util/keyboard.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include <iostream>

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& eng) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, InputCmp2& i, PhysicsCmp2& p) {
                p.vx = 0;
                p.vy = 0;
                if(keyboard.isKeyPressed(i.key_left)){
                    //std::cout<<"A\n";
                    //p.vx = -0.1;
                }
                if(keyboard.isKeyPressed(i.key_right)){
                    //std::cout<<"D\n";
                    //p.vx = 0.1;
                }
                if(keyboard.isKeyPressed(i.key_up)){
                    //std::cout<<"W\n";
                    //p.vy = 0.1;
                }
                if(keyboard.isKeyPressed(i.key_down)){
                    //std::cout<<"S\n";
                    //p.vy = -0.1;
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
                case irr::KEY_KEY_P:
                    checkPressed(event, XK_P);
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