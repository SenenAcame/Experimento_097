#include "physys2.hpp"

void PhySys2::update(EntyMan& EM, double delta) {
    EM.foreach<prueba, SYSTAGs>(
        [&](Enty& enty, PhysicsCmp2& physic, RenderCmp2& rend) {
            bool is_bullet = enty.hasTAG<TBullet>() || enty.hasTAG<TEneBullet>();
            
            if(is_bullet) bulletPhysics(physic);
            else          entityPhysics(physic, delta); 
        }
    );
}

void PhySys2::update_after_colision(EntyMan& EM, double dt) {
    EM.foreach<POSTCOLLCMPs, SYSTAGs>(
        [&](Enty& en, PhysicsCmp2& phy, EstadoCmp& state) {
            bool entity_collide_with_wall = (en.hasTAG<TPlayer>() || en.hasTAG<TEnemy>()) && state.wall_collision;
            
            if(entity_collide_with_wall) partial_velocities(phy, state, dt); 
        }
    );
}

void PhySys2::bulletPhysics(PhysicsCmp2& p) const noexcept{
    p.x += p.vx;
    p.y += p.vy;
    p.z += p.vz;
}

void PhySys2::entityPhysics(PhysicsCmp2& phy, double const dt) const noexcept{
    calculatePosition(phy, dt);

    phy.v_lin += dt * phy.a_lin;
    phy.v_ang += dt * phy.a_ang;

    phy.v_lin = std::clamp(phy.v_lin, -phy.kMxVLin, phy.kMxVLin);
    phy.v_ang = std::clamp(phy.v_ang, -phy.kMxVAng, phy.kMxVAng);

    auto roz = dt * std::fabs(phy.v_lin) * (phy.kRoz);
    if(phy.v_lin > 0) phy.v_lin -= roz;
    else              phy.v_lin += roz;  
}

void PhySys2::calculatePosition(PhysicsCmp2& p, double const dt) {
    p.orieny += dt * p.v_ang;

    while (p.orieny > 2*PI) p.orieny -= 2*PI;
    while (p.orieny < 0)    p.orieny += 2*PI;

    p.vx =  p.v_lin * std::cos(p.orieny);
    p.vz =  p.v_lin * std::sin(p.orieny);

    p.x += dt * p.vx;
    p.z += dt * p.vz;
}

void PhySys2::partial_velocities(PhysicsCmp2& phy, EstadoCmp& state, const double dt) {
    phy.x -= dt * phy.vx;
    phy.z -= dt * phy.vz;

    phy.x += dt * phy.partial_x;
    phy.z += dt * phy.partial_z;

    phy.partial_x = 0;
    phy.partial_z = 0;

    state.wall_collision = false;
}