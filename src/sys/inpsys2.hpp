#pragma once
#include "../util/keyboard.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"

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
                    int ammo=0;
                    switch (EM.getComponent<InventarioCmp>(player).equipada)
                    {
                    case 0:
                        ammo = EM.getComponent<InventarioCmp>(player).ammo1;
                        break;
                    case 1:
                        ammo = EM.getComponent<InventarioCmp>(player).ammo2;
                        break;

                    default:
                        break;
                    }
                    
                    if(ammo>0){
                        Enty& bullet = EM.createEntity();
                        if(EM.getComponent<InventarioCmp>(player).equipada==0){ //pistol
                            EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{.damage=20.f, .speed=0.8f, .bulletRad=0.1f});
                            ammo-=1;
                            EM.getComponent<InventarioCmp>(player).ammo1-=1;
                        }
                        else if (EM.getComponent<InventarioCmp>(player).equipada==1){ //escopeta
                            EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{.damage=50.f, .speed=0.4f, .bulletRad=0.5f});
                            ammo-=1;
                            EM.getComponent<InventarioCmp>(player).ammo2-=1;
                        }
                        EM.addComponent<PhysicsCmp2>(
                            bullet, PhysicsCmp2{
                                .x =r.n->getParent()->getPosition().X,
                                .y =r.n->getParent()->getPosition().Y,
                                .z =r.n->getParent()->getPosition().Z,
                                .vx= sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * 
                                EM.getComponent<EstadisticaCmp>(bullet).speed,
                                .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * 
                                EM.getComponent<EstadisticaCmp>(bullet).speed,
                                .vz= cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * 
                                EM.getComponent<EstadisticaCmp>(bullet).speed
                            }
                        );

                        EM.addComponent<RenderCmp2>(bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
                        EM.addComponent<EstadoCmp> (bullet);
                        EM.addTag<TBullet>(bullet);
                        for(auto& a : EM.getEntities()){
                            if(a.hasTAG<TWeapon>()){
                                SS.changesound(EM.getComponent<SoundCmp>(a),2);
                                SS.startsound(EM.getComponent<SoundCmp>(a));
                            }
                        }
                    }
                    keyboard.keyReleased(i.key_shot);
                }
                if(keyboard.isKeyPressed(i.key_sound1)){
                    
                }
                if(keyboard.isKeyPressed(i.key_sound2)){
                    
                }
                if(keyboard.isKeyPressed(i.key_weapon1)){
                    EM.getComponent<InventarioCmp>(player).inventary[EM.getComponent<InventarioCmp>(player).equipada] = 1;
                    EM.getComponent<InventarioCmp>(player).equipada = 0;
                    EM.getComponent<InventarioCmp>(player).inventary[0] = 2;
                }
                if(keyboard.isKeyPressed(i.key_weapon2)){
                    
                    if(EM.getComponent<InventarioCmp>(player).inventary[1] != 0){
                        
                        EM.getComponent<InventarioCmp>(player).inventary[EM.getComponent<InventarioCmp>(player).equipada] = 1;
                        EM.getComponent<InventarioCmp>(player).equipada = 1;
                        EM.getComponent<InventarioCmp>(player).inventary[1] = 2;
                    }
                }
                if(keyboard.isKeyPressed(i.key_reloadALLAmmo)){
                    EM.getComponent<InventarioCmp>(player).ammo1=10;
                    EM.getComponent<InventarioCmp>(player).ammo2=5;
                    for(auto& a : EM.getEntities()){
                        if(a.hasTAG<TWeapon>()){
                            SS.changesound(EM.getComponent<SoundCmp>(a),1);
                            SS.startsound(EM.getComponent<SoundCmp>(a));
                        }
                    }
                }
                if(keyboard.isKeyPressed(i.key_weapon1)){
                    EM.getComponent<InventarioCmp>(player).inventary[EM.getComponent<InventarioCmp>(player).equipada] = 1;
                    EM.getComponent<InventarioCmp>(player).equipada = 0;
                    EM.getComponent<InventarioCmp>(player).inventary[0] = 2;
                }
                if(keyboard.isKeyPressed(i.key_weapon2)){
                    
                    if(EM.getComponent<InventarioCmp>(player).inventary[1] != 0){
                        
                        EM.getComponent<InventarioCmp>(player).inventary[EM.getComponent<InventarioCmp>(player).equipada] = 1;
                        EM.getComponent<InventarioCmp>(player).equipada = 1;
                        EM.getComponent<InventarioCmp>(player).inventary[1] = 2;
                    }
                }
                if(keyboard.isKeyPressed(i.key_reloadALLAmmo)){
                    EM.getComponent<InventarioCmp>(player).ammo1=10;
                    EM.getComponent<InventarioCmp>(player).ammo2=5;

                }
                bb = { cam->getPosition().X, cam->getPosition().Z, SB::Seek, true };
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
    static void onkeypressed(KeySym k) {
        keyboard.keyPressed(k);
    }

    static void onkeyreleased(KeySym k) {
        keyboard.keyReleased(k);
    }

    inline static Keyboard keyboard {};
};