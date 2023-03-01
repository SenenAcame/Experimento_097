#pragma once
#include "../util/types.hpp"
#include <cmath>
#include <numbers>

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr double PI { std::numbers::pi };

    void update(EntyMan& EM, double delta) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& en, PhysicsCmp2& physic) {
                if(en.hasTAG<TBullet>() || en.hasTAG<TEneBullet>()){
                    bulletPhysics(physic);
                }
                else{
                    bool player_or_enemy_not_shooting = !(en.hasCMP<AICmp>() && EM.getComponent<AICmp>(en).behaviour==SB::Shoot);
                    if(player_or_enemy_not_shooting){
                        entityPhysics(en, physic, delta);  
                    }
                }
            }
        );
    }

    void bulletPhysics(PhysicsCmp2& p) {
        p.x += p.vx;
        p.y += p.vy;
        p.z += p.vz;
    }

    void entityPhysics(Enty& entity, PhysicsCmp2& p, double dt) {
        p.orieny += dt * p.v_ang;
        if      (p.orieny > 2*PI) p.orieny -= 2*PI;
        else if (p.orieny < 0)    p.orieny += 2*PI;

        if(entity.hasTAG<TPlayer>()){
            p.vx =  p.v_lin * std::sin(p.orieny);
            p.vz =  p.v_lin * std::cos(p.orieny);
        }
        else{
            p.vx =  p.v_lin * std::cos(p.orieny);
            p.vz =  p.v_lin * std::sin(p.orieny);
        }

        p.x += dt * p.vx;
        p.z += dt * p.vz;

        p.v_lin += dt * p.a_lin;
        p.v_ang += dt * p.a_ang;
        p.v_lin = irr::core::clamp(p.v_lin, -p.kMxVLin, p.kMxVLin);
        p.v_ang = irr::core::clamp(p.v_ang, -p.kMxVAng, p.z);

        auto roz = dt * std::fabs(p.v_lin) * (p.kRoz);
        if(p.v_lin > 0) p.v_lin -= roz;
        else            p.v_lin += roz;  
    }
};