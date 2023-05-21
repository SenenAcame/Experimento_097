#include "aisys.hpp"
#include "../man/levelman.hpp"
#include "../eng/engine2.hpp"
//#include "../eng/engine.hpp"

[[nodiscard]] constexpr double AISys::arcTan(Point const point) const noexcept {
    double arctan = std::atan2(point.z, point.x);
    while (arctan < 0) arctan += 2*PI;
    return arctan;
}

[[nodiscard]] double AISys::capLimits(double const value, double const limit) const noexcept {
    return std::clamp(value, -limit, limit);
}

[[nodiscard]] constexpr double AISys::distanceModule(Point const dist) const noexcept {
    return std::sqrt(dist.x*dist.x + dist.z*dist.z);
}

[[nodiscard]] constexpr double AISys::distance(Point const target, Point const origin) const noexcept {
    Point p_dist { target.x - origin.x, target.z - origin.z };
    return distanceModule(p_dist);
}

[[nodiscard]] constexpr double AISys::distanceAngle(double const a, double const b) const noexcept {
    double angDist = a - b;
    while (angDist >  PI) angDist -= 2*PI;
    while (angDist < -PI) angDist += 2*PI;
    return angDist;
}

[[nodiscard]] constexpr double AISys::angularVelocity(Point const dist, double const orieny, double const time) const noexcept {
    auto t_ang      { arcTan(dist) };
    auto t_ang_dist { distanceAngle(t_ang, orieny) };
    double ang_vel  { t_ang_dist / time };
    return ang_vel;
}

constexpr void AISys::shoot2(LevelMan& LM, GraphicEngine& GE, Enty const& enem, AICmp& ai, PhysicsCmp2& phy) const noexcept {
    phy.a_lin = phy.v_lin = 0;

    if(!ai.shoot) return;

    Point t_dist    { ai.ox - phy.x, ai.oz - phy.z };
    auto dM { distanceModule(t_dist) };

    auto& EM = LM.getEM();
    auto& eneStats = EM.getComponent<EstadisticaCmp>(enem);

    LM.createEneBullet(
        GE, 
        { .x = phy.x, .y = phy.y, .z = phy.z, .vx = t_dist.x/dM, .vz = t_dist.z/dM },
        eneStats.damage
    );

    ai.shoot = false;
}

void AISys::seek(Point const target, PhysicsCmp2& phyEnem, double const timeArrive) const noexcept {
    Point t_dist { target.x - phyEnem.x, target.z - phyEnem.z };
    auto t_ang_vel { angularVelocity(t_dist, phyEnem.orieny, timeArrive) };

    auto mod       { std::fabs(t_ang_vel) };
    auto t_lin_acc { (phyEnem.kMxVLin / (1+mod)) / timeArrive };

    phyEnem.a_lin = capLimits(t_lin_acc, phyEnem.kMxALin);
    phyEnem.v_ang = capLimits(t_ang_vel, phyEnem.kMxVAng);
}

void AISys::persue(Point const target, PhysicsCmp2& phyEnem, Point const velPlayer, double const timeArrive) const noexcept {
    auto t_lin_dist { distance(target, {phyEnem.x, phyEnem.z}) };
    auto time { t_lin_dist / phyEnem.kMxVLin };

    Point predict {
        target.x + velPlayer.x * time,
        target.z + velPlayer.z * time
    };
    seek(predict, phyEnem, timeArrive);
}

void AISys::twoSteps(AICmp& ai, PhysicsCmp2& phyEnem, Point const velPlayer, int const sala) const noexcept {
    Point target { ai.ox, ai.oz };
    auto t_lin_dist { distance(target, { phyEnem.x, phyEnem.z }) };
    
    if(t_lin_dist <= ai.rad) seek(target, phyEnem, ai.timeArrive);
    else {
        bool inRoom { sala == 0 ||sala == 3 ||sala == 6 ||sala == 11 ||sala == 13 };

        if(inRoom) ai.rad = 5.;
        else       ai.rad = 1.;

        ai.flock_x = cos(ai.ang) * ai.rad;
        ai.flock_z = sin(ai.ang) * ai.rad;
        
        Point flock_targ { ai.flock_x + ai.ox, ai.flock_z + ai.oz };
        seek(flock_targ, phyEnem, ai.timeArrive);
    }
}

constexpr void AISys::percept(BlackBoardCmp const& board, AICmp& ai, double const delta) const noexcept {
    ai.time += delta;
    if(ai.time <= ai.cooldown) return;

    ai.time -= ai.cooldown;

    if(ai.behaviour != SB::Patrol){
        ai.ox = board.tx;
        ai.oz = board.tz;
        ai.entyID = board.entyID;
        ai.shoot = board.shoot;
    }
}

void AISys::find(AICmp& ai, PhysicsCmp2& phy){
    double desv_x=0;
    double desv_z=0;
    if(ai.ruta.size()>1){
        
        /*if(ai.xrand)
            desv_x+=ai.random;
        else
            desv_x-=ai.random;
        if(ai.zrand)
            desv_z+=ai.random;
        else
            desv_z-=ai.random;*/
        float dist_nodos=sqrt((ai.ruta.at(ai.ruta.size()-1).coord.x-ai.ruta.at(ai.ruta.size()-2).coord.x)*(ai.ruta.at(ai.ruta.size()-1).coord.x-ai.ruta.at(ai.ruta.size()-2).coord.x)+(ai.ruta.at(ai.ruta.size()-1).coord.z-ai.ruta.at(ai.ruta.size()-2).coord.z)*(ai.ruta.at(ai.ruta.size()-1).coord.z-ai.ruta.at(ai.ruta.size()-2).coord.z));
        float dist_ene_nodo=sqrt((phy.x-ai.ruta.at(ai.ruta.size()-2).coord.x)*(phy.x-ai.ruta.at(ai.ruta.size()-2).coord.x)+(phy.z-ai.ruta.at(ai.ruta.size()-2).coord.z)*(phy.z-ai.ruta.at(ai.ruta.size()-2).coord.z));
        if(dist_ene_nodo<=dist_nodos)
            ai.ruta.pop_back();
        //else if(phy.x>=ai.ruta.at(ai.ruta.size()-1).coord.x-1+desv_x && phy.x<=ai.ruta.at(ai.ruta.size()-1).coord.x+1+desv_x && phy.z>=ai.ruta.at(ai.ruta.size()-1).coord.z-1+desv_z && phy.z<=ai.ruta.at(ai.ruta.size()-1).coord.z+1+desv_z){
        //    ai.ruta.pop_back();
        //}
    }
    if(ai.ruta.size()>0){
        ai.ox=ai.ruta.at(ai.ruta.size()-1).coord.x+desv_x;
        ai.oz=ai.ruta.at(ai.ruta.size()-1).coord.z+desv_z;
        seek  ({ ai.ox, ai.oz }, phy, ai.timeArrive);
    }
}

void AISys::die(Enty& enemy, PhysicsCmp2& phyEnem, RenderCmp2& renderEne) const noexcept {
    renderEne.node->rotate( {-1, 0, 0});
    auto rot = renderEne.node->getRotation();
    phyEnem.y -= 0.01;
    if(rot.x <= -90) enemy.setDestroy();
}

/*NUEVO*/ void AISys::update2(LevelMan& LM, GraphicEngine& GE, double dt) {
    auto& EM = LM.getEM();
    auto& bb = EM.getBoard();

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& entity, AICmp& ai, PhysicsCmp2& phy, RenderCmp2& render) {
            percept(bb, ai, dt);
            if(!ai.enable) return;

            switch(ai.behaviour) {
                case SB::Patrol: find  (ai, phy); break;
                case SB::Shoot:  shoot2(LM, GE, entity, ai, phy);
                case SB::Two_Steps: {
                    auto& player     = EM.getEntityById(bb.entyID);
                    auto& phyPlayer  = EM.getComponent<PhysicsCmp2>(player);
                    auto& salaPlayer = EM.getComponent<SalaCmp>(player);
                    twoSteps(ai, phy, { phyPlayer.vx, phyPlayer.vz }, salaPlayer.sala); 
                    break;
                }
                case SB::Persue: {
                    auto& player    = EM.getEntityById(bb.entyID);
                    auto& phyPlayer = EM.getComponent<PhysicsCmp2>(player);
                    persue({ ai.ox, ai.oz }, phy, { phyPlayer.vx, phyPlayer.vz }, ai.timeArrive); 
                    break;
                }
                case SB::Diying: die(entity, phy, render); break;
            }
        }
    );
}