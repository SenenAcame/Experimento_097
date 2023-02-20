#pragma once
#include "../util/keyboard.hpp"
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include "soundsystem.hpp"

struct InpSys2 : public irr::IEventReceiver{
    using SYSCMPs = MP::Typelist<InputCmp2, RenderCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& SS, double const dt) {
        auto& bb = EM.getBoard();
        auto cam   = eng.getCamera();
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& player, InputCmp2& i, RenderCmp2& r) {
                EM.getComponent<InventarioCmp>(player).clockCadence += dt;
                
                double reloadTimer = 0;
                
                if(keyboard.isKeyPressed(i.key_shot)){
                    //cambiar por funcion de disparo en funcion de inventario array y el modelo arma
                    //std::cout<<"Arma equipada: " <<EM.getComponent<InventarioCmp>(player).equipada<<
                    //"\n";
                    int ammo = 0;
                    double weaponCadence=0;
                    size_t weapon =0;
                    
                    

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
                        //std::cout<<"NO PUEDES DISPARAR AUN. Reloading es: "<<EM.getComponent<InventarioCmp>(player).reloading << 
                        //" , el clock es: "<<EM.getComponent<InventarioCmp>(player).clockReload <<
                        //", Y el reloadtimer es: "<<reloadTimer<<"\n";
                        return;
                    }

                    //std::cout<<"DISPARANDO. Reloading es: "<<EM.getComponent<InventarioCmp>(player).reloading << 
                    //" , el clock es: "<<EM.getComponent<InventarioCmp>(player).clockReload <<
                    //", Y el reloadtimer es: "<<reloadTimer<<"\n";

                    notReloading(EM, player);
                    
                    if(ammo > 0) { 
                        createBullet(EM, player, ammo, weaponCadence, r, eng, SS, dt); 
                        //std::cout<<"Municion arma es " << EM.getComponent<InventarioCmp>(player).ammo2 <<"\n";
                        //std::cout<<"Cargador arma es " << EM.getComponent<InventarioCmp>(player).magazine2 <<"\n";
                    }
                    if(EM.getComponent<InventarioCmp>(player).equipada == 0 || EM.getComponent<InventarioCmp>(player).equipada ==1){
                        keyboard.keyReleased(i.key_shot);
                    }
                      
                }
                
                if(keyboard.isKeyPressed(i.key_weapon1)) { changeWeapon(EM, player, 0); }
                if(keyboard.isKeyPressed(i.key_weapon2) && EM.getComponent<InventarioCmp>(player).inventary[1] != 0) { changeWeapon(EM, player, 1); }
                if(keyboard.isKeyPressed(i.key_weapon3) && EM.getComponent<InventarioCmp>(player).inventary[2] != 0) { changeWeapon(EM, player, 2); }

                if(keyboard.isKeyPressed(i.key_unlockAll)){
                    //std::cout<<"ARRAY INVENTARIO: ";
                    for(int i=0;i<3;i++){
                        
                        if(EM.getComponent<InventarioCmp>(player).inventary[i]!=2){
                            //std::cout<<EM.getComponent<InventarioCmp>(player).inventary[i]<<"\n";
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

    void iAmReloading(EntyMan& EM, Enty& player){
        
        EM.getComponent<InventarioCmp>(player).reloading=1;
        //std::cout<<"Reloading es ahora: "<< EM.getComponent<InventarioCmp>(player).reloading<<"\n";  
    }

    void notReloading(EntyMan& EM, Enty& player){
        
        EM.getComponent<InventarioCmp>(player).reloading=0;
        //std::cout<<"Reloading es ahora: "<< EM.getComponent<InventarioCmp>(player).reloading<<"\n";
    }

    void createBullet(EntyMan& EM, Enty& player, int ammo, double cadenciaWeapon, RenderCmp2& r, TheEngine& eng, SoundSystem_t& SS, double const dt) {
        
        //std::cout<<"Este es el dt:" <<EM.getComponent<InventarioCmp>(player).clockCadence << " y esta es la cadencia: "
        //<<EM.getComponent<InventarioCmp>(player).cadenceWeapon1 <<"\n";
        if(EM.getComponent<InventarioCmp>(player).clockCadence <= cadenciaWeapon){
            //std::cout<<"NO PUEDES DISPARAR AUN\n";
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
                    .x =r.n->getParent()->getPosition().X,
                    .y =r.n->getParent()->getPosition().Y,
                    .z =r.n->getParent()->getPosition().Z,
                    .vx=  sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * cos(r.n->getParent()->getRotation().X * M_PI/180.f) * speed,
                    .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * speed,
                    .vz=  cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * cos(r.n->getParent()->getRotation().X * M_PI/180.f) * speed
                }
            );
            EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
            EM.addComponent<EstadoCmp>  (bullet);
            EM.addComponent<SoundCmp>  (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
            EM.addComponent<SelfDestCmp>(bullet);
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
                        .x =r.n->getParent()->getPosition().X+(i * cos(r.n->getParent()->getRotation().Y * M_PI/180.f)),
                        .y =r.n->getParent()->getPosition().Y ,
                        .z =r.n->getParent()->getPosition().Z+(i * -sin(r.n->getParent()->getRotation().Y * M_PI/180.f)),
                        .vx=  sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * cos(r.n->getParent()->getRotation().X * M_PI/180.f) * speed,
                        .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * speed,
                        .vz=  cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * cos(r.n->getParent()->getRotation().X * M_PI/180.f) * speed
                    }
                );
                
                EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
                EM.addComponent<EstadoCmp>  (bullet);
                EM.addComponent<SoundCmp>  (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
                EM.addComponent<SelfDestCmp>(bullet);
                EM.addTag<TBullet>(bullet);

                if(i>-0.4 && i<0.4){
                    Enty& bullet2 = EM.createEntity();
                    statsBullet(EM, bullet2, ammo, 50.f, 0.8f, 0.1f);
                    EM.addComponent<PhysicsCmp2>(
                    bullet2, PhysicsCmp2{
                            .x =r.n->getParent()->getPosition().X+(i*cos(r.n->getParent()->getRotation().Y * M_PI/180.f)),
                            .y =r.n->getParent()->getPosition().Y+(1*0.2),
                            .z =r.n->getParent()->getPosition().Z+(i *-sin(r.n->getParent()->getRotation().Y * M_PI/180.f)),
                            .vx=  sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * speed,
                            .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * speed,
                            .vz=  cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * speed
                        }
                    );
                    
                    
                    EM.addComponent<RenderCmp2> (bullet2, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
                    EM.addComponent<EstadoCmp>  (bullet2);
                    EM.addComponent<SoundCmp>  (bullet2, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
                    EM.addComponent<SelfDestCmp>(bullet2);
                    EM.addTag<TBullet>(bullet2);
                }
                Enty& bullet3 = EM.createEntity();
                statsBullet(EM, bullet3, ammo, 50.f, 0.8f, 0.1f);
                EM.addComponent<PhysicsCmp2>(
                bullet3, PhysicsCmp2{
                        .x =r.n->getParent()->getPosition().X+(i*cos(r.n->getParent()->getRotation().Y * M_PI/180.f)),
                        .y =r.n->getParent()->getPosition().Y+(2*0.2),
                        .z =r.n->getParent()->getPosition().Z+(i * -sin(r.n->getParent()->getRotation().Y * M_PI/180.f)),
                        .vx=  sin(r.n->getParent()->getRotation().Y * M_PI/180.f) * speed,
                        .vy= -sin(r.n->getParent()->getRotation().X * M_PI/180.f) * speed,
                        .vz=  cos(r.n->getParent()->getRotation().Y * M_PI/180.f) * speed
                    }
                );
                
                
                EM.addComponent<RenderCmp2> (bullet3, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
                EM.addComponent<EstadoCmp>  (bullet3);
                EM.addComponent<SoundCmp>  (bullet3, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
                EM.addComponent<SelfDestCmp>(bullet3);
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
            EM.getComponent<InventarioCmp>(player).magazine3-=1;
        }
        
        
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