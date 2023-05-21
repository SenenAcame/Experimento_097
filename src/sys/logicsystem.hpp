#pragma once
#include "../util/types.hpp"
#include "UIsys.hpp"

//struct TheEngine;
struct LevelMan;
struct GraphicEngine;

struct LogicSystem {
    using SYSCMPs       = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSCMP_Player = MP::Typelist<SoundCmp>;
    using SYSTAGs       = MP::Typelist<TInteract>;
    using SYSTAG_Player = MP::Typelist<TPlayer>;
    using SYSTAG_Walls  = MP::Typelist<TWall>;

    static constexpr double PI { std::numbers::pi };

    void update2      (LevelMan& LM, GraphicEngine& GE, double dt, UIsys& UISys, bool& dead);
    void checkColision(LevelMan& LM, GraphicEngine& GE, Enty& entity, EstadoCmp& state, UIsys& UISys, double dt);

    void colisionWall     (EntyMan& EM, Enty& current, Enty& colisioned, double dt);
    void colisionPlayer2  (LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned, double dt, UIsys& UISys);
    void colisionEnemy2   (LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned, double dt, UIsys& UISys);
    void colisionEneBullet(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned);
    void colisionBullet   (LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned);
    void colisionWeapon2  (LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned);
    void colisionPowerUp  (LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned);

    void receiveEntityDamage2(LevelMan& LM, GraphicEngine& GE, Enty& receptor, Enty& agressor, UIsys& UISys);
    void reciveDamge(LevelMan& LM, GraphicEngine& GE, Enty& receptor, Enty& agressor);
    void markDestroy(Enty& enty_to_dele) { enty_to_dele.setDestroy(); }
    void cancelMove(EntyMan& EM, Enty& ent_move, double dt);
    void takeWeapon2(LevelMan& LM, GraphicEngine& GE, Enty& player, Enty& weapon);
    void increaseStat(EntyMan& EM, Enty& player, Enty& power);

    void resetCollision(EstadoCmp& state);
    void soundMonster(EntyMan& EM, Enty& e);
    void partialVelocities(EntyMan& EM, Enty& player, double dt);
    void preCalculation(PhysicsCmp2& copy_physics, double const dt);
    void secondStep(EntyMan& EM, PhysicsCmp2& copy_physics, PhysicsCmp2& phy, EstadoCmp& state, size_t const wall_id, float const dx, float const dz, double const dt);
    bool checkFutureCollision(EntyMan& EM, size_t const colld_id, float const f_coordx, float const f_coordz, float const width, float const depth) const noexcept;
    void chanceDrop(LevelMan& LM, GraphicEngine& GE, PhysicsCmp2& phy);
};