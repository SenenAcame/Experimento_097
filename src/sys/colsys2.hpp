#pragma once
#include "../util/types.hpp"
#include "../man/levelman.hpp"
#include <cstdint>

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;
    static constexpr double pos_y  = 9;
    static constexpr float height  = 10;
    static constexpr uint8_t thick = 3;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty const& main_entity, PhysicsCmp2 const& main_phy, EstadoCmp& main_state) {
                EM.foreach<SYSCMPs, SYSTAGs>(
                    [&](Enty const& collisioned_entity, PhysicsCmp2 const& collisioned_phy, EstadoCmp& collisioned_state){
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

    [[nodiscard]] constexpr float calculateDist(float const main_pos, float const coll_pos, float const main_dim, float const coll_dim) const noexcept{
        float d;
        d = abs(main_pos - coll_pos);
        d -= main_dim + coll_dim;
        return d;
    }

    void init_Hitoxes_Map(LevelMan& LM, TheEngine& dev) noexcept {
        hitboxesMapaOriginalSala_Inicio     (LM, dev);
        hitboxesMapaOriginalInicio_Adyacente(LM, dev);
        hitboxesMapaOriginalPatio           (LM, dev);
        hitboxesMapaOriginalPatio_Adyacente (LM, dev);
        hitboxesMapaOriginalSala_Alejada    (LM, dev);
        hitboxesMapaOriginalPasillo1        (LM, dev);
        hitboxesMapaOriginalPasillo2        (LM, dev);
        hitboxesMapaOriginalPasillo3        (LM, dev);
    }

    void init_Hitoxes_Map2(LevelMan& LM, TheEngine& dev) noexcept {
        hitboxesMapaSimpleSala1   (LM, dev);
        hitboxesMapaSimpleSala2   (LM, dev);
        hitboxesMapaSimpleSala3   (LM, dev);
        hitboxesMapaSimplePasillo1(LM, dev);
        hitboxesMapaSimplePasillo2(LM, dev);
        hitboxesMapaSimplePasillo3(LM, dev);
    }

    //salas del mapa original
    void hitboxesMapaOriginalSala_Inicio(LevelMan& LM, TheEngine& dev) noexcept {
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

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaOriginalInicio_Adyacente(LevelMan& LM, TheEngine& dev) noexcept {
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

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaOriginalPatio(LevelMan& LM, TheEngine& dev) noexcept {
        //Sala Patio:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: { -83.7, -41.95,  -0.2} 41.75
        //z: {  50.7,   85.4, 120.1} 34.7
        //
        //Paredes con puerta en medio
        //x: { -83.7, -64.45, -45.2} 19.25
        //x: { -21.4,  -10.8,  -0.2} 10.6
        //x: { -83.7, -78.85,   -74} 4.85
        //x: { -49.7, -24.95,  -0.2} 24.75
        //z: {  50.7,  58.25,  65.8} 7.55
        //z: {  88.9,  104.5, 120.1} 15.6

        float pos_x[] = { -83.7, -64.45, -10.8, -78.85, -24.95, -0.2,  -0.2};
        float pos_z[] = { 85.4,  50.7,   50.7,  120.1,  120.1,  58.25, 104.5};
        float widht[] = { thick, 19.25,  10.6,  4.85,   24.75,  thick, thick};
        float depth[] = { 34.7,  thick,  thick, thick,  thick,  7.55,  15.6};
        uint8_t num_paredes = 7;

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaOriginalPatio_Adyacente(LevelMan& LM, TheEngine& dev) noexcept {
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

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaOriginalSala_Alejada(LevelMan& LM, TheEngine& dev) noexcept {
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

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaOriginalPasillo1(LevelMan& LM, TheEngine& dev) noexcept {
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

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaOriginalPasillo2(LevelMan& LM, TheEngine& dev) noexcept {
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

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaOriginalPasillo3(LevelMan& LM, TheEngine& dev) noexcept {
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

        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    //salas del mapa simple
    void hitboxesMapaSimpleSala1(LevelMan& LM, TheEngine& dev) noexcept {
        //Sala 1:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {-68, -33.5,  1} 34.5
        //z: { -1,  33.5, 68} 34.5
        //
        //Paredes con puerta en medio
        //x: {  -68, -56.75, -45.5} 11.25
        //x: {-21.5, -10.25,     1} 11.25
        //z: {   -1,  10.25,  21.5} 11.25
        //z: { 45.5,  56.75,    68} 11.25

        float pos_x[] = {-33.5, -68,   1,     1,     -56.75, -10.25};
        float pos_z[] = {68,    33.5,  10.25, 56.75, -1,     -1};
        float widht[] = {34.5,  thick, thick, thick, 11.25,  11.25};
        float depth[] = {thick, 34.5,  11.25, 11.25, thick,  thick};
        uint8_t num_paredes { 6 };
        
        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaSimpleSala2(LevelMan& LM, TheEngine& dev) noexcept {
        //Sala 2:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {73, 107.5, 142} 34.5
        //z: {23,  57.5,  92} 34.5
        //
        //Paredes con puerta en medio
        //x: {   73,  84.25, 95.5} 11.25
        //x: {119.5, 130.75,  142} 11.25
        //z: {   23,  34.25, 45.5} 11.25
        //z: { 69.5,  80.75,   92} 11.25

        float pos_x[] = {107.5,142  ,84.25,130.75,73,   73};
        float pos_z[] = {92,   57.5 ,23,   23,    34.25,80.75};
        float widht[] = {34.5, thick,11.25,11.25, thick,thick};
        float depth[] = {thick,34.5 ,thick,thick, 11.25,11.25};
        uint8_t num_paredes { 6 };
        
        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaSimpleSala3(LevelMan& LM, TheEngine& dev) noexcept {
        //Sala 3:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {  2.5,  37,  71.5} 34.5
        //z: {-95.5, -61, -26.5} 34.5
        //
        //Paredes con puerta en medio
        //z: {-95.5, -84.25,   -73} 11.25
        //z: {  -49, -37.75, -26.5} 11.25

        float pos_x[] = {37,   37,   2.5,   71.5,  2.5,   71.5  };
        float pos_z[] = {-26.5,-95.5,-84.25,-84.25,-37.75,-37.75};
        float widht[] = {34.5, 34.5, thick, thick, thick, thick };
        float depth[] = {thick,thick,11.25, 11.25, 11.25, 11.25 };
        uint8_t num_paredes { 6 };
        
        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaSimplePasillo1(LevelMan& LM, TheEngine& dev) noexcept {
        //Pasillo 1:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {   1,   37,   73} 36
        //z: {21.5, 45.5, 69.5} 24
        //
        //Paredes con puerta en medio
        //x: {   1,   13,   25} 12
        //x: {  25,   49,   73} 24
        //x: {   1,   25,   49} 24
        //x: {  49,   61,   73} 12
        //z: {21.5, 33.5, 45.5} 12
        //z: {45.5, 57.5, 69.5} 12

        float pos_x[] = {25,   49,   25,   61,   13,   49   };
        float pos_z[] = {57.5, 33.5, 21.5, 45.5, 45.5, 69.5 };
        float widht[] = {thick,thick,24,   12,   12,   24   };
        float depth[] = {12,   12,   thick,thick,thick,thick};
        uint8_t num_paredes { 6 };
        
        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaSimplePasillo2(LevelMan& LM, TheEngine& dev) noexcept {
        //Pasillo 2:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {71.5, 95.5, 119.5} 24
        //z: { -73,  -25,    23} 48
        //
        //Paredes con puerta en medio
        //x: {71.5, 83.5, 95.5} 12
        //z: { -49,  -13,   23} 36

        float pos_x[] = {119.5,95.5, 95.5, 83.5 };
        float pos_z[] = {-25,  -13,  -73,  -49  };
        float widht[] = {thick,thick,24,   12   };
        float depth[] = {48,   36,   thick,thick};
        uint8_t num_paredes { 4 };
        
        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void hitboxesMapaSimplePasillo3(LevelMan& LM, TheEngine& dev) noexcept {
        //Pasillo 3:
        //
        //Dimensiones
        //   extremo  mitad  extremo  dist
        //x: {-45.5, -21.5, 2.5} 24
        //z: {   -1,   -37, -73} 36
        //
        //Paredes con puerta en medio
        //x: {-21.5, -9.5, 2.5} 12
        //z: {   -1,  -25, -49} 24

        float pos_x[] = {-45.5,-21.5,-21.5,-9.5 };
        float pos_z[] = {-37,  -25,  -73,  -49  };
        float widht[] = {thick,thick,24,   12   };
        float depth[] = {36,   24,   thick,thick};
        uint8_t num_paredes { 4 };
        
        create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
    }

    void create_HitBoxes(uint8_t const num, LevelMan& LM, float const pos_x[], float const pos_z[], float const widht[], float const depth[], TheEngine& dev) {
        for(uint8_t i {0}; i < num; i++)
            LM.createHitBox(static_cast<double>(pos_x[i]), pos_y, static_cast<double>(pos_z[i]),widht[i], height, depth[i], dev);
    }
};