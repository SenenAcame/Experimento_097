#pragma once
#include "../util/types.hpp"

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;

    void update(EntyMan& EM) {
        std::cout<<"\n";
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& main_entity, PhysicsCmp2& main_phy, EstadoCmp& main_stats) {
                EM.foreach<SYSCMPs, SYSTAGs>(
                    [&](Enty& collisioned_entity, PhysicsCmp2& collisioned_phy, EstadoCmp& collisioned_stats){
                        if((main_entity.getID() != collisioned_entity.getID()) && 
                           (collisioned_stats.colision == 0))
                        {
                            float dx = abs(main_phy.x - collisioned_phy.x);
                            float dy = abs(main_phy.y - collisioned_phy.y);
                            float dz = abs(main_phy.z - collisioned_phy.z);
                            
                            dx -= (main_stats.width  + collisioned_stats.width);
                            dy -= (main_stats.height + collisioned_stats.height);
                            dz -= (main_stats.depth  + collisioned_stats.depth);

                            if(dx<=0 && dy<=0 && dz<=0){
                                if(collisioned_entity.hasTAG<TBullet>() && main_entity.hasTAG<TEnemy>()){
                                    auto& sound = EM.getComponent<SoundCmp>(main_entity);
                                    EM.changeSound(sound, 0);
                                }

                                collisioned_stats.colision  = 1<<1;
                                collisioned_stats.entityCol = main_entity.getID();
                                
                                main_stats.colision = 1<<1;
                                main_stats.entityCol = collisioned_entity.getID();
                            }
                        }
                    }
                );
                std::cout<<"Soy "<<main_entity.getID()<<" y he colisionado contra "<<main_stats.entityCol<<"\n";
            }
        );
    }

    void init_Hitoxes_Map(EntyMan& EM, TheEngine& dev) {
        //EM.addComponent<RenderCmp2> (w2, dev.createModel("assets/models/enemy.obj","assets/textures/fire.bmp"));
        hitboxes_Sala_Inicio(EM);
        hitboxes_Inicio_Adyacente(EM);
        hitboxes_Patio(EM);
    }

    void hitboxes_Sala_Inicio(EntyMan& EM) {
        //Sala de inicio:
        //x: {  -57, -22.25, 12.5}
        //z: {-25.7,   9.05, 43.8}

        //Paredes enteras
        Enty& w1 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w1, -22.25, 0, -25.7);
        EM.addComponent<EstadoCmp>  (w1,  34.75, 1,     1);
        EM.addTag      <TInteract>  (w1);
        EM.addTag      <TWall>      (w1);

        Enty& w2 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w2, -57, 0,  9.05);
        EM.addComponent<EstadoCmp>  (w2,   1, 1, 34.75);
        EM.addTag      <TInteract>  (w2);
        EM.addTag      <TWall>      (w2);

        //Paredes con puerta en medio

        //x: {  -57, -52.9, -48.8}
        //x: {-41.5, -14.5,  12.5}
        Enty& w3 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w3, -52.9, 0, 43.8);
        EM.addComponent<EstadoCmp>  (w3,   4.1, 1,    1);
        EM.addTag      <TInteract>  (w3);
        EM.addTag      <TWall>      (w3);

        Enty& w4 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w4, -14.5, 0, 43.8);
        EM.addComponent<EstadoCmp>  (w4,    27, 1,    1);
        EM.addTag      <TInteract>  (w4);
        EM.addTag      <TWall>      (w4);

        //z: {-25.7, -11.05,  5.6}
        //z: { 12.5,  28.15, 43.8}
        Enty& w5 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w5, 12.5, 0, 28.15);
        EM.addComponent<EstadoCmp>  (w5,    1, 1, 15.65);
        EM.addTag      <TInteract>  (w5);
        EM.addTag      <TWall>      (w5);

        Enty& w6 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w6, 12.5, 0, -11.05);
        EM.addComponent<EstadoCmp>  (w6,    1, 1,  15.65);
        EM.addTag      <TInteract>  (w6);
        EM.addTag      <TWall>      (w6);
    }

    void hitboxes_Inicio_Adyacente(EntyMan& EM) {
        //Sala adyacente:
        //x: { 22.9, 36.8, 50.7}
        //z: {-25.7, 9.05, 43.8}
        
        //Paredes enteras
        Enty& w1 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w1, 50.7, 0,  9.05);
        EM.addComponent<EstadoCmp>  (w1,    1, 1, 34.75);
        EM.addTag      <TInteract>  (w1);
        EM.addTag      <TWall>      (w1);

        Enty& w2 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w2, 36.8, 0, -25.7);
        EM.addComponent<EstadoCmp>  (w2, 13.9, 1,     1);
        EM.addTag      <TInteract>  (w2);
        EM.addTag      <TWall>      (w2);
        
        Enty& w3 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w3, 36.8, 0, 43.8);
        EM.addComponent<EstadoCmp>  (w3, 13.9, 1,    1);
        EM.addTag      <TInteract>  (w3);
        EM.addTag      <TWall>      (w3);

        //Paredes con puerta en medio
        //z: {-25.7, -13.35,   -1} 12.35
        //z: { 26.4,   35.1, 43.8} 8.7
        Enty& w4 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w4, 22.9, 0, -13.35);
        EM.addComponent<EstadoCmp>  (w4,    1, 1,  12.35);
        EM.addTag      <TInteract>  (w4);
        EM.addTag      <TWall>      (w4);
        
        Enty& w5 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w5, 22.9, 0, 35.1);
        EM.addComponent<EstadoCmp>  (w5,    1, 1,  8.7);
        EM.addTag      <TInteract>  (w5);
        EM.addTag      <TWall>      (w5);
    }

    void hitboxes_Patio(EntyMan& EM) {
        //Sala Patio:
        //x: { -70.7, -29.05,  12.6} 41.65
        //z: {  54.2,  89.45, 123.7} 35.25
        
        //Paredes enteras
        Enty& w1 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w1, -70.7, 0, 89.45);
        EM.addComponent<EstadoCmp>  (w1,     1, 1, 35.25);
        EM.addTag      <TInteract>  (w1);
        EM.addTag      <TWall>      (w1);

        //Paredes con puerta en medio
        //x: {-70.7,-43.25,-15.8} 27.45
        //x: { -8.8,   1.9, 12.6} 10.7

        Enty& w2 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w2, -43.25, 0, 54.2);
        EM.addComponent<EstadoCmp>  (w2,  27.45, 1,    1);
        EM.addTag      <TInteract>  (w2);
        EM.addTag      <TWall>      (w2);

        Enty& w3 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w3,  1.9, 0, 54.2);
        EM.addComponent<EstadoCmp>  (w3, 10.7, 1,    1);
        EM.addTag      <TInteract>  (w3);
        EM.addTag      <TWall>      (w3);

        //x: { -70.7, -65.9, -61.1} 4.8
        //x: { -54.2, -20.8,  12.6} 33.4

        Enty& w4 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w4, -65.9, 0, 123.7);
        EM.addComponent<EstadoCmp>  (w4,   4.8, 1,     1);
        EM.addTag      <TInteract>  (w4);
        EM.addTag      <TWall>      (w4);

        Enty& w5 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w5, -20.8, 0, 123.7);
        EM.addComponent<EstadoCmp>  (w5,  33.4, 1,     1);
        EM.addTag      <TInteract>  (w5);
        EM.addTag      <TWall>      (w5);

        //z: { 54.2,  69.85,  85.5} 15.65
        //z: { 92.4, 108.05, 123.7} 15.65

        Enty& w6 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w6, 12.6, 0, 69.85);
        EM.addComponent<EstadoCmp>  (w6,    1, 1, 15.65);
        EM.addTag      <TInteract>  (w6);
        EM.addTag      <TWall>      (w6);

        Enty& w7 = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(w7, 12.6, 0, 108.05);
        EM.addComponent<EstadoCmp>  (w7,    1, 1,  15.65);
        EM.addTag      <TInteract>  (w7);
        EM.addTag      <TWall>      (w7);
    }
};


// Viejo codigo del update del sistema de colisiones

//EM.foreach<SYSCMPs, SYSTAGs>(
//    [&](Enty& e, PhysicsCmp2& p) {
//        for(auto& a : EM.getEntities()){
//            if(e.getID()!=a.getID()){
//                if(a.hasTAG<TPlayer>() || a.hasTAG<TEnemy>() || a.hasTAG<TBullet>() ){
//                    if(a.hasCMP<EstadoCmp>()){
//                        if( EM.getComponent<EstadoCmp>(a).colision == 0){
//                            auto& phy = p;
//                            auto& phy2 = EM.getComponent<PhysicsCmp2>(a);
//                            float tamx=0, tamy=0, tamz=0, tamx2=0, tamy2=0, tamz2=0;
//                            if(e.hasTAG<TPlayer>()|| e.hasTAG<TEnemy>()){
//                                tamx=0.8;
//                                tamy=2.5;
//                                tamz=2;
//                            }
//                            if(a.hasTAG<TPlayer>()|| a.hasTAG<TEnemy>()){
//                                tamx2=0.8;
//                                tamy2=2.5;
//                                tamz2=2;
//                            }
//                            float dx, dy, dz;
//                            if((dx = phy.x - phy2.x) < 0)
//                                dx=-dx;
//                            dx -= (tamx + tamx2);
//                            if((dy = phy.y - phy2.y) < 0)
//                                dy=-dy;
//                            dy -= (tamy + tamy2);
//                            if((dz = phy.z - phy2.z) < 0)
//                                dz=-dz;
//                            dz -= (tamz + tamz2);
//                            if(dx<=0 && dy<=0 && dz<=0){
//                                if(a.hasTAG<TBullet>()&&e.hasTAG<TEnemy>()){
//                                    SS.changesound(EM.getComponent<SoundCmp>(e),0);
//                                    SS.startsound(EM.getComponent<SoundCmp>(e));
//                                }
//                                EM.getComponent<EstadoCmp>(a).colision = 1<<1;
//                                EM.getComponent<EstadoCmp>(a).entityCol = e.getID();
//                                if(a.hasTAG<TPlayer>() && EM.getComponent<EstadoCmp>(a).colision ==1){
//                                    std::cout<<"Soy player y he chocado\n";
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//);