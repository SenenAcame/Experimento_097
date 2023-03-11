#pragma once
#include "../util/types.hpp"
#include <irrlicht/irrMath.h>
#include <numbers>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2, RenderCmp2>;
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

    [[nodiscard]] constexpr double distanceModule(Point const dist) const noexcept {
        return std::sqrt(dist.x*dist.x + dist.z*dist.z);
    }

    [[nodiscard]] constexpr double distance(Point const target, Point const origin) const noexcept {
        Point p_dist { target.x - origin.x, target.z - origin.z };
        return distanceModule(p_dist);
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

    constexpr void arrive(AICmp& ai, PhysicsCmp2& phy) const noexcept {
        phy.v_ang = phy.a_lin = 0;

        Point t_dist { ai.ox - phy.x, ai.oz - phy.z };
        auto t_lin_dist { distanceModule(t_dist) };

        if  (t_lin_dist < ai.arrivalRadius) { ai.enable = false; return; }

        auto t_ang_vel  { angularVelocity(t_dist, phy.orieny, ai.timeArrive) };

        auto t_lin_vel  { capLimits(t_lin_dist/ai.timeArrive, phy.kMxVLin) };
        auto t_lin_acc  { (t_lin_vel - phy.v_lin)/ai.timeArrive };

        phy.a_lin = capLimits(t_lin_acc, phy.kMxALin);
        phy.v_ang = capLimits(t_ang_vel, phy.kMxVAng);
    }

    constexpr void shoot(AICmp& ai, PhysicsCmp2& phy, EntyMan& EM, TheEngine& eng, Enty& enem) const noexcept {
        if(ai.shoot){
            Point t_dist { ai.ox - phy.x, ai.oz - phy.z };
            auto dM { distanceModule(t_dist) };

            Enty& bullet  = EM.createEntity();
            auto& stats = EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{.damage=EM.getComponent<EstadisticaCmp>(enem).damage, .speed=0.8f, .bulletRad=0.5f}); 
            EM.addComponent<PhysicsCmp2>(
                bullet, PhysicsCmp2{
                    .x  = phy.x,
                    .y  = phy.y,
                    .z  = phy.z,
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

            ai.shoot = false;
        }
    }

    void seek(Point const target, PhysicsCmp2& phyEnem, double const timeArrive) const noexcept {
        Point t_dist { target.x - phyEnem.x, target.z - phyEnem.z };
        auto t_ang_vel { angularVelocity(t_dist, phyEnem.orieny, timeArrive) };

        auto mod       { std::fabs(t_ang_vel) };
        auto t_lin_acc { (phyEnem.kMxVLin / (1+mod)) / timeArrive };

        phyEnem.a_lin = capLimits(t_lin_acc, phyEnem.kMxALin);
        phyEnem.v_ang = capLimits(t_ang_vel, phyEnem.kMxVAng);
    }

    void persue(Point const target, PhysicsCmp2& phyEnem, Point const velPlayer, double const timeArrive) const noexcept{
        auto t_lin_dist { distance(target, {phyEnem.x, phyEnem.z}) };
        auto time { t_lin_dist / phyEnem.kMxVLin };

        Point predict {
            target.x + velPlayer.x * time,
            target.z + velPlayer.z * time
        };
        seek(predict, phyEnem, timeArrive);
    }

    void twoSteps(AICmp const& ai, PhysicsCmp2& phyEnem, Point const velPlayer) const noexcept{
        Point target { ai.ox, ai.oz };
        auto t_lin_dist { distance(target, { phyEnem.x, phyEnem.z }) };

        if(t_lin_dist <= ai.rad) {
            seek(target, phyEnem, ai.timeArrive);
            //persue(target, phyEnem, velPlayer,ai.timeArrive); 
        }
        else {
            Point flock_targ {ai.flock_x + ai.ox, ai.flock_z + ai.oz};
            seek(flock_targ, phyEnem, ai.timeArrive);
            //persue(flock_targ, phyEnem, velPlayer,ai.timeArrive);
        }
    }

    constexpr void percept(BlackBoardCmp& board, AICmp& ai, double delta) const noexcept {
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

    void die(Enty& enemy, RenderCmp2& renderEne, PhysicsCmp2& phy) const noexcept {
        float rotEneX = renderEne.n->getRotation().X;
        float rotEneY = renderEne.n->getRotation().Y;
        float rotEneZ = renderEne.n->getRotation().Z;
        renderEne.n->setRotation(irr::core::vector3df(rotEneX, rotEneY, rotEneZ+2));
        if(rotEneZ==90){
            enemy.setDestroy();
        }
    }

    void update(EntyMan& EM, double dt, TheEngine& dev) {
        auto& bb = EM.getBoard();

        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& ai, PhysicsCmp2& phy, RenderCmp2& render) {
                percept(bb, ai, dt);

                if(!ai.enable) return;

                switch(ai.behaviour){
                    case SB::Arrive: arrive(ai, phy); break;
                    case SB::Seek:   seek  ({ ai.ox, ai.oz }, phy, ai.timeArrive); break;
                    case SB::Patrol: seek  ({ ai.ox, ai.oz }, phy, ai.timeArrive); break;
                    case SB::Shoot:  shoot (ai, phy, EM, dev, e); break;
                    case SB::Two_Steps: {
                        auto& player    = EM.getEntityById(bb.entyID);
                        auto& phyPlayer = EM.getComponent<PhysicsCmp2>(player);
                        twoSteps(ai, phy, { phyPlayer.vx, phyPlayer.vz }); 
                        break;
                    }
                    case SB::Persue: {
                        auto& player    = EM.getEntityById(bb.entyID);
                        auto& phyPlayer = EM.getComponent<PhysicsCmp2>(player);
                        persue({ ai.ox, ai.oz }, phy, { phyPlayer.vx, phyPlayer.vz }, ai.timeArrive); 
                        break;
                    }
                    case SB::Diying: die(e, render, phy); break;
                }
            }
        );
    }
};