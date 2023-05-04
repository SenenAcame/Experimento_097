#pragma once
#include "../util/types.hpp"

struct LevelMan;
struct TheEngine;

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;
    static constexpr double pos_y = 9;
    static constexpr float height = 10;
    static constexpr float thick  = 0.1f;

    void update(EntyMan& EM);

    [[nodiscard]] static constexpr float calculateDist(float const main_pos, float const coll_pos, float const main_dim, float const coll_dim) noexcept;

    /*VIEJO*/ void static init_Hitoxes_Map(LevelMan& LM) noexcept;
    /*VIEJO*/ void static init_Hitoxes_Map2(LevelMan& LM) noexcept;

    ////salas del mapa original
    ///*VIEJO*/ void static hitboxesMapaOriginalSala_Inicio(LevelMan& LM) noexcept;
    ///*VIEJO*/ void static hitboxesMapaOriginalInicio_Adyacente(LevelMan& LM) noexcept;
    ///*VIEJO*/ void static hitboxesMapaOriginalPatio(LevelMan& LM) noexcept;
    ///*VIEJO*/ void static hitboxesMapaOriginalPatio_Adyacente(LevelMan& LM) noexcept;
    ///*VIEJO*/ void static hitboxesMapaOriginalSala_Alejada(LevelMan& LM) noexcept;
    ///*VIEJO*/ void static hitboxesMapaOriginalPasillo1(LevelMan& LM) noexcept;
    ///*VIEJO*/ void static hitboxesMapaOriginalPasillo2(LevelMan& LM) noexcept;
    ///*VIEJO*/ void static hitboxesMapaOriginalPasillo3(LevelMan& LM) noexcept;

    //salas del mapa simple
    void static hitboxesMapaSimpleSala1(LevelMan& LM) noexcept;
    void static hitboxesMapaSimpleSala2(LevelMan& LM) noexcept;
    void static hitboxesMapaSimpleSala3(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo1(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo2(LevelMan& LM) noexcept;
    void static hitboxesMapaSimplePasillo3(LevelMan& LM) noexcept;

    void static create_HitBoxes(uint8_t const num, LevelMan& LM, float const pos_x[], float const pos_z[], float const widht[], float const depth[]);
};