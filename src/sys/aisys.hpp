#pragma once
#include "../util/types.hpp"
#include <irrlicht/irrMath.h>
#include <numbers>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr auto PI { std::numbers::pi };

     double arcTan(double const y, double const x) const {
        double arctan = std::atan2(y, x);
        while (arctan < 0) arctan += 2*PI;
        return arctan;
    }

     double capLimits(double const value, double const limit) const {
        return irr::core::clamp(value, -limit, limit);
    }

     double distancePoints(double const a, double const b) const {
        return a - b;
    }

     double distanceModule(double const x, double const y) const {
        return std::sqrt(x*x + y*y);
    }

     double distanceAngle(double const a, double const b) const {
        double angDist = a - b;
        while (angDist >  PI) angDist -= 2*PI;
        while (angDist < -PI) angDist += 2*PI;
        return angDist;
    }

     double angularVelocity(double const dx, double const dz, double const orien, double const time) const{
        auto t_ang      { arcTan(dz, dx) };
        auto t_ang_dist { distanceAngle(t_ang, orien) };
        double ang_vel  { t_ang_dist / time };
        return ang_vel;
    }

     void arrive(AICmp& a, PhysicsCmp2& p) const {
        p.v_ang = p.a_lin = 0;

        auto t_dx       { distancePoints(a.ox, p.x) };
        auto t_dz       { distancePoints(a.oz, p.z) };
        auto t_lin_dist { distanceModule(t_dx, t_dz) };

        if  (t_lin_dist < a.arrivalRadius) { a.enable = false; return; }

        auto t_ang_vel  { angularVelocity(t_dx, t_dz, p.orien, a.timeArrive) };

        auto t_lin_vel  { capLimits(t_lin_dist/a.timeArrive, p.kMxVLin) };
        auto t_lin_acc  { (t_lin_vel - p.v_lin)/a.timeArrive };

        p.a_lin = capLimits(t_lin_acc, p.kMxALin);
        p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

     void seek(AICmp& a, PhysicsCmp2& p) const {
        p.v_ang = p.a_lin = 0;

        auto t_dx       { distancePoints(a.ox, p.x) };
        auto t_dz       { distancePoints(a.oz, p.z) };

        auto t_ang_vel  { angularVelocity(t_dx, t_dz, p.orien, a.timeArrive) };

        auto mod        { std::fabs(t_ang_vel) };
        auto t_lin_acc  { (p.kMxVLin / (1+mod)) / a.timeArrive };

        p.a_lin = capLimits(t_lin_acc, p.kMxALin);
        p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

    void percept(BlackBoardCmp& board, AICmp& ai, double delta) {
        ai.time += delta;
        if( ai.time <= ai.cooldown ) return;

        ai.time -= ai.cooldown;

        if(board.tactive) {
            ai.ox = board.tx;
            ai.oz = board.tz;
            ai.behaviour = board.behaviour;
            board.tactive = false;
        }
    }

    void update(EntyMan& EM, double dt) {
        auto& bb = EM.getBoard();

        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& a, PhysicsCmp2& p) {
                if(e.hasCMP<EstadoCmp>()){
                    auto& est = EM.getComponent<EstadoCmp>(e);
                    if(est.alive){ 
                        if(a.enable){
                            EM.getComponent<SoundCmp>(e).parametro=2;
                            EM.getComponent<SoundCmp>(e).play=true;
                            for(auto& en : EM.getEntities()){
                                if(en.hasTAG<TPlayer>()){
                                    EM.getComponent<SoundCmp>(en).parametro=1;
                                    EM.getComponent<SoundCmp>(en).play=true;
                                }
                            }
                        }
                        a.enable=false;
                    }
                }

                percept(bb, a, dt);

                if(!a.enable) return;

                switch(a.behaviour){
                    case SB::Arrive: arrive(a,p); break;
                    case SB::Seek:   seek  (a,p); break;
                }
            }
        );
    }
};