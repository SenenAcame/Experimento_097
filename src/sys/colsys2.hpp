#pragma once
#include "../util/types.hpp"

struct LevelMan;
//struct TheEngine;

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;
    static constexpr double pos_y  = 3.5;
    static constexpr float  height = 10;
    static constexpr float  thick  = 0.01f;

    void update(EntyMan& EM);
    [[nodiscard]] static constexpr float calculateDist(float const main_pos, float const coll_pos, float const main_dim, float const coll_dim) noexcept;
    /*NUEVO*/ void shotSound(EntyMan& EM, Enty& main, Enty& collied);
    void static init_Hitoxes_Map2(LevelMan& LM) noexcept;

    //salas del mapa simple
    void static hitboxesMapaSimpleSala1   (LevelMan& LM) noexcept;
    void static hitboxesMapaSimpleSala2   (LevelMan& LM) noexcept;
    void static hitboxesMapaSimpleSala3   (LevelMan& LM) noexcept;
    void static hitboxesMapaSimpleSala4   (LevelMan& LM) noexcept;
    void static hitboxesMapaSimpleSala5   (LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePatio   (LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo1(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo2(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo3(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo4(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo5(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo6(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo7(LevelMan& LM) noexcept;

    void static create_HitBoxes(uint8_t const num, LevelMan& LM, float const pos_x[], float const pos_z[], float const widht[], float const depth[]);
};