#pragma once
#include "../util/types.hpp"

//struct TheEngine;
struct LevelMan;
struct GraphicEngine;

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2, RenderCmp2>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr auto PI { std::numbers::pi };

    struct Point { double x { 0.0 }, z { 0.0 }; };

    [[nodiscard]] constexpr double arcTan(Point const point) const noexcept;
    [[nodiscard]] double capLimits(double const value, double const limit) const noexcept;
    [[nodiscard]] constexpr double distanceModule(Point const dist) const noexcept;
    [[nodiscard]] constexpr double distance(Point const target, Point const origin) const noexcept;
    [[nodiscard]] constexpr double distanceAngle(double const a, double const b) const noexcept;
    [[nodiscard]] constexpr double angularVelocity(Point const dist, double const orieny, double const time) const noexcept;
    constexpr void arrive(AICmp& ai, PhysicsCmp2& phy) const noexcept;

    ///*VIEJO*/ constexpr void shoot (AICmp& ai, PhysicsCmp2 const& phy, EntyMan& EM, TheEngine& eng, Enty const& enem) const noexcept;
    /*NUEVO*/ constexpr void shoot2(LevelMan& LM, GraphicEngine& GE, Enty const& enem, AICmp& ai, PhysicsCmp2& phy) const noexcept;

    void seek(Point const target, PhysicsCmp2& phyEnem, double const timeArrive) const noexcept;
    void persue(Point const target, PhysicsCmp2& phyEnem, Point const velPlayer, double const timeArrive) const noexcept;
    void twoSteps(AICmp& ai, PhysicsCmp2& phyEnem, Point const velPlayer, int const sala) const noexcept;
    constexpr void percept(BlackBoardCmp const& board, AICmp& ai, double const delta) const noexcept;
    void die(Enty& enemy, RenderCmp2& renderEne) const noexcept;

    ///*VIEJO*/ void update(EntyMan& EM, double dt, TheEngine& dev);
    /*NUEVO*/ void update2(LevelMan& LM, GraphicEngine& GE, double dt);
};