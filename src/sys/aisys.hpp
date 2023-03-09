#pragma once
#include "../util/types.hpp"
#include <irrlicht/irrMath.h>
#include <numbers>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr auto PI { std::numbers::pi };

    struct Point { double x { 0.0 }, z { 0.0 }; };

    [[nodiscard]] constexpr double arcTan(Point const point) const noexcept {
        double arctan = std::atan2(point.z, point.x);
        while (arctan < 0) arctan += 2*PI;
        return arctan;
    }

    [[nodiscard]] double capLimits(double const value, double const limit) const noexcept {
        return irr::core::clamp(value, -limit, limit);
    }

    [[nodiscard]] constexpr double distancePoints(double const a, double const b) const noexcept {
        return a - b;
    }

    [[nodiscard]] constexpr double distanceModule(Point const dist) const noexcept {
        return std::sqrt(dist.x*dist.x + dist.z*dist.z);
    }

    [[nodiscard]] constexpr double distanceAngle(double const a, double const b) const noexcept {
        double angDist = a - b;
        while (angDist >  PI) angDist -= 2*PI;
        while (angDist < -PI) angDist += 2*PI;
        return angDist;
    }

    [[nodiscard]] constexpr double angularVelocity(Point const dist, double const orieny, double const time) const noexcept {
        auto t_ang      { arcTan(dist) };
        auto t_ang_dist { distanceAngle(t_ang, orieny) };
        double ang_vel  { t_ang_dist / time };
        return ang_vel;
    }

    constexpr void arrive(AICmp& a, PhysicsCmp2& p) const noexcept {
        p.v_ang = p.a_lin = 0;
        Point t_dist { distancePoints(a.ox, p.x), distancePoints(a.oz, p.z) };

        auto t_lin_dist { distanceModule(t_dist) };

        if  (t_lin_dist < a.arrivalRadius) { a.enable = false; return; }

        auto t_ang_vel  { angularVelocity(t_dist, p.orieny, a.timeArrive) };

        auto t_lin_vel  { capLimits(t_lin_dist/a.timeArrive, p.kMxVLin) };
        auto t_lin_acc  { (t_lin_vel - p.v_lin)/a.timeArrive };

        p.a_lin = capLimits(t_lin_acc, p.kMxALin);
        p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

    void seek(Point const target, PhysicsCmp2& phyEnem, double const timeArrive) const noexcept {
        Point t_dist { distancePoints(target.x, phyEnem.x), distancePoints(target.z, phyEnem.z) };

        auto t_ang_vel { angularVelocity(t_dist, phyEnem.orieny, timeArrive) };

        auto mod       { std::fabs(t_ang_vel) };
        auto t_lin_acc { (phyEnem.kMxVLin / (1+mod)) / timeArrive };

        phyEnem.a_lin = capLimits(t_lin_acc, phyEnem.kMxALin);
        phyEnem.v_ang = capLimits(t_ang_vel, phyEnem.kMxVAng);
    }

    void persue(AICmp& ai, PhysicsCmp2& phyEnem, PhysicsCmp2& phyPlayer) {
        Point t_dist { distancePoints(ai.ox, phyEnem.x), distancePoints(ai.oz, phyEnem.z) };
        auto t_lin_dist { distanceModule(t_dist) };
        auto time { t_lin_dist / phyEnem.kMxVLin };
        Point predict {
            phyPlayer.x + phyPlayer.vx * time,
            phyPlayer.z + phyPlayer.vz * time
        };
        seek(predict, phyEnem, ai.timeArrive);
    }

    constexpr void shoot(AICmp& a, PhysicsCmp2& p, EntyMan& EM, TheEngine& eng, Enty& enem) const noexcept {
        if(a.shoot){
            Point t_dist { distancePoints(a.ox, p.x), distancePoints(a.oz, p.z) };

            auto dM { distanceModule(t_dist) };

            Enty& bullet  = EM.createEntity();
            auto& stats = EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{.damage=EM.getComponent<EstadisticaCmp>(enem).damage, .speed=0.8f, .bulletRad=0.5f}); 
            EM.addComponent<PhysicsCmp2>(
                bullet, PhysicsCmp2{
                    .x  = p.x,
                    .y  = p.y,
                    .z  = p.z,
                    .vx = t_dist.x/dM * stats.speed,
                    .vy = 0,
                    .vz = t_dist.z/dM * stats.speed
                }
            );
            EM.addComponent<RenderCmp2> (bullet, eng.createSphere(EM.getComponent<EstadisticaCmp>(bullet).bulletRad));
            EM.addComponent<EstadoCmp>  (bullet);
            EM.addComponent<SelfDestCmp>(bullet, SelfDestCmp{.cooldown=10});
            EM.addTag<TEneBullet>(bullet);
            EM.addTag<TInteract> (bullet);

            a.shoot = false;
        }
    }

    constexpr void percept(BlackBoardCmp& board, AICmp& ai, double delta) noexcept {
        ai.time += delta;
        if( ai.time <= ai.cooldown) return;

        ai.time -= ai.cooldown;

        if(ai.behaviour!=SB::Patrol){
            ai.ox = board.tx;
            ai.oz = board.tz;
            ai.entyID = board.entyID;
            ai.shoot = board.shoot;
        }
    }

    void update(EntyMan& EM, double dt, TheEngine& dev) {
        auto& bb = EM.getBoard();

        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& ai, PhysicsCmp2& phy) {
                percept(bb, ai, dt);

                if(!ai.enable) return;

                switch(ai.behaviour){
                    case SB::Arrive: arrive(ai, phy); break;
                    case SB::Seek:   seek  ({ ai.ox, ai.oz }, phy, ai.timeArrive); break;
                    case SB::Shoot:  shoot (ai, phy, EM, dev, e); break;
                    case SB::Patrol: seek  ({ ai.ox, ai.oz }, phy, ai.timeArrive); break;
                    case SB::Persue: {
                        auto& player = EM.getEntityById(bb.entyID);
                        auto& phyPlayer = EM.getComponent<PhysicsCmp2>(player);
                        persue(ai, phy, phyPlayer); 
                        break;
                    }
                }
            }
        );
    }
};