#pragma once
#include "../util/types.hpp"
#include <irrlicht/irrMath.h>
#include <numbers>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr auto PI { std::numbers::pi };

    constexpr double arcTan(double const y, double const x) const noexcept{
        double arctan = std::atan2(y, x);
        while (arctan < 0) arctan += 2*PI;
        return arctan;
    }

    double capLimits(double const value, double const limit) const noexcept{
        return irr::core::clamp(value, -limit, limit);
    }

    constexpr double distancePoints(double const a, double const b) const noexcept{
        return a - b;
    }

    constexpr double distanceModule(double const x, double const y) const noexcept{
        return std::sqrt(x*x + y*y);
    }

    constexpr double distanceAngle(double const a, double const b) const noexcept{
        double angDist = a - b;
        while (angDist >  PI) angDist -= 2*PI;
        while (angDist < -PI) angDist += 2*PI;
        return angDist;
    }

    constexpr double angularVelocity(double const dx, double const dz, double const orieny, double const time) const noexcept{
        auto t_ang      { arcTan(dz, dx) };
        auto t_ang_dist { distanceAngle(t_ang, orieny) };
        double ang_vel  { t_ang_dist / time };
        return ang_vel;
    }

    constexpr void arrive(AICmp& a, PhysicsCmp2& p) const noexcept{
        p.v_ang = p.a_lin = 0;

        auto t_dx       { distancePoints(a.ox, p.x) };
        auto t_dz       { distancePoints(a.oz, p.z) };
        auto t_lin_dist { distanceModule(t_dx, t_dz) };

        if  (t_lin_dist < a.arrivalRadius) { a.enable = false; return; }

        auto t_ang_vel  { angularVelocity(t_dx, t_dz, p.orieny, a.timeArrive) };

        auto t_lin_vel  { capLimits(t_lin_dist/a.timeArrive, p.kMxVLin) };
        auto t_lin_acc  { (t_lin_vel - p.v_lin)/a.timeArrive };

        p.a_lin = capLimits(t_lin_acc, p.kMxALin);
        p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

    void seek(AICmp& a, PhysicsCmp2& p, Enty& e) const noexcept{
        p.v_ang = p.a_lin = 0;

        auto t_dx       { distancePoints(a.ox, p.x) };
        auto t_dz       { distancePoints(a.oz, p.z) };

            auto t_ang_vel  { angularVelocity(t_dx, t_dz, p.orieny, a.timeArrive) };

            auto mod        { std::fabs(t_ang_vel) };
            auto t_lin_acc  { (p.kMxVLin / (1+mod)) / a.timeArrive };

            p.a_lin = capLimits(t_lin_acc, p.kMxALin);
            p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

    constexpr void shoot(AICmp& a, PhysicsCmp2& p, EntyMan& EM, TheEngine& eng, Enty& enem) const noexcept{
        if(a.shoot){
            auto dPX = distancePoints(a.ox,p.x);
            auto dPZ = distancePoints(a.oz,p.z);
            auto dM  = distanceModule(dPX, dPZ);

            Enty& bullet  = EM.createEntity();
            auto& stats = EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{.damage=50.f, .speed=0.2f, .bulletRad=0.5f}); 
            EM.addComponent<PhysicsCmp2>(
                bullet, PhysicsCmp2{
                    .x  = p.x,
                    .y  = p.y,
                    .z  = p.z,
                    .vx = dPX/dM * stats.speed,
                    .vy = 0,
                    .vz = dPZ/dM * stats.speed
                }
            );
            
            EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
            EM.addComponent<EstadoCmp>  (bullet);
            EM.addComponent<SelfDestCmp>(bullet);
            EM.addTag<TEneBullet>(bullet);
            a.shoot = false;
        }
    }

    void patrol(AICmp& a, PhysicsCmp2& p, Enty& e) const noexcept{
        p.v_ang = p.a_lin = 0;

        auto t_dx       { distancePoints(a.ox, p.x) };
        auto t_dz       { distancePoints(a.oz, p.z) };

        auto t_ang_vel  { angularVelocity(t_dx, t_dz, p.orieny, a.timeArrive) };

        auto mod        { std::fabs(t_ang_vel) };
        auto t_lin_acc  { (p.kMxVLin / (1+mod)) / a.timeArrive };

        p.a_lin = capLimits(t_lin_acc, p.kMxALin);
        p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

    constexpr void percept(BlackBoardCmp& board, AICmp& ai, double delta) noexcept{
        ai.time += delta;
        if( ai.time <= ai.cooldown) return;

        ai.time -= ai.cooldown;

        if(ai.behaviour!=SB::Patrol){
            ai.ox = board.tx;
            ai.oz = board.tz;
            ai.shoot = board.shoot;
        }
    }

    void update(EntyMan& EM, double dt, TheEngine& dev) {
        auto& bb = EM.getBoard();

        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& a, PhysicsCmp2& p) {
                //if(e.getDestroy()){
                //    std::cout<<"Entro\n";
                //    if(a.enable){
                //        EM.getComponent<SoundCmp>(e).parametro=2;
                //        EM.getComponent<SoundCmp>(e).cambia=true;
                //        EM.getComponent<SoundCmp>(e).play=true;
                //        for(auto& en : EM.getEntities()){
                //            if(en.hasTAG<TPlayer>()){
                //                EM.getComponent<SoundCmp>(en).parametro=1;
                //                EM.getComponent<SoundCmp>(en).cambia=true;
                //                EM.getComponent<SoundCmp>(en).play=true;
                //            }
                //        }
                //    }
                //    //a.enable=false;
                //}

                percept(bb, a, dt);

                if(!a.enable) return;

                switch(a.behaviour){
                    case SB::Arrive: arrive(a,p); break;
                    case SB::Seek:   seek  (a,p,e); break;
                    case SB::Shoot:  shoot (a, p, EM, dev, e); break;
                    case SB::Patrol: patrol(a, p,e);break;
                }
            }
        );
    }
};