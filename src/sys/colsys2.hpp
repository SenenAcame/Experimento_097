#pragma once
#include "../util/types.hpp"
#include <cstdint>

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
        hitboxes_Sala_Inicio     (EM, dev);
        hitboxes_Inicio_Adyacente(EM, dev);
        hitboxes_Patio           (EM, dev);
        hitboxes_Patio_Adyacente (EM, dev);
        hitboxes_Sala_Alejada    (EM, dev);
        hitboxes_Pasillo1        (EM, dev);
        hitboxes_Pasillo2        (EM, dev);
        hitboxes_Pasillo3        (EM, dev);
        hitboxes_Pasillo4        (EM, dev);
        hitboxes_Rampa           (EM, dev);
    }

    void hitboxes_Sala_Inicio(EntyMan& EM, TheEngine& dev) {
        //Sala de inicio:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {  -57, -22.25, 12.5} 34.75
        //z: {-25.7,   9.05, 43.8} 34.75
        //
        //Paredes con puerta en medio
        //x: {  -57, -52.9, -48.8} 4.1
        //x: {-41.5, -14.5,  12.5} 27
        //z: {-25.7, -10.05,  5.6} 15.65
        //z: { 12.5,  28.15, 43.8} 15.65

        float pos_x[] = { -22.25, -57,   -52.9, -14.5, 12.5,  12.5};
        float pos_z[] = { -25.7,  9.05,  43.8,  43.8,  28.15, -10.05};
        float widht[] = { 34.75,  1,     4.1,   27,    1,     1};
        float depth[] = { 1,      34.75, 1,     1,     15.65, 15.65};
        uint8_t num_paredes = 6;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Inicio_Adyacente(EntyMan& EM, TheEngine& dev) {
        //Sala adyacente:
        //
        //Dimensiones
        //  extremo mitad extremo dist
        //x: { 22.9, 36.8, 50.7} 13.9
        //z: {-25.7, 9.05, 43.8} 34.75
        //
        //Paredes con puerta en medio
        //z: {-25.7, -13.35,   -1} 12.35
        //z: { 26.4,   35.1, 43.8} 8.7

        float pos_x[] = { 50.7,  36.8,  36.8, 22.9,   22.9};
        float pos_z[] = { 9.05,  -25.7, 43.8, -13.35, 35.1};
        float widht[] = { 1,     13.9,  13.9, 1,      1};
        float depth[] = { 34.75, 1,     1,    12.35,  8.7};
        uint8_t num_paredes = 5;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Patio(EntyMan& EM, TheEngine& dev) {
        //Sala Patio:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: { -70.7, -29.05,  12.6} 41.65
        //z: {  54.2,  89.45, 123.7} 35.25
        //
        //Paredes con puerta en medio
        //x: { -70.7, -43.25, -15.8} 27.45
        //x: {  -8.8,    1.9,  12.6} 10.7
        //x: { -70.7,  -65.9, -61.1} 4.8
        //x: { -54.2,  -20.8,  12.6} 33.4
        //z: {  54.2,  69.85,  85.5} 15.65
        //z: {  92.4, 108.05, 123.7} 15.65

        float pos_x[] = { -70.7, -43.25, 1.9,  -65.9, -20.8, 12.6,  12.6};
        float pos_z[] = { 89.45, 54.2,   54.2, 123.7, 123.7, 69.85, 108.05};
        float widht[] = { 1,     27.45,  10.7, 4.8,   33.4,  1,     1};
        float depth[] = { 35.25, 1,      1,    1,     1,     15.65, 15.65};
        uint8_t num_paredes = 7;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Patio_Adyacente(EntyMan& EM, TheEngine& dev) {
        //Sala Patio Adyacente:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: { -70.8, -39.6,  -8.4} 31.2
        //z: { 123.7, 144.5, 165.3} 20.8

        float pos_x[] = { -39.6, -70.8, -8.4};
        float pos_z[] = { 165.3, 144.5, 144.5};
        float widht[] = { 31.2,  1,     1};
        float depth[] = { 1,     20.8,  20.8};
        uint8_t num_paredes = 3;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Sala_Alejada(EntyMan& EM, TheEngine& dev) {
        //Sala Alejada:
        //
        //Dimensiones
        //    extremo  mitad  extremo  dist
        //x: {   22.8, 54.05,  85.3} 31.25
        //z: { -111.3, -83.5, -55.7} 27.8
        //
        //Paredes con puerta en medio
        //x: {   22.8,   40.2,  57.6} 17.4
        //x: {   64.6,  74.95,  85.3} 10.35
        //z: { -111.3,  -98.9, -86.5} 12,4
        //z: {  -79.6, -67.95, -55.7} 11.95

        float pos_x[] = { 54.05, 85.3,  40.2,   74.95,  22.8,  22.8};
        float pos_z[] = { -55.7, -83.5, -111.3, -111.3, -98.9, -67.95};
        float widht[] = { 31.25, 1,     17.4,   10.35,  1,     1};
        float depth[] = { 1,     27.8,  1,      1,      12.4,  11.95};
        uint8_t num_paredes = 6;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Pasillo1(EntyMan& EM, TheEngine& dev) {
        //Pasillo 1:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: {  12.5, 17.7,  22.9} 5.2
        //z: { -25.7,   49, 123.7} 74.7
        //
        //Trozo de pared
        //z: {  43.8, 83.75, 123.7} 39.95

        float pos_x[] = {17.7,  22.9};
        float pos_z[] = {123.7, 83.75};
        float widht[] = {5.2,   1};
        float depth[] = {1,     39.95};
        uint8_t num_paredes = 2;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Pasillo2(EntyMan& EM, TheEngine& dev) {
        //Pasillo 2:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: {  -57, -22.2, 12.6} 34.8
        //z: { 43.8,    49, 54.2} 5.2

        float pos_x[] = {-57};
        float pos_z[] = {49};
        float widht[] = {1};
        float depth[] = {5.2};
        uint8_t num_paredes = 1;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Pasillo3(EntyMan& EM, TheEngine& dev) {
        //Pasillo 3:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: {   12.5, 17.65,  22.8} 5.15
        //z: { -170.3,  -113, -55.7} 57.3
        //
        //Trozo de pared
        //z: {-170.3,    -146, -121.7} 24.3
        //z: {-121.7, -120.74, -119.8} 0.95
        //z: {-112.9,  -112.1, -111.3} 0.8

        float pos_x[] = {17.65,  12.5, 22.8,   22.8,    22.8};
        float pos_z[] = {-170.3, -113, -112.1, -120.74, -146};
        float widht[] = {5.15,   1,    1,      1,       1};
        float depth[] = {1,      57.3, 0.8,    0.95,    24.3};
        uint8_t num_paredes = 5;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Pasillo4(EntyMan& EM, TheEngine& dev) {
        //Pasillo 4:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: {   22.8,  54.05,   85.3} 31.25
        //z: { -121.7, -116.5, -111.3} 5.2

        float pos_x[] = {85.3,   54.05};
        float pos_z[] = {-116.5, -121.7};
        float widht[] = {1,      31.25};
        float depth[] = {5.2,    1};
        uint8_t num_paredes = 2;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Rampa(EntyMan& EM, TheEngine& dev) {
        //Rampa:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: {  12.5,  17.65,  22.8} 5.15
        //z: { -55.7, -40.65, -25.6} 15.05

        float pos_x[] = {12.5, 22.8};
        float pos_z[] = {-40.65, -40.65};
        float widht[] = {1, 1};
        float depth[] = {15.05, 15.05};
        uint8_t num_paredes = 2;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void create_Hitbox(uint8_t num, EntyMan& EM, float pos_x[], float pos_z[], float widht[], float depth[], TheEngine& dev) {
        for(uint8_t i {0}; i < num; i++) {
            Enty& wall = EM.createEntity();
            EM.addComponent<PhysicsCmp2>(wall, pos_x[i], 0, pos_z[i]);
            EM.addComponent<EstadoCmp>  (wall, widht[i], 1, depth[i]);
            EM.addComponent<RenderCmp2> (wall, dev.createModel("assets/models/enemy.obj","assets/textures/fire.bmp"));
            EM.addTag      <TInteract>  (wall);
            EM.addTag      <TWall>      (wall);
        }
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