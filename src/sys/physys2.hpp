#pragma once
#include "../util/types.hpp"
#include <cmath>
#include <numbers>


struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using POSTCOLLCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr double PI { std::numbers::pi };

    void update(EntyMan& EM, double delta) {
      
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& en, PhysicsCmp2& physic) {
                if(en.hasTAG<TBullet>() || en.hasTAG<TEneBullet>()) bulletPhysics(physic);
                else {
                    bool player_or_enemy_not_shooting = !(en.hasCMP<AICmp>() && EM.getComponent<AICmp>(en).behaviour==SB::Shoot);
                    bool enemy_is_diying              =  (en.hasCMP<AICmp>() && EM.getComponent<AICmp>(en).behaviour==SB::Diying);
                    
                    if(enemy_is_diying) { physic.y -= 0.1; }
                    else if(player_or_enemy_not_shooting){
                        entityPhysics(en.hasTAG<TEnemy>(), physic, delta);  
                    }
                }
            }
        );
    }

    void bulletPhysics(PhysicsCmp2& p) const noexcept{
        p.x += p.vx;
        p.y += p.vy;
        p.z += p.vz;
    }

    void entityPhysics(bool const is_enemy, PhysicsCmp2& phy, double const dt) const noexcept{
        calculatePosition(is_enemy, phy, dt);

        phy.v_lin += dt * phy.a_lin;
        phy.v_ang += dt * phy.a_ang;

        phy.v_lin = irr::core::clamp(phy.v_lin, -phy.kMxVLin, phy.kMxVLin);
        phy.v_ang = irr::core::clamp(phy.v_ang, -phy.kMxVAng, phy.kMxVAng);

        auto roz = dt * std::fabs(phy.v_lin) * (phy.kRoz);
        if(phy.v_lin > 0) phy.v_lin -= roz;
        else              phy.v_lin += roz;  
    }

    static void calculatePosition(bool const is_enemy, PhysicsCmp2& p, double const dt) {
        p.orieny += dt * p.v_ang;

        while (p.orieny > 2*PI) p.orieny -= 2*PI;
        while (p.orieny < 0)    p.orieny += 2*PI;

        if(is_enemy) {
            p.vx =  p.v_lin * std::cos(p.orieny);
            p.vz =  p.v_lin * std::sin(p.orieny);
        }
        else {
            p.vx =  p.v_lin * std::sin(p.orieny);
            p.vz =  p.v_lin * std::cos(p.orieny);
        }

        p.x += dt * p.vx;
        p.z += dt * p.vz;
    }

    void update_after_colision(EntyMan& EM, double dt) {
        
        EM.foreach<POSTCOLLCMPs, SYSTAGs>(
            [&](Enty& en, PhysicsCmp2& phy, EstadoCmp& state) {
                if((en.hasTAG<TPlayer>() || en.hasTAG<TEnemy>()) && state.wall_collision){
                    phy.x -= dt * phy.vx;
                    phy.z -= dt * phy.vz;

                    phy.x += dt * phy.partial_x;
                    phy.z += dt * phy.partial_z;

                    phy.partial_x = 0;
                    phy.partial_z = 0;

                    state.wall_collision = false;
                }
            }
        );
    }
};