#include "colsys2.hpp"
#include "../man/levelman.hpp"

void ColSys2::update(EntyMan& EM) {
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty const& main_entity, PhysicsCmp2 const& main_phy, EstadoCmp& main_state) {
            EM.foreach<SYSCMPs, SYSTAGs>(
                [&](Enty const& collisioned_entity, PhysicsCmp2 const& colld_phy, EstadoCmp& colld_state) {
                    bool distint_entities  = main_entity.getID() != collisioned_entity.getID();
                    bool without_prev_coll = colld_state.colision == 0;
                    bool no_wall_with_wall = !(main_entity.hasTAG<TWall>() && collisioned_entity.hasTAG<TWall>());

                    if(distint_entities && without_prev_coll && no_wall_with_wall) {
                        float dx, dy, dz;
                        dx = calculateDist(static_cast<float>(main_phy.x), static_cast<float>(colld_phy.x), main_state.width,  colld_state.width);
                        dy = calculateDist(static_cast<float>(main_phy.y), static_cast<float>(colld_phy.y), main_state.height, colld_state.height);
                        dz = calculateDist(static_cast<float>(main_phy.z), static_cast<float>(colld_phy.z), main_state.depth,  colld_state.depth);

                        if(dx<=0 && dy<=0 && dz<=0) {
                            if(collisioned_entity.hasTAG<TBullet>() && main_entity.hasTAG<TEnemy>()) {
                                auto& sound = EM.getComponent<SoundCmp>(main_entity);
                                EM.changeSound(sound, 0);
                            }

                            colld_state.colision  = 1<<1;
                            colld_state.entityCol = main_entity.getID();
                            
                            main_state.colision = 1<<1;
                            main_state.entityCol = collisioned_entity.getID();
                        }
                    }
                }
            );
        }
    );
}

[[nodiscard]] float ColSys2::calculateDist(double const main_pos, double const coll_pos, double const main_dim, double const coll_dim) noexcept {
    double d {};
    d  = abs(main_pos - coll_pos);
    d -= main_dim + coll_dim;
    return static_cast<float>(d);
}

void ColSys2::init_Hitoxes_Map(LevelMan& LM, TheEngine& dev) noexcept {
    hitboxesMapaOriginalSala_Inicio     (LM, dev);
    hitboxesMapaOriginalInicio_Adyacente(LM, dev);
    hitboxesMapaOriginalPatio           (LM, dev);
    hitboxesMapaOriginalPatio_Adyacente (LM, dev);
    hitboxesMapaOriginalSala_Alejada    (LM, dev);
    hitboxesMapaOriginalPasillo1        (LM, dev);
    hitboxesMapaOriginalPasillo2        (LM, dev);
    hitboxesMapaOriginalPasillo3        (LM, dev);
}

void  ColSys2::init_Hitoxes_Map2(LevelMan& LM, TheEngine& dev) noexcept {
    hitboxesMapaSimpleSala1   (LM, dev);
    hitboxesMapaSimpleSala2   (LM, dev);
    hitboxesMapaSimpleSala3   (LM, dev);
    hitboxesMapaSimplePasillo1(LM, dev);
    hitboxesMapaSimplePasillo2(LM, dev);
    hitboxesMapaSimplePasillo3(LM, dev);
}

void  ColSys2::hitboxesMapaOriginalSala_Inicio(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { -34.85f, -69.6f, -64.7f, -17.65f, -0.1f, -0.1f  };
    float pos_z[] = { -33.8f,  0.95f,  35.7f,  35.7f,   19.9f, -24.3f };
    float widht[] = { 34.75f,  thick,  4.9f,   17.55f,  thick, thick  };
    float depth[] = { thick,   34.75f, thick,  thick,   15.8f, 9.5f   };
    uint8_t num_paredes = 6;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaOriginalInicio_Adyacente(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { 42.6f,  28.7f,  28.7f, 14.8f,  14.8f };
    float pos_z[] = { 0.95f,  -33.8f, 35.7f, -24.7f, 23.4f };
    float widht[] = { thick,  13.9f,  13.9f, thick,  thick };
    float depth[] = { 34.75f, thick,  thick, 9.1f,   12.3f };
    uint8_t num_paredes = 5;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaOriginalPatio(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { -83.7f, -64.45f, -10.8f, -78.85f, -24.95f, -0.2f,  -0.2f  };
    float pos_z[] = { 85.4f,  50.7f,   50.7f,  120.1f,  120.1f,  58.25f, 104.5f };
    float widht[] = { thick,  19.25f,  10.6f,  4.85f,   24.75f,  thick,  thick  };
    float depth[] = { 34.7f,  thick,   thick,  thick,   thick,   7.55f,  15.6f  };
    uint8_t num_paredes = 7;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaOriginalPatio_Adyacente(LevelMan& LM, TheEngine& dev) noexcept {
    //Sala Patio Adyacente:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -83.7,  -52.4, -21.1} 31.3
    //z: { 120.1, 140.95, 161.8} 20.85

    float pos_x[] = { -52.4f, -83.7f,  -21.1f  };
    float pos_z[] = { 161.8f, 140.95f, 140.95f };
    float widht[] = { 31.3f,  thick,   thick   };
    float depth[] = { thick,  20.85f,  20.85f  };
    uint8_t num_paredes = 3;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaOriginalSala_Alejada(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { 46.05f, 77.3f,   29.5f,   72.05f,  14.8f,   14.8f   };
    float pos_z[] = { -83.f,  -110.8f, -138.6f, -138.6f, -131.1f, -88.75f };
    float widht[] = { 31.25f, thick,   14.7f,   5.25f,   thick,   thick   };
    float depth[] = { thick,  27.8f,   thick,   thick,   7.5f,    5.75f   };
    uint8_t num_paredes = 6;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaOriginalPasillo1(LevelMan& LM, TheEngine& dev) noexcept {
    //Pasillo 1:
    //
    //Dimensiones
    //  extremo  mitad  extremo  dist
    //x: {  -69.6, -34.9, -0.2} 34.7
    //z: { 35.7,    43.2, 50.7} 7.5

    float pos_x[] = { -69.6f };
    float pos_z[] = { 43.2f  };
    float widht[] = { thick  };
    float depth[] = { 7.5f   };
    uint8_t num_paredes = 1;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaOriginalPasillo2(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { 7.3f,   7.3f,   -0.2f,    14.8f,   14.8f,  14.8f  };
    float pos_z[] = { -172.f, 120.2f, -102.95f, -162.8f, -58.4f, 77.95f };
    float widht[] = { 7.5f,   7.5f,   thick,    thick,   thick,  thick  };
    float depth[] = { thick,  thick,  69.05f,   9.2f,    24.6f,  42.25f };
    uint8_t num_paredes = 6;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaOriginalPasillo3(LevelMan& LM, TheEngine& dev) noexcept {
    //Pasillo 3:
    //
    //Dimensiones
    //  extremo  mitad  extremo  dist
    //x: {  14.8,  46.05,   77.3} 31.25
    //z: { -153.6, -146.1, -138.6} 7.5

    float pos_x[] = { 77.3f,   46.05f  };
    float pos_z[] = { -146.1f, -153.6f };
    float widht[] = { thick,   31.25f  };
    float depth[] = { 7.5f,    thick   };
    uint8_t num_paredes = 2;

    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaSimpleSala1(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { -33.5f, -68.f, 1.f,    1.f,    -56.75f, -10.25f };
    float pos_z[] = { 68.f,   33.5f, 10.25f, 56.75f, -1.f,    -1.f    };
    float widht[] = { 34.5f,  thick, thick,  thick,  11.25f,  11.25f  };
    float depth[] = { thick,  34.5f, 11.25f, 11.25f, thick,   thick   };
    uint8_t num_paredes { 6 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaSimpleSala2(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { 107.5f, 142.f, 84.25f, 130.75f, 73.f,   73.f   };
    float pos_z[] = { 92.f,   57.5f, 23.f,   23.f,    34.25f, 80.75f };
    float widht[] = { 34.5f,  thick, 11.25f, 11.25f,  thick,  thick  };
    float depth[] = { thick,  34.5f, thick,  thick,   11.25f, 11.25f };
    uint8_t num_paredes { 6 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaSimpleSala3(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { 37.f,   37.f,   2.5f,    71.5f,   2.5f,    71.5f   };
    float pos_z[] = { -26.5f, -95.5f, -84.25f, -84.25f, -37.75f, -37.75f };
    float widht[] = { 34.5f,  34.5f,  thick,   thick,   thick,   thick   };
    float depth[] = { thick,  thick,  11.25f,  11.25f,  11.25f,  11.25f  };
    uint8_t num_paredes { 6 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaSimplePasillo1(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { 25.f,  49.f,  25.f,  61.f,  13.f,  49.f  };
    float pos_z[] = { 57.5f, 33.5f, 21.5f, 45.5f, 45.5f, 69.5f };
    float widht[] = { thick, thick, 24.f,  12.f,  12.f,  24.f  };
    float depth[] = { 12.f,  12.f,  thick, thick, thick, thick };
    uint8_t num_paredes { 6 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaSimplePasillo2(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { 119.5f, 95.5f, 95.5f, 83.5f };
    float pos_z[] = { -25.f,  -13.f, -73.f, -49.f };
    float widht[] = { thick,  thick, 24.f,  12.f  };
    float depth[] = { 48.f,   36.f,  thick, thick };
    uint8_t num_paredes { 4 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::hitboxesMapaSimplePasillo3(LevelMan& LM, TheEngine& dev) noexcept {
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

    float pos_x[] = { -45.5f, -21.5f, -21.5f, -9.5f };
    float pos_z[] = { -37.f,  -25.f,  -73.f,  -49.f };
    float widht[] = { thick,  thick,  24.f,   12.f  };
    float depth[] = { 36.f,   24.f,   thick,  thick };
    uint8_t num_paredes { 4 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth, dev);
}

void ColSys2::create_HitBoxes(uint8_t const num, LevelMan& LM, float const pos_x[], float const pos_z[], float const widht[], float const depth[], TheEngine& dev) {
    for(uint8_t i {0}; i < num; i++)
        LM.createHitBox(static_cast<double>(pos_x[i]), pos_y, static_cast<double>(pos_z[i]),widht[i], height, depth[i], dev);
}