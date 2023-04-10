#pragma once
#include "../util/types.hpp"

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using POSTCOLLCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<>;

    static constexpr double PI { std::numbers::pi };

    void update(EntyMan& EM, double delta);
    void update_after_colision(EntyMan& EM, double dt);
    void bulletPhysics(PhysicsCmp2& p) const noexcept;
    void entityPhysics(bool const is_enemy, PhysicsCmp2& phy, double const dt) const noexcept;
    static void calculatePosition(bool const is_enemy, PhysicsCmp2& p, double const dt);
    void partial_velocities(PhysicsCmp2& phy, EstadoCmp& state, double const dt);
};