#pragma once
#include "../util/types.hpp"

struct TheEngine;
struct LevelMan;
struct GraphicEngine;

struct LogicSystem {
    using SYSCMPs       = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSCMP_Player = MP::Typelist<SoundCmp>;
    using SYSTAGs       = MP::Typelist<TInteract>;
    using SYSTAG_Player = MP::Typelist<TPlayer>;
    using SYSTAG_Walls  = MP::Typelist<TWall>;

    static constexpr double PI { std::numbers::pi };

    /*VIEJO*/ void update (LevelMan& LM, TheEngine& eng, double dt);
    /*NUEVO*/ void update2(LevelMan& LM, GraphicEngine& GE, double dt);

    void colisionWall(EntyMan& EM, Enty& current, Enty& colisioned, double dt);

    /*VIEJO*/ void colisionPlayer(LevelMan& LM, TheEngine& eng, Enty& current, Enty& colisioned, double dt);
    /*NUEVO*/ void colisionPlayer2(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned, double dt);

    /*VIEJO*/ void colisionEnemy(LevelMan& LM, TheEngine& eng, Enty& current, Enty& colisioned, double dt);
    /*NUEVO*/ void colisionEnemy2(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned, double dt);

    /*VIEJO*/ void colisionBullet(EntyMan& EM, Enty& current, Enty& colisioned);
    

    //void colisionEneBullet(EntyMan& EM, Enty& current, Enty& colisioned);
    void colisionWeapon(LevelMan& LM, Enty& current, Enty& colisioned, TheEngine& eng);
    //void colisionDoor(EntyMan& EM, Enty& current, Enty& colisioned);
    //void colisionKey(EntyMan& EM, Enty& current, Enty& colisioned);
    void receiveEntityDamage(LevelMan& LM, TheEngine& eng, Enty& receptor, Enty& agressor);
    void reciveDamge(EntyMan& EM, Enty& receptor, Enty& agressor);
    void markDestroy(Enty& enty_to_dele) { enty_to_dele.setDestroy(); }
    void cancelMove(EntyMan& EM, Enty& ent_move, double dt);
    void takeWeapon(Enty& player, Enty& weapon, LevelMan& LM, TheEngine& eng);
    //void openDoor();
    //void takeKey();
    //void resetCollision(EstadoCmp& recept_state, EstadoCmp& agress_state);
    void resetCollision(EstadoCmp& state);
    void soundMonster(EntyMan& EM, Enty& e);
    void partialVelocities(EntyMan& EM, Enty& player, double dt);
    void preCalculation(PhysicsCmp2& copy_physics, bool const is_enemy, double const dt);
    void secondStep(EntyMan& EM, PhysicsCmp2& copy_physics, PhysicsCmp2& phy, EstadoCmp& state, size_t const wall_id, float const dx, float const dz, double const dt);
    bool checkFutureCollision(EntyMan& EM, size_t const colld_id, float const f_coordx, float const f_coordz, float const width, float const depth) const noexcept;
};