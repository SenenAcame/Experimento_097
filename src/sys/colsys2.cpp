#include "colsys2.hpp"
#include "../man/levelman.hpp"

void ColSys2::update(EntyMan& EM) {
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& main_entity, PhysicsCmp2 const& main_phy, EstadoCmp& main_state) {
            EM.foreach<SYSCMPs, SYSTAGs>(
                [&](Enty& collisioned_entity, PhysicsCmp2 const& collisioned_phy, EstadoCmp& collisioned_state) {
                    bool distint_entities  = main_entity.getID() != collisioned_entity.getID();
                    bool without_prev_coll = collisioned_state.colision == 0;
                    bool no_wall_with_wall = !(main_entity.hasTAG<TWall>() && collisioned_entity.hasTAG<TWall>());

                    if(distint_entities && without_prev_coll && no_wall_with_wall) {
                        float dx = calculateDist(main_phy.x, collisioned_phy.x, main_state.width,  collisioned_state.width);
                        float dy = calculateDist(main_phy.y, collisioned_phy.y, main_state.height, collisioned_state.height);
                        float dz = calculateDist(main_phy.z, collisioned_phy.z, main_state.depth,  collisioned_state.depth);

                        if(dx <= 0 && dy <= 0 && dz <= 0) {
                            shotSound(EM, main_entity, collisioned_entity);

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

[[nodiscard]] constexpr float ColSys2::calculateDist(float const main_pos, float const coll_pos, float const main_dim, float const coll_dim) noexcept {
    float d {};
    d = abs(main_pos - coll_pos);
    d -= main_dim + coll_dim;
    return d;
}

void ColSys2::shotSound(EntyMan& EM, Enty& main, Enty& collied) {
    if(collied.hasTAG<TBullet>() && main.hasTAG<TEnemy>()) {
        auto& sound = EM.getComponent<SoundCmp>(main);
        EM.changeSound(sound, 0);
    }
}

void  ColSys2::init_Hitoxes_Map2(LevelMan& LM) noexcept {
    hitboxesMapaSimpleSala1   (LM);
    hitboxesMapaSimpleSala2   (LM);
    hitboxesMapaSimpleSala3   (LM);
    hitboxesMapaSimpleSala4   (LM);
    hitboxesMapaSimpleSala5   (LM);
    hitboxesMapaSimplePatio   (LM);
    hitboxesMapaSimplePasillo1(LM);
    hitboxesMapaSimplePasillo2(LM);
    hitboxesMapaSimplePasillo3(LM);
    hitboxesMapaSimplePasillo4(LM);
    hitboxesMapaSimplePasillo5(LM);
    hitboxesMapaSimplePasillo6(LM);
    hitboxesMapaSimplePasillo7(LM);
}

void ColSys2::hitboxesMapaSimpleSala1(LevelMan& LM) noexcept {
    //Sala 1:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: {-26.5, -36.85, -47.2} 10.35
    //z: {  1.5,  -8.85, -19.2} 10.35
    //
    //Paredes con puerta en medio
    //x: {-26.5, -29.85, -33.2} 3.35
    //x: {-40.4, -43.65, -47.2} 3.25
    //z: {  1.5,  -1.85,  -5.2} 3.35
    //z: {-12.4,  -15.8, -19.2} 3.4

    float pos_x[] = {-26.5, -29.85, -43.65, -47.2, -47.2, -43.65, -29.85};
    float pos_z[] = {-8.85, -19.2,  -19.2,  -1.85, -15.8, 1.5,    1.5};
    float widht[] = {thick, 3.35,   3.25,   thick, thick, 3.25,   3.25};
    float depth[] = {10.35, thick,  thick,  3.35,  3.4,   thick,  thick};
    uint8_t num_paredes { 7 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimpleSala2(LevelMan& LM) noexcept {
    //Sala 2:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -68.8, -79.15, -89.5} 10.35
    //z: {   -12,  -1.65,   8.7} 10.35
    //
    //Paredes con puerta en medio
    //x: { -68.8, -72.15, -75.5} 3.35
    //x: { -82.7,  -86.1, -89.5} 3.4
    //z: {   8.7,   5.35,     2} 3.35 
    //z: {  -5.2,   -8.6,   -12} 3.4

    float pos_x[] = { -68.8, -68.8, -89.5, -89.5, -72.15, -86.1, -72.15, -86.1};
    float pos_z[] = { 5.35,  -8.6,  5.35,  -8.6,  -12,    -12,   8.7,    8.7};
    float widht[] = { thick, thick, thick, thick, 3.35,   3.4,   3.35,   3.4};
    float depth[] = { 3.35,  3.4,   3.35,  3.4,   thick,  thick, thick,  thick};
    uint8_t num_paredes { 8 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimpleSala3(LevelMan& LM) noexcept {
    //Sala 3:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -47.6, -57.95, -68.3} 10.35
    //z: { -47.5, -37.15, -26.8} 10.35
    //
    //Paredes con puerta en medio
    //x: { -47.6,    -51, -54.4} 3.4
    //x: { -61.6, -64.95, -68.3} 3.35
    //z: { -26.8,  -30.2, -33.6} 3.4
    //z: { -40.8, -44.15, -47.5} 3.35

    float pos_x[] = {-57.95, -47.6, -47.6,  -68.3, -68.3,  -51,   -64.95};
    float pos_z[] = {-26.8,  -30.2, -44.15, -30.2, -44.15, -47.5, -47.5};
    float widht[] = {10.35,  thick, thick,  thick, thick,  3.4,   3.35};
    float depth[] = {thick,  3.4,   3.35,   3.4,   3.35,   thick, thick};
    uint8_t num_paredes { 7 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimpleSala4(LevelMan& LM) noexcept {
    //Sala 4:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -110.6, -100.25, -89.9} 10.35 
    //z: {  -40.3,  -29.95, -19.6} 10.35 
    //
    //Paredes con puerta en medio
    //x: { -110.6, -107.2, -103.8} 3.4
    //x: {  -96.6, -93.25,  -89.9} 3.35

    float pos_x[] = { -110.6, -89.9,  -100.25, -107.2, -93.25};
    float pos_z[] = { -29.95, -29.95, -40.3,   -19.6,  -19.6};
    float widht[] = { thick,  thick,  10.35,   3.4,    3.35};
    float depth[] = { 10.35,  10.35,  thick,   thick,  thick};
    uint8_t num_paredes { 5 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimpleSala5(LevelMan& LM) noexcept {
    //Sala 5:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -68.3, -57.9,  -47.6 } 10.35 
    //z: { -82.6, -72.25, -61.9 } 10.35 
    //
    //Paredes con puerta en medio
    //x: { -68.3, -64.95, -61.6 } 3.35
    //x: { -54.4,    -51, -47.6 } 3.4

    float pos_x[] = { -68.3,  -47.6,  -57.9, -64.95, -51};
    float pos_z[] = { -72.25, -72.25, -82.6, -61.9,  -61.9};
    float widht[] = { thick,  thick,  10.35, 3.35,   3.4};
    float depth[] = { 10.35,  10.35,  thick, thick,  thick};
    uint8_t num_paredes { 5 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePatio(LevelMan& LM) noexcept {
    //Patio:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -89.5,   -58, -26.5} 31.5
    //z: {  43.8, 33.45,  23.1} 10.35
    //
    //Paredes con puerta en medio
    //x: { -89.5,  -86.1, -82.7} 3.4
    //x: { -75.5, -57.95, -40.4} 17.55
    //x: { -33.2, -29.85, -26.5} 3.35

    float pos_x[] = { -58,   -26.5, -89.5, -86.1, -57.95, -29.85};
    float pos_z[] = { 43.8,  33.45, 33.45, 23.1,  23.1,   23.1};
    float widht[] = { 31.5,  thick, thick, 3.4,   17.55,  3.35};
    float depth[] = { thick, 10.35, 10.35, thick, thick,  thick};
    uint8_t num_paredes { 6 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePasillo1(LevelMan& LM) noexcept {
    //Pasillo 1:
    //
    //Paredes con puerta en medio
    //x: { -68.8, -61.6, -54.4} 7.2
    //x: { -54.4, -50.8, -47.2} 3.6 
    //x: { -68.8, -65.2, -61.6} 3.6
    //x: { -61.6, -54.4, -47.2} 7.2
    //z: {     2,  -1.6,  -5.2} 3.6
    //z: {  -5.2,  -8.8, -12.4} 3.6

    float pos_x[] = { -61.6, -50.8, -65.2, -54.4, -54.4, -61.6};
    float pos_z[] = { 2,     -5.2,  -5.2,  -12.4, -1.6,  -8.8};
    float widht[] = { 7.2,   3.6,   3.6,   7.2,   thick, thick};
    float depth[] = { thick, thick, thick, thick, 3.6,   3.6};
    uint8_t num_paredes { 6 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePasillo2(LevelMan& LM) noexcept {
    //Pasillo 2:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -82.7, -75.5, -68.3} 7.2
    //z: {   -12, -26.4, -40.8} 14.4
    //
    //Paredes con puerta en medio
    //x: { -75.5, -71.9, -68.3} 3.6
    //z: {   -12, -22.8, -33.6} 10.8

    float pos_x[] = { -82.7, -75.5, -71.9, -75.5};
    float pos_z[] = { -26.4, -40.8, -33.6, -22.8};
    float widht[] = { thick, 7.2,   3.6,   thick};
    float depth[] = { 14.4,  thick, thick, 10.8};
    uint8_t num_paredes { 4 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePasillo3(LevelMan& LM) noexcept {
    //Pasillo 3:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -33.2, -40.4, -47.6} 7.2
    //z: { -19.2,   -30, -40.8} 10.8
    //
    //Paredes con puerta en medio
    //x: { -40.4,    -44, -47.6} 3.6
    //z: { -19.2, -26.35, -33.5} 7.15

    float pos_x[] = {-33.2, -40.4, -44,   -40.4};
    float pos_z[] = {-30,   -40.8, -33.5, -26.35};
    float widht[] = {thick, 7.2,   3.6,   thick};
    float depth[] = {10.8,  thick, thick, 7.15};
    uint8_t num_paredes { 4 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePasillo4(LevelMan& LM) noexcept {
    //Pasillo 4:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -103.9, -96.7, -89.5} 7.2
    //z: {  -19.6,  -8.8,     2} 10.8
    //
    //Paredes con puerta en medio
    //x: { -96.7, -93.1, -89.5} 3.6
    //z: { -19.6, -12.4,  -5.2} 7.2

    float pos_x[] = {-96.7, -103.9, -93.1, -96.7};
    float pos_z[] = {2,     -8.8,   -5.2,  -12.4};
    float widht[] = {7.2,   thick,  3.6,   thick};
    float depth[] = {thick, 10.8,   thick, 7.2};
    uint8_t num_paredes { 4 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePasillo5(LevelMan& LM) noexcept {
    //Pasillo 5:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -61.6,   -58, -54.4} 3.6
    //z: { -61.9, -54.7, -47.5} 7.2

    float pos_x[] = { -61.6, -54.4};
    float pos_z[] = { -54.7, -54.7};
    float widht[] = { thick, thick};
    float depth[] = { 7.2,   7.2};
    uint8_t num_paredes { 2 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePasillo6(LevelMan& LM) noexcept {
    //Pasillo 6:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -40.4, -36.8, -33.2} 3.6
    //z: {  23.1,  12.3,   1.5} 10.8

    float pos_x[] = { -40.4, -33.2};
    float pos_z[] = { 12.3,  12.3};
    float widht[] = { thick, thick};
    float depth[] = { 10.8,  10.8};
    uint8_t num_paredes { 2 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::hitboxesMapaSimplePasillo7(LevelMan& LM) noexcept {
    //Pasillo 7:
    //
    //Dimensiones
    //   extremo  mitad  extremo  dist
    //x: { -82.7, -79.1, -75.5} 3.6
    //z: {  23.1,  15.9,   8.7} 7.2

    float pos_x[] = { -82.7, -75.5};
    float pos_z[] = { 15.9,  15.9};
    float widht[] = { thick, thick};
    float depth[] = { 7.2,   7.2};
    uint8_t num_paredes { 2 };
    
    create_HitBoxes(num_paredes, LM, pos_x, pos_z, widht, depth);
}

void ColSys2::create_HitBoxes(uint8_t const num, LevelMan& LM, float const pos_x[], float const pos_z[], float const widht[], float const depth[]) {
    for(uint8_t i {0}; i < num; i++)
        LM.createHitBox(static_cast<double>(pos_x[i]), pos_y, static_cast<double>(pos_z[i]),widht[i], height, depth[i]);
}