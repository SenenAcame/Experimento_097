#pragma once
#include "../util/types.hpp"
#include <irrlicht/irrMath.h>
#include <numbers>

struct AISys {
    using SYSCMPs = MP::Typelist<AICmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;
    static constexpr auto PI { std::numbers::pi };

    constexpr double arcTan(double y, double x) const noexcept{
        double arctan = std::atan2(y, x);
        if (arctan < 0) arctan += 2*PI;
        return arctan;
    }

    constexpr double capLimits(double value, double limit) const noexcept{
        return irr::core::clamp(value, -limit, limit);
    }

    constexpr double distancePoints(double a, double b) const noexcept{
        return a - b;
    }

    constexpr double distanceModule(double x, double y) const noexcept{
        return std::sqrt(x*x + y*y);
    }

    constexpr double distanceAngle(double a, double b) const noexcept{
        double angDist = a - b;
        if      (angDist >  PI) angDist -= 2*PI;
        else if (angDist < -PI) angDist += 2*PI;
        return angDist;
    }

    constexpr void arrive(AICmp& a, PhysicsCmp2& p) const noexcept{
        p.v_ang = p.a_lin = 0;

        auto t_dx       { distancePoints(a.ox, p.x) };
        auto t_dz       { distancePoints(a.oz, p.z) };
        auto t_lin_dist { distanceModule(t_dx, t_dz) };

        if  (t_lin_dist < a.arrivalRadius) { a.enable = false; return; }

        auto t_lin_vel  { capLimits(t_lin_dist/a.timeArrive, p.kMxVLin) };
        auto t_lin_acc  { (t_lin_vel - p.v_lin)/a.timeArrive };
        
        auto t_ang      { arcTan(t_dz, t_dx) };
        auto t_ang_dist { distanceAngle(t_ang, p.orien) };
        auto t_ang_vel  { t_ang_dist / a.timeArrive };

        p.a_lin = capLimits(t_lin_acc, p.kMxALin);
        p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

    constexpr void seek(AICmp& a, PhysicsCmp2& p) const noexcept{
        p.v_ang = p.a_lin = 0;

        auto t_dx       { distancePoints(a.ox, p.x) };
        auto t_dz       { distancePoints(a.oz, p.z) };

        auto t_ang      { arcTan(t_dz, t_dx) };
        auto t_ang_dist { distanceAngle(t_ang, p.orien) };
        auto t_ang_vel  { t_ang_dist / a.timeArrive };

        auto mod        { std::fabs(t_ang_vel) };
        auto t_lin_acc  { (p.kMxVLin / (1+mod)) / a.timeArrive };

        p.a_lin = capLimits(t_lin_acc, p.kMxALin);
        p.v_ang = capLimits(t_ang_vel, p.kMxVAng);
    }

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, AICmp& a, PhysicsCmp2& p) {
                if(!a.enable) return;

                switch(a.behaviour){
                    case SB::Arrive: arrive(a,p); break;
                    case SB::Seek:   seek  (a,p); break;
                }
            }
        );
    }
};