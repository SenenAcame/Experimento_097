#include "logicsystem.hpp"
#include "UIsys.hpp"
#include "colsys2.hpp"
#include "inpsys2.hpp"
#include "physys2.hpp"
#include "../man/levelman.hpp"
#include "../eng/engine2.hpp"
#include "../util/munition_aux.hpp"

//int aux = 0;

///*VIEJO*/ void LogicSystem::update(LevelMan& LM, TheEngine& eng, double dt) {
//    auto& EM = LM.getEM();
//    EM.foreach<SYSCMPs, SYSTAGs >(
//        [&](Enty& entity, PhysicsCmp2&, EstadoCmp& state) {

//            if(entity.hasTAG<TEnemy>()) EM.getComponent<EstadisticaCmp>(entity).ClockAttackEnemy += dt;
//
//            if(state.colision != 0) {

//                auto& entity_colisioned = EM.getEntityById(state.entityCol);

//                if(entity_colisioned.hasCMP<EstadoCmp>()) {

//                    auto& colisiones_state  = EM.getComponent<EstadoCmp>(entity_colisioned);

//                    if(entity.hasTAG<TWall>()){
//                        //proceso Colision Wall
//                        colisionWall     (EM, entity, entity_colisioned, dt);
//                    }
//                    else if(entity.hasTAG<TPlayer>()){
//                        //proceso Colision Jugador
//                        colisionPlayer   (LM, eng, entity, entity_colisioned, dt);
//                    }
//                    else if(entity.hasTAG<TEnemy>()){
//                        //proceso Colision Enemy
//                        colisionEnemy    (LM, eng, entity, entity_colisioned, dt);
//                    }
//                    else if(entity.hasTAG<TBullet>()){
//                        //proceso Colision Bullet
//                        colisionBullet   (EM, entity, entity_colisioned);
//                    }
//                    //else if(entity.hasTAG<TEneBullet>()){
//                    //    //proceso Colision EnemyBullet
//                    //    colisionEneBullet(EM, entity, entity_colisioned);
//                    //}
//                    else if(entity.hasTAG<TWeapon>()){
//                        //proceso Colision Weapon
//                        colisionWeapon   (LM, entity, entity_colisioned, eng);
//                    }
//                    //else if(entity.hasTAG<TDoor>()){
//                    //    //proceso Colision Door
//                    //    colisionDoor     (EM, entity, entity_colisioned);
//                    //}
//                    //else if(entity.hasTAG<TKey>()){
//                    //    //proceso Colision Key
//                    //    colisionKey     (EM, entity, entity_colisioned);
//                    //
//                    //resetCollision(state, colisiones_state);
//                    resetCollision(colisiones_state);
//                }
//                resetCollision(state);
//            }
//        }
//    );
//}

/*NUEVO*/ void LogicSystem::update2(LevelMan& LM, GraphicEngine& GE, double dt, UIsys& UISys, bool& dead) {
    auto& EM = LM.getEM();
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& entity, PhysicsCmp2&, EstadoCmp& state) {
            if(entity.hasTAG<TPlayer>()){
                if(EM.getComponent<EstadisticaCmp>(entity).hitpoints == 0) {
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
        else if(entity.hasTAG<TBullet>()){
            //proceso Colision Bullet
            colisionBullet(EM, entity, entity_colisioned);
        }
        else if(entity.hasTAG<TWeapon>()){
            //proceso Colision Weapon
            colisionWeapon2(LM, GE, entity, entity_colisioned);
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

///*VIEJO*/ void LogicSystem::colisionPlayer(LevelMan& LM, TheEngine& eng, Enty& current, Enty& colisioned, double dt) {
//    if(colisioned.hasTAG<TWall>()){
//        //moverse hacia atras
//        auto& EM = LM.getEM();
//        cancelMove(EM, current, dt);
//    }
//    else if(colisioned.hasTAG<TEnemy>()){
//        //jugador recibe daño del enemigo
//        receiveEntityDamage(LM, eng, current, colisioned);
//    }
//    //else if(colisioned.hasTAG<TEneBullet>()) {
//    //    //jugador recibe daño de la bala enemiga
//    //    reciveDamge(EM, current, colisioned);
//    //}
//    else if(colisioned.hasTAG<TWeapon>()){
//        //mostrar texto de recoger arma
//        takeWeapon(current, colisioned, LM, eng);
//    }
//    //else if(colisioned.hasTAG<TDoor>()){
//    //    //mostrar texto de abrir puerta
//    //    openDoor();
//    //}
//    //else if(colisioned.hasTAG<TKey>()) {
//    //    //mostrar texto de recoger llave
//    //    takeKey();
//    //}
//}

/*NUEVO*/ void LogicSystem::colisionPlayer2(LevelMan &LM, GraphicEngine &GE, Enty& current, Enty& colisioned, double dt, UIsys& UISys) {
    if(colisioned.hasTAG<TWall>()){
        //moverse hacia atras
        auto& EM = LM.getEM();
        cancelMove(EM, current, dt);
    }
    else if(colisioned.hasTAG<TEnemy>()){
        //jugador recibe daño del enemigo
        //std::cout<<"Daño\n";
    }
    else if(colisioned.hasTAG<TWeapon>()){
        //mostrar texto de recoger arma
        takeWeapon2(LM, GE, current, colisioned);
    }
}

///*VIEJO*/ void LogicSystem::colisionEnemy(LevelMan& LM, TheEngine& eng, Enty& current, Enty& colisioned, double dt) {
//    if(colisioned.hasTAG<TWall>()){
//        //moverse hacia atras
//        auto& EM = LM.getEM();
//        cancelMove(EM, current, dt);
//    }
//    else if(colisioned.hasTAG<TPlayer>()){
//        //enemigo hace daño al jugador
//        receiveEntityDamage(LM, eng, colisioned, current);
//    }
//    else if(colisioned.hasTAG<TBullet>()){
//        //enemigo recibe daño de la bala
//        auto& EM = LM.getEM();
//        reciveDamge(EM, current, colisioned);
//    }
//}

/*NUEVO*/ void LogicSystem::colisionEnemy2(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned, double dt) {
    if(colisioned.hasTAG<TWall>()){
        //moverse hacia atras
        auto& EM = LM.getEM();
        cancelMove(EM, current, dt);
    }
    else if(colisioned.hasTAG<TPlayer>()){
        //enemigo hace daño al jugador
        //std::cout<<"Daño\n";
    }
    else if(colisioned.hasTAG<TBullet>()){
        //enemigo recibe daño de la bala
        auto& EM = LM.getEM();
        reciveDamge(EM, current, colisioned);
    }
}

void LogicSystem::colisionBullet(EntyMan& EM, Enty& current, Enty& colisioned) {
    if(colisioned.hasTAG<TWall>()){
        //bala impacta en muro
        markDestroy(current);
    }
    else if(colisioned.hasTAG<TEnemy>()){
        //bala hace daño al enemigo
        reciveDamge(EM, colisioned, current);
    }
}

//void LogicSystem::colisionEneBullet(EntyMan& EM, Enty& current, Enty& colisioned) {
//    if(colisioned.hasTAG<TWall>()){
//        //bala enemiga impacta en muro
//        markDestroy(current);
//    }
//    else if(colisioned.hasTAG<TPlayer>()){
//        //bala enemiga hace daño al jugador
//        reciveDamge(EM, colisioned, current);
//    }
//}

///*VIEJO*/ void LogicSystem::colisionWeapon(LevelMan& LM, Enty& current, Enty& colisioned, TheEngine& eng){
//    if(colisioned.hasTAG<TPlayer>()){
//        //mostrar texto de recoger arma
//        //borrar entidad arma
//        takeWeapon(colisioned, current, LM, eng);
//    }
//}

/*NUEVO*/ void LogicSystem::colisionWeapon2(LevelMan& LM, GraphicEngine& GE, Enty& current, Enty& colisioned){
    if(colisioned.hasTAG<TPlayer>()){
        //mostrar texto de recoger arma
        takeWeapon2(LM, GE, colisioned, current);
    }
}

//void LogicSystem::colisionDoor(EntyMan& EM, Enty& current, Enty& colisioned) {
//    if(colisioned.hasTAG<TPlayer>()) {
//        //mostrar texto de abrir puerta
//        openDoor();
//    }
//}

//void LogicSystem::colisionKey(EntyMan& EM, Enty& current, Enty& colisioned) {
//    if(colisioned.hasTAG<TPlayer>()){
//        //mostrar texto de recoger llave
//        takeKey();
//    }
//}

///*VIEJO*/ void LogicSystem::receiveEntityDamage(LevelMan& LM, TheEngine& eng, Enty& receptor, Enty& agressor) {
//    auto& EM = LM.getEM();
//    auto& enemyStats = EM.getComponent<EstadisticaCmp>(agressor);
//    if(enemyStats.ClockAttackEnemy < enemyStats.attackSpeedEnemy) { return; }
//    enemyStats.ClockAttackEnemy = 0;
//    reciveDamge(EM, receptor, agressor);
//    LM.updateInterfaceHit(eng, receptor);
//}

/*VIEJO*/ void LogicSystem::receiveEntityDamage2(LevelMan& LM, GraphicEngine& GE, Enty& receptor, Enty& agressor) {
    auto& EM = LM.getEM();
    auto& enemyStats = EM.getComponent<EstadisticaCmp>(agressor);
    if(enemyStats.ClockAttackEnemy < enemyStats.attackSpeedEnemy) { return; }
    enemyStats.ClockAttackEnemy = 0;
    reciveDamge(EM, receptor, agressor);
    //LM.updateInterfaceHit(eng, receptor);
}

void LogicSystem::reciveDamge(EntyMan& EM, Enty& receptor, Enty& agressor) {
    auto& recept_stats = EM.getComponent<EstadisticaCmp>(receptor);
    auto& agress_stats = EM.getComponent<EstadisticaCmp>(agressor);
    
    recept_stats.hitpoints -= agress_stats.damage;

    //std::cout<<"Impacto "<<aux++<<"\n";

    if(recept_stats.hitpoints <= 0) {
        //if(receptor.hasTAG<TEnemy>()) { 
        //    EM.getComponent<AICmp>(receptor).behaviour = SB::Diying;
        //    EM.removeComponent<EstadoCmp>(receptor);
        //}
        //else { markDestroy(receptor); } 
        markDestroy(receptor);
    }
    
    if(!agressor.hasTAG<TEnemy>()) { markDestroy(agressor); }
}

void LogicSystem::cancelMove(EntyMan& EM, Enty& ent_move, double dt) {
    auto& state = EM.getComponent<EstadoCmp>(ent_move);
    state.wall_collision = true;
    if(state.entityCol != 0) partialVelocities(EM, ent_move, dt);
}

///*VIEJO*/ void LogicSystem::takeWeapon(Enty& player, Enty& weapon, LevelMan& LM, TheEngine& eng) {
//    //unificarlo en el level manager para que no este el codigo en input y aqui
//    auto& EM = LM.getEM();
//    auto& equipment = EM.getComponent<InventarioCmp>(player);
//    auto& playerRender = EM.getComponent<RenderCmp2>(player);
//    int ammo {}, magazine {};
//    size_t aux = 0;
//
//    for(auto i: equipment.inventary){ //Desequipo el arma actual y equipo la nueva
//        if(i == 2){
//            auto& wpn = EM.getComponent<WeaponCmp>(weapon);
//            equipment.inventary[aux] = 1;
//            equipment.inventary[wpn.typeWe] = 2;
//            equipment.equipada = wpn.typeWe;
//            break;
//        }
//        aux++;
//    }
//    
//    playerRender.n->remove();
//
//    switch (equipment.equipada) {
//        case 0: playerRender.n = eng.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp");
//            ammo = equipment.ammo1;
//            magazine = equipment.magazine1;
//            break;
//        case 1: playerRender.n = eng.createPlayer("assets/models/armas/escopeta.obj","assets/textures/fire.bmp");
//            ammo = equipment.ammo2;
//            magazine = equipment.magazine2;
//            break;
//        case 2: playerRender.n = eng.createPlayer("assets/models/armas/subfusil.obj","assets/textures/fire.bmp");
//            ammo = equipment.ammo3;
//            magazine = equipment.magazine3;
//            break;
//        default: break;
//    }
//    LM.updateInterfaceWhenReload(eng, magazine, ammo);
//    weapon.setDestroy();
//}

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
        case 0: invent.gun.ammo += invent.gun.maxAmmo/10;
            break;
        case 1: invent.shot.ammo += invent.shot.maxAmmo/10;
            break;
        case 2: invent.rifle.ammo += invent.rifle.maxAmmo/10;
            break;
    }
    
    weapon.setDestroy();
}

void LogicSystem::resetCollision(EstadoCmp& state) {
    state.colision  = 0;
    state.entityCol = 0;
}

void LogicSystem::soundMonster(EntyMan& EM, Enty& e) {
    auto& monster = EM.getComponent<SoundCmp>(e);
    EM.changeSound(monster, 2);
    EM.foreach<SYSCMP_Player, SYSTAG_Player>(
        [&](Enty&, SoundCmp& voice){
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