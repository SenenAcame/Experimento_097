#include "logicsystem.hpp"
#include "UIsys.hpp"
#include "colsys2.hpp"
#include "inpsys2.hpp"
#include "physys2.hpp"
#include "../man/levelman.hpp"
#include "../eng/engine2.hpp"
#include "../util/munition_aux.hpp"
#include <cstdlib>
#include <iostream>

//int aux = 0;

/*NUEVO*/ void LogicSystem::update2(LevelMan& LM, GraphicEngine& GE, double dt, UIsys& UISys, bool& dead) {
    auto& EM = LM.getEM();
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& entity, PhysicsCmp2&, EstadoCmp& state) {
            if(entity.hasTAG<TPlayer>()){
                if(EM.getComponent<EstadisticaCmp>(entity).hitpoints <= 0) {
                    dead = true;
                }
            }
            if(entity.hasTAG<TEnemy>()) {
                auto& stats = EM.getComponent<EstadisticaCmp>(entity);
                stats.ClockAttackEnemy += dt;
            }

            if(state.colision != 0) checkColision(LM, GE, entity, state, UISys, dt);
        }
    );
}

/*NUEVO*/ void LogicSystem::checkColision(LevelMan& LM, GraphicEngine& GE, Enty& entity, EstadoCmp& state, UIsys& UISys, double dt) {
    auto& EM = LM.getEM();
    auto& entity_colisioned = EM.getEntityById(state.entityCol);

    if(entity_colisioned.hasCMP<EstadoCmp>()) {
        auto& colisiones_state = EM.getComponent<EstadoCmp>(entity_colisioned);
        if(entity.hasTAG<TWall>()){
            //proceso Colision Wall
            colisionWall(EM, entity, entity_colisioned, dt);
        }
        else if(entity.hasTAG<TPlayer>()){
            //proceso Colision Jugador
            colisionPlayer2(LM, GE, entity, entity_colisioned, dt, UISys);
        }
        else if(entity.hasTAG<TEnemy>()){
            //proceso Colision Enemy
            colisionEnemy2(LM, GE, entity, entity_colisioned, dt);
        }
        else if(entity.hasTAG<TEneBullet>()){
            //proceso Colision Bullet
            colisionEneBullet(LM, GE, entity, entity_colisioned);
        }
        else if(entity.hasTAG<TBullet>()){
            //proceso Colision Bullet
            colisionBullet(LM, GE, entity, entity_colisioned);
        }
        else if(entity.hasTAG<TWeapon>()){
            //proceso Colision Weapon
            colisionWeapon2(LM, GE, entity, entity_colisioned);
        }
        else if(entity.hasTAG<TPowerUp>()){
            //proceso Colision Weapon
            colisionPowerUp(LM, GE, entity, entity_colisioned);
        }
        resetCollision(colisiones_state);
    }
    resetCollision(state);
}

void LogicSystem::colisionWall(EntyMan& EM, Enty& current, Enty& colisioned, double dt) {
    if(colisioned.hasTAG<TPlayer>() || colisioned.hasTAG<TEnemy>()) {
        //mover el jugador hacia atras
        cancelMove(EM, colisioned, dt);
    }
    else if(colisioned.hasTAG<TBullet>()) {
        //destruir la bala
        markDestroy(colisioned);
    }
}

/*NUEVO*/ void LogicSystem::colisionPlayer2(LevelMan &LM, GraphicEngine &GE, Enty& current, Enty& colisioned, double dt, UIsys& UISys) {
    if(colisioned.hasTAG<TWall>()) {
        //moverse hacia atras
        auto& EM = LM.getEM();
        cancelMove(EM, current, dt);
    }
    else if(colisioned.hasTAG<TEnemy>()) {
        //jugador recibe daño del enemigo
        //receiveEntityDamage2(LM, GE, current, colisioned);
    }
    else if(colisioned.hasTAG<TEneBullet>()) {
        //jugador recibe daño de bala enemiga
        //auto& EM = LM.getEM();
        //reciveDamge(EM, current, colisioned);
    }
    else if(colisioned.hasTAG<TWeapon>()) {
        //mostrar texto de recoger arma
        takeWeapon2(LM, GE, current, colisioned);
    }
    else if(colisioned.hasTAG<TPowerUp>()) {
        //proceso Colision Weapon
        auto& EM = LM.getEM();
        increaseStat(EM, current, colisioned);
    }
}

/*NUEVO*/ void LogicSystem::colisionEnemy2(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned, double dt) {
    if(colisioned.hasTAG<TWall>()){
        //moverse hacia atras
        auto& EM = LM.getEM();
        cancelMove(EM, current, dt);
    }
    else if(colisioned.hasTAG<TPlayer>()){
        //enemigo hace daño al jugador
        ///receiveEntityDamage2(LM, GE, colisioned, current);
    }
    else if(colisioned.hasTAG<TBullet>()){
        //enemigo recibe daño de la bala
        reciveDamge(LM, GE, current, colisioned);
    }
}

void LogicSystem::colisionBullet(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned) {
    if(colisioned.hasTAG<TWall>()){
        //bala impacta en muro
        markDestroy(current);
    }
    else if(colisioned.hasTAG<TEnemy>()){
        //bala hace daño al enemigo
        reciveDamge(LM, GE, colisioned, current);
    }
}

void LogicSystem::colisionEneBullet(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned) {
    if(colisioned.hasTAG<TWall>()){
        //bala enemiga impacta en muro
        markDestroy(current);
    }
    else if(colisioned.hasTAG<TPlayer>()){
        //bala enemiga hace daño al jugador
        reciveDamge(LM, GE, colisioned, current);
    }
}

void LogicSystem::colisionPowerUp(LevelMan &LM, GraphicEngine &GE, Enty &current, Enty &colisioned) {
    if(colisioned.hasTAG<TPlayer>()) {
        //powerup recogido por jugador
        auto& EM = LM.getEM();
        increaseStat(EM, colisioned, current);
    }
}

/*NUEVO*/ void LogicSystem::colisionWeapon2(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned) {
    if(colisioned.hasTAG<TPlayer>()) {
        //mostrar texto de recoger arma
        takeWeapon2(LM, GE, colisioned, current);
    }
}

/*NUEVO*/ void LogicSystem::receiveEntityDamage2(LevelMan& LM, GraphicEngine& GE, Enty& receptor, Enty& agressor) {
    auto& EM = LM.getEM();
    auto& enemyStats = EM.getComponent<EstadisticaCmp>(agressor);

    if(enemyStats.ClockAttackEnemy < enemyStats.attackSpeedEnemy) return;

    enemyStats.ClockAttackEnemy = 0;
    reciveDamge(LM, GE, receptor, agressor);
}

void LogicSystem::reciveDamge(LevelMan& LM, GraphicEngine& GE, Enty& receptor, Enty& agressor) {
    auto& EM = LM.getEM();
    auto& recept_stats = EM.getComponent<EstadisticaCmp>(receptor);
    auto& agress_stats = EM.getComponent<EstadisticaCmp>(agressor);
    
    recept_stats.hitpoints -= agress_stats.damage;

    if(!agressor.hasTAG<TEnemy>()) markDestroy(agressor);

    if(recept_stats.hitpoints <= 0) {
        if(receptor.hasTAG<TEnemy>()) { 
            auto& phy = EM.getComponent<PhysicsCmp2>(receptor);
            chanceDrop(LM, GE, phy);

            EM.getComponent<AICmp>(receptor).behaviour = SB::Diying;
            EM.removeComponent<EstadoCmp>(receptor);
        }
        else markDestroy(receptor);
    }
}

void LogicSystem::cancelMove(EntyMan& EM, Enty& ent_move, double dt) {
    auto& state = EM.getComponent<EstadoCmp>(ent_move);
    state.wall_collision = true;
    if(state.entityCol != 0) partialVelocities(EM, ent_move, dt);
}

/*NUEVO*/ void LogicSystem::takeWeapon2(LevelMan& LM, GraphicEngine& GE, Enty& player, Enty& weapon) {
    auto& EM = LM.getEM();
    auto& invent  = EM.getComponent<InventarioCmp>(player);
    auto& new_wpn = EM.getComponent<WeaponCmp>(weapon);
    size_t old_wpn {};

    //Busco el arma catual para desequiparla
    for(old_wpn = 0; old_wpn < invent.numWeapons - 1; old_wpn++)
        if(invent.inventary[old_wpn] == 2) break;

    InpSys2::changeWeaponMethod(GE, invent, new_wpn.typeWe, old_wpn);

    switch(new_wpn.typeWe) {
        case 0: invent.gun.ammo   += invent.gun.maxAmmo/10;   break;
        case 1: invent.shot.ammo  += invent.shot.maxAmmo/10;  break;
        case 2: invent.rifle.ammo += invent.rifle.maxAmmo/10; break;
    }
    
    weapon.setDestroy();
}

void LogicSystem::increaseStat(EntyMan& EM, Enty& player, Enty& power) {
    auto& stats = EM.getComponent<EstadisticaCmp>(player);

    stats.extra_dmg += .2;

    markDestroy(power);
}

void LogicSystem::resetCollision(EstadoCmp& state) {
    state.colision  = 0;
    state.entityCol = 0;
}

void LogicSystem::soundMonster(EntyMan& EM, Enty& e) {
    auto& monster = EM.getComponent<SoundCmp>(e);
    EM.changeSound(monster, 2);
    EM.foreach<SYSCMP_Player, SYSTAG_Player>(
        [&](Enty&, SoundCmp& voice) {
            EM.changeSound(voice, 1);
        }
    );
}

void LogicSystem::partialVelocities(EntyMan& EM, Enty& player, double dt) {
    auto copy_physics = EM.getComponent<PhysicsCmp2>(player);
    auto& state     = EM.getComponent<EstadoCmp>(player);
    auto& wall      = EM.getEntityById(state.entityCol);
    auto& wall_state= EM.getComponent<EstadoCmp>(wall);
    auto& wall_physc= EM.getComponent<PhysicsCmp2>(wall);
    float dx, dz;

    //precalculo de coordenadas
    preCalculation(copy_physics, player.hasTAG<TEnemy>(), dt);

    //comprobar colision en la siguiente posicion
    dx = ColSys2::calculateDist(copy_physics.x, wall_physc.x, state.width, wall_state.width);
    dz = ColSys2::calculateDist(copy_physics.z, wall_physc.z, state.depth, wall_state.depth);

    //si en la siguiente posicion colisiona con una pared
    if(dx<=0 && dz<=0) {
        auto& phy = EM.getComponent<PhysicsCmp2>(player);
        secondStep(EM, copy_physics, phy, state, wall.getID(), dx, dz, dt);
    }
}

void LogicSystem::preCalculation(PhysicsCmp2& copy_physics, bool const is_enemy, double const dt) {
    PhySys2::calculatePosition(is_enemy, copy_physics, dt);
}

void LogicSystem::secondStep(EntyMan& EM, PhysicsCmp2& copy_physics, PhysicsCmp2& phy, EstadoCmp& state, size_t const wall_id, float const dx, float const dz, double const dt) {
    if(dx < dz) {
        //comprobar si la siguiente posicion a esta (2 pasos) en el eje X colisiona con otra pared distinta
        copy_physics.x += dt * copy_physics.vx;
        if(!checkFutureCollision(EM, wall_id, copy_physics.x, copy_physics.z, state.width, state.depth))
            phy.partial_x = copy_physics.vx;
    }
    else {
        //comprobar si la siguiente posicion a esta (2 pasos) en el eje Z colisiona con otra pared distinta
        copy_physics.z += dt * copy_physics.vz;
        if(!checkFutureCollision(EM, wall_id, copy_physics.x, copy_physics.z, state.width, state.depth))
            phy.partial_z = copy_physics.vz;
    }
}

bool LogicSystem::checkFutureCollision(EntyMan& EM, size_t const colld_id, float const f_coordx, float const f_coordz, float const width, float const depth) const noexcept {
    bool check = false;
    EM.foreach<SYSCMPs, SYSTAG_Walls>(
        [&](Enty& future_collisioned, PhysicsCmp2& future_phy, EstadoCmp& future_state){
            if(colld_id != future_collisioned.getID()) {
                float future_dx = ColSys2::calculateDist(f_coordx, future_phy.x, width, future_state.width);
                float future_dz = ColSys2::calculateDist(f_coordz, future_phy.z, depth, future_state.depth);
                if(future_dx <= 0 && future_dz <= 0) check = true;
            }
        }
    );
    return check;
}

void LogicSystem::chanceDrop(LevelMan& LM, GraphicEngine& GE, PhysicsCmp2& phy) {
    auto& bb = LM.getEM().getBoard();
    int num = rand() % 100 + 1;

    if(num <= bb.spawn_perc) {
        LM.createPowerUp(GE, phy);
        bb.spawn_perc = 1;
    }
    else bb.spawn_perc++; 
}