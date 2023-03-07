#pragma once
#include "../util/types.hpp"
#include <cstdint>

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;
    static constexpr double pos_y  = 9;
    static constexpr float height  = 10;
    static constexpr uint8_t thick = 1;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& main_entity, PhysicsCmp2& main_phy, EstadoCmp& main_state) {
                EM.foreach<SYSCMPs, SYSTAGs>(
                    [&](Enty& collisioned_entity, PhysicsCmp2& collisioned_phy, EstadoCmp& collisioned_state){
                        if((main_entity.getID() != collisioned_entity.getID()) && 
                           (collisioned_state.colision == 0))
                        {
                            float dx, dy, dz;
                            dx = calculateDist(main_phy.x, collisioned_phy.x, main_state.width,  collisioned_state.width);
                            dy = calculateDist(main_phy.y, collisioned_phy.y, main_state.height, collisioned_state.height);
                            dz = calculateDist(main_phy.z, collisioned_phy.z, main_state.depth,  collisioned_state.depth);

                            if(dx<=0 && dy<=0 && dz<=0){
                                if(collisioned_entity.hasTAG<TBullet>() && main_entity.hasTAG<TEnemy>()){
                                    auto& sound = EM.getComponent<SoundCmp>(main_entity);
                                    EM.changeSound(sound, 0);
                                }

                                collisioned_state.colision  = 1<<1;
                                collisioned_state.entityCol = main_entity.getID();
                                
                                main_state.colision = 1<<1;
                                main_state.entityCol = collisioned_entity.getID();
                            }
                        }
                    }
                );
            }
        );
    }

    float calculateDist(float main_pos, float coll_pos, float main_dim, float coll_dim) {
        float d;
        d = abs(main_pos - coll_pos);
        d -= main_dim + coll_dim;
        return d;
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
    }

    void hitboxes_Sala_Inicio(EntyMan& EM, TheEngine& dev) {
        //Sala de inicio:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {  -57, -22.25, 12.5} 34.75
        //z: {-25.7,   9.05, 43.8} 34.75
        //
        //   extremo  mitad  extremo  dist
        //x: { -69.6, -34.85,  -0.1} 34.75
        //z: { -33.8,   0.95,  35.7} 34.75
        //x: { -69.6,  -64.7, -59.8} 4.9
        //x: { -35.2, -17.65,  -0.1} 17.55
        //z: { -33.8,  -24.3, -14.8} 9.5
        //z: {   4.1,   19.9,  35.7} 15.8

        float pos_x[] = { -34.85, -69.6, -64.7, -17.65, -0.1,  -0.1};
        float pos_z[] = { -33.8,  0.95,  35.7,  35.7,   19.9,  -24.3};
        float widht[] = { 34.75,  thick, 4.9,   17.55,  thick, thick};
        float depth[] = { thick,  34.75, thick, thick,  15.8,  9.5};
        uint8_t num_paredes = 6;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Inicio_Adyacente(EntyMan& EM, TheEngine& dev) {
        //Sala adyacente:
        //
        //Dimensiones
        //  extremo mitad extremo dist
        //x: { 14.8, 28.7, 42.6} 13.9
        //z: {-33.8, 0.95, 35.7} 34.75
        //
        //Paredes con puerta en medio
        //z: { -33.8, -24.7, -15.6} 9.1
        //z: {  11.1,  23.4,  35.7} 12.3

        float pos_x[] = { 42.6,  28.7,  28.7,  14.8,  14.8};
        float pos_z[] = { 0.95,  -33.8, 35.7,  -24.7, 23.4};
        float widht[] = { thick, 13.9,  13.9,  thick, thick};
        float depth[] = { 34.75, thick, thick, 9.1,   12.3};
        uint8_t num_paredes = 5;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Patio(EntyMan& EM, TheEngine& dev) {
        //Sala Patio:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: { -83.7, -41.95,  -0.2} 41.75
        //z: {  50.7,   85.4, 120.1} 34.7
        //
        //Paredes con puerta en medio
        //x: { -83.7, -64.45, -45.2} 19.25
        //x: { -21.4,   -9.9,  -0.2} 9.7
        //x: { -83.7, -78.85,   -74} 4.85
        //x: { -49.7, -24.95,  -0.2} 24.75
        //z: {  50.7,  58.25,  65.8} 7.55
        //z: {  88.9,  104.5, 120.1} 15.6

        float pos_x[] = { -83.7, -64.45, -9.9,  -78.85, -24.95, -0.2,  -0.2};
        float pos_z[] = { 85.4,  50.7,   50.7,  120.1,  120.1,  58.25, 104.5};
        float widht[] = { thick, 19.25,  9.7,   4.85,   24.75,  thick, thick};
        float depth[] = { 34.7,  thick,  thick, thick,  thick,  7.55,  15.6};
        uint8_t num_paredes = 7;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Patio_Adyacente(EntyMan& EM, TheEngine& dev) {
        //Sala Patio Adyacente:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: { -83.7,  -52.4, -21.1} 31.3
        //z: { 120.1, 140.95, 161.8} 20.85

        float pos_x[] = { -52.4, -83.7, -21.1};
        float pos_z[] = { 161.8, 140.95, 140.95};
        float widht[] = { 31.3,  thick, thick};
        float depth[] = { thick, 20.85,  20.85};
        uint8_t num_paredes = 3;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Sala_Alejada(EntyMan& EM, TheEngine& dev) {
        //Sala Alejada:
        //
        //Dimensiones
        //    extremo  mitad  extremo  dist
        //x: {   14.8,  46.05,  77.3} 31.25
        //z: { -138.6, -110.8,   -83} 27.8
        //
        //Paredes con puerta en medio
        //x: {   14.8,   29.5,   44.2} 14.7
        //x: {   66.8,  72.05,   77.3} 5.25
        //z: { -138.6, -131.1, -123.6} 7.5
        //z: {  -94.5, -88.75,    -83} 5.75

        float pos_x[] = { 46.05, 77.3,   29.5,   72.05,  14.8,   14.8};
        float pos_z[] = { -83,   -110.8, -138.6, -138.6, -131.1, -88.75};
        float widht[] = { 31.25, thick,  14.7,   5.25,   thick,  thick};
        float depth[] = { thick, 27.8,   thick,  thick,  7.5,    5.75};
        uint8_t num_paredes = 6;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Pasillo1(EntyMan& EM, TheEngine& dev) {
        //Pasillo 1:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: {  -69.6, -34.9, -0.2} 34.7
        //z: { 35.7,    43.2, 50.7} 7.5

        float pos_x[] = {-69.6};
        float pos_z[] = {43.2};
        float widht[] = {thick};
        float depth[] = {7.5};
        uint8_t num_paredes = 1;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Pasillo2(EntyMan& EM, TheEngine& dev) {
        //Pasillo 2:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: { -0.2,   7.3,  14.8} 7.5
        //z: { -172, -25.9, 120.2} 146.1
        //
        //Trozo de pared
        //z: { -172, -102.95,  -33.9} 69.05
        //z: { -172,  -162.8, -153.6} 9.2
        //z: {  -83,   -58.4,  -33.8} 24.6
        //z: { 35.7,   77.95,  120.2} 42.25

        float pos_x[] = {7.3,   7.3,   -0.2,    14.8,   14.8,  14.8};
        float pos_z[] = {-172,  120.2, -102.95, -162.8, -58.4, 77.95};
        float widht[] = {7.5,   7.5,   thick,   thick,  thick, thick};
        float depth[] = {thick, thick, 69.05,   9.2,    24.6,  42.25};
        uint8_t num_paredes = 6;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxes_Pasillo3(EntyMan& EM, TheEngine& dev) {
        //Pasillo 3:
        //
        //Dimensiones
        //  extremo  mitad  extremo  dist
        //x: {  14.8,  46.05,   77.3} 31.25
        //z: { -153.6, -146.1, -138.6} 7.5

        float pos_x[] = {77.3,   46.05};
        float pos_z[] = {-146.1, -153.6};
        float widht[] = {thick,  31.25};
        float depth[] = {7.5,    thick};
        uint8_t num_paredes = 2;

        create_Hitbox(num_paredes, EM, pos_x, pos_z, widht, depth, dev);
    }

    void create_Hitbox(uint8_t num, EntyMan& EM, float pos_x[], float pos_z[], float widht[], float depth[], TheEngine& dev) {
        for(uint8_t i {0}; i < num; i++) {
            Enty& wall = EM.createEntity();
            EM.addComponent<PhysicsCmp2>(wall, static_cast<double>(pos_x[i]), pos_y, static_cast<double>(pos_z[i]));
            EM.addComponent<EstadoCmp>  (wall, widht[i], height, depth[i]);
            //EM.addComponent<RenderCmp2> (wall, dev.createModel("assets/models/enemy.obj","assets/textures/fire.bmp"));
            EM.addTag      <TInteract>  (wall);
            EM.addTag      <TWall>      (wall);
        }
    }
};