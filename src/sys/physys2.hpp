#pragma once
#include "../util/types.hpp"
#include <cmath>
#include <numbers>

struct PhySys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using PlayTAGs = MP::Typelist<TPlayer>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr double PI { std::numbers::pi };

    void update(EntyMan& EM, double delta) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& en, PhysicsCmp2& physic) {
                if(en.hasTAG<TBullet>() || en.hasTAG<TEneBullet>()) bulletPhysics(physic);
                else{
                    bool player_or_enemy_not_shooting = !(en.hasCMP<AICmp>() && EM.getComponent<AICmp>(en).behaviour==SB::Shoot);
                    bool enemy_is_diying              =  (en.hasCMP<AICmp>() && EM.getComponent<AICmp>(en).behaviour==SB::Diying);
                    
                    if(enemy_is_diying) { physic.y -= 0.1; }
                    else if(player_or_enemy_not_shooting){
                        entityPhysics(en.hasTAG<TPlayer>(), physic, delta);  
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

    void entityPhysics(bool const is_player, PhysicsCmp2& p, double const dt) const noexcept{
        p.orieny += dt * p.v_ang;
        while (p.orieny > 2*PI) p.orieny -= 2*PI;
        while (p.orieny < 0)    p.orieny += 2*PI;

        if(is_player) {
            //std::cout<<"Jugador: "<<p.orieny<<"\n";
            p.vx =  p.v_lin * std::sin(p.orieny) + p.partial_x;
            p.vz =  p.v_lin * std::cos(p.orieny) + p.partial_z;
        }
        else {
            p.vx =  p.v_lin * std::cos(p.orieny) + p.partial_x;
            p.vz =  p.v_lin * std::sin(p.orieny) + p.partial_z;
        }

        p.x += dt * p.vx;
        p.z += dt * p.vz;

        p.partial_x = 0;
        p.partial_z = 0;
        p.v_lin += dt * p.a_lin;
        p.v_ang += dt * p.a_ang;
        p.v_lin = irr::core::clamp(p.v_lin, -p.kMxVLin, p.kMxVLin);
        p.v_ang = irr::core::clamp(p.v_ang, -p.kMxVAng, p.z);

        auto roz = dt * std::fabs(p.v_lin) * (p.kRoz);
        if(p.v_lin > 0) p.v_lin -= roz;
        else            p.v_lin += roz;  
    }

    void update_after_colision(EntyMan& EM, double dt) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& en, PhysicsCmp2& p) {
                if((en.hasTAG<TPlayer>() || en.hasTAG<TEnemy>()) && en.hasCMP<EstadoCmp>()){
                    if(EM.getComponent<EstadoCmp>(en).wall_collision){
                        p.x -= dt * p.vx;
                        p.z -= dt * p.vz;

                        p.x += dt * p.partial_x;
                        p.z += dt * p.partial_z;
                        EM.getComponent<EstadoCmp>(en).wall_collision=false;
                    }
                }
            }
        );
    }
};