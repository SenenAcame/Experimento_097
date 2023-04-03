#pragma once
#include "../util/types.hpp"
#include "colsys2.hpp"
#include "physys2.hpp"
#include "../man/levelman.hpp"

struct LogicSystem {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;
    using SYSCMP_Player = MP::Typelist<SoundCmp>;
    using SYSTAG_Player = MP::Typelist<TPlayer>;
    using SYSTAG_Walls  = MP::Typelist<TWall>;
    static constexpr double PI { std::numbers::pi };

    void update(LevelMan& LM, TheEngine& eng, double dt) {
        auto& EM = LM.getEM();
        EM.foreach<SYSCMPs, SYSTAGs >(
            [&](Enty& entity, PhysicsCmp2&, EstadoCmp& state) {
                if(entity.hasTAG<TEnemy>()) EM.getComponent<EstadisticaCmp>(entity).ClockAttackEnemy += dt;

                if(state.colision != 0) {
                    auto& entity_colisioned = EM.getEntityById(state.entityCol);
                    if(entity_colisioned.hasCMP<EstadoCmp>()) {
                        auto& colisiones_state  = EM.getComponent<EstadoCmp>(entity_colisioned);
                        if(entity.hasTAG<TWall>()){
                            //proceso Colision Wall
                            colisionWall     (EM, entity, entity_colisioned, dt);
                        }
                        else if(entity.hasTAG<TPlayer>()){
                            //proceso Colision Jugador
                            colisionPlayer   (LM, eng, entity, entity_colisioned, dt);
                        }
                        else if(entity.hasTAG<TEnemy>()){
                            //proceso Colision Enemy
                            colisionEnemy    (LM, eng, entity, entity_colisioned, dt);
                        }
                        else if(entity.hasTAG<TBullet>()){
                            //proceso Colision Bullet
                            colisionBullet   (EM, entity, entity_colisioned);
                        }
                        //else if(entity.hasTAG<TEneBullet>()){
                        //    //proceso Colision EnemyBullet
                        //    colisionEneBullet(EM, entity, entity_colisioned);
                        //}
                        else if(entity.hasTAG<TWeapon>()){
                            //proceso Colision Weapon
                            colisionWeapon   (LM, entity, entity_colisioned, eng);
                        }
                        //else if(entity.hasTAG<TDoor>()){
                        //    //proceso Colision Door
                        //    colisionDoor     (EM, entity, entity_colisioned);
                        //}
                        //else if(entity.hasTAG<TKey>()){
                        //    //proceso Colision Key
                        //    colisionKey     (EM, entity, entity_colisioned);
                        //
                        //resetCollision(state, colisiones_state);
                        resetCollision(colisiones_state);
                    }
                    resetCollision(state);
                }
            }
        );
    }

    void colisionWall(EntyMan& EM, Enty& current, Enty& colisioned, double dt) {
        if(colisioned.hasTAG<TPlayer>() || colisioned.hasTAG<TEnemy>()){
            //mover el jugador hacia atras
            cancelMove(EM, colisioned, dt);
        }
        else if(colisioned.hasTAG<TBullet>()) {
            //destruir la bala
            markDestroy(colisioned);
        }
    }

    void colisionPlayer(LevelMan& LM, TheEngine& eng, Enty& current, Enty& colisioned, double dt) {
        if(colisioned.hasTAG<TWall>()){
            //moverse hacia atras
            auto& EM = LM.getEM();
            cancelMove(EM, current, dt);
        }
        else if(colisioned.hasTAG<TEnemy>()){
            //jugador recibe daño del enemigo
            receiveEntityDamage(LM, eng, current, colisioned);
        }
        //else if(colisioned.hasTAG<TEneBullet>()) {
        //    //jugador recibe daño de la bala enemiga
        //    reciveDamge(EM, current, colisioned);
        //}
        else if(colisioned.hasTAG<TWeapon>()){
            //mostrar texto de recoger arma
            takeWeapon(current, colisioned, LM, eng);
        }
        //else if(colisioned.hasTAG<TDoor>()){
        //    //mostrar texto de abrir puerta
        //    openDoor();
        //}
        //else if(colisioned.hasTAG<TKey>()) {
        //    //mostrar texto de recoger llave
        //    takeKey();
        //}
    }

    void colisionEnemy(LevelMan& LM, TheEngine& eng, Enty& current, Enty& colisioned, double dt) {
        if(colisioned.hasTAG<TWall>()){
            //moverse hacia atras
            auto& EM = LM.getEM();
            cancelMove(EM, current, dt);
        }
        else if(colisioned.hasTAG<TPlayer>()){
            //enemigo hace daño al jugador
            receiveEntityDamage(LM, eng, colisioned, current);
        }
        else if(colisioned.hasTAG<TBullet>()){
            //enemigo recibe daño de la bala
            auto& EM = LM.getEM();
            reciveDamge(EM, current, colisioned);
        }
    }

    void colisionBullet(EntyMan& EM, Enty& current, Enty& colisioned) {
        if(colisioned.hasTAG<TWall>()){
            //bala impacta en muro
            markDestroy(current);
        }
        else if(colisioned.hasTAG<TEnemy>()){
            //bala hace daño al enemigo
            reciveDamge(EM, colisioned, current);
        }
    }

    //void colisionEneBullet(EntyMan& EM, Enty& current, Enty& colisioned) {
    //    if(colisioned.hasTAG<TWall>()){
    //        //bala enemiga impacta en muro
    //        markDestroy(current);
    //    }
    //    else if(colisioned.hasTAG<TPlayer>()){
    //        //bala enemiga hace daño al jugador
    //        reciveDamge(EM, colisioned, current);
    //    }
    //}
    //
    void colisionWeapon(LevelMan& LM, Enty& current, Enty& colisioned, TheEngine& eng){
        if(colisioned.hasTAG<TPlayer>()){
            //mostrar texto de recoger arma
            //borrar entidad arma
            takeWeapon(colisioned, current, LM, eng);
        }
    }
    //
    //void colisionDoor(EntyMan& EM, Enty& current, Enty& colisioned) {
    //    if(colisioned.hasTAG<TPlayer>()) {
    //        //mostrar texto de abrir puerta
    //        openDoor();
    //    }
    //}
    //
    //void colisionKey(EntyMan& EM, Enty& current, Enty& colisioned) {
    //    if(colisioned.hasTAG<TPlayer>()){
    //        //mostrar texto de recoger llave
    //        takeKey();
    //    }
    //}

    void receiveEntityDamage(LevelMan& LM, TheEngine& eng, Enty& receptor, Enty& agressor) {
        auto& EM = LM.getEM();
        auto& enemyStats = EM.getComponent<EstadisticaCmp>(agressor);
        if(enemyStats.ClockAttackEnemy < enemyStats.attackSpeedEnemy) { return; }
        enemyStats.ClockAttackEnemy = 0;
        reciveDamge(EM, receptor, agressor);
        LM.updateInterfaceHit(eng, receptor);
    }

    void reciveDamge(EntyMan& EM, Enty& receptor, Enty& agressor) {
        auto& recept_stats = EM.getComponent<EstadisticaCmp>(receptor);
        auto& agress_stats = EM.getComponent<EstadisticaCmp>(agressor);
        
        recept_stats.hitpoints -= agress_stats.damage;
        
        if(recept_stats.hitpoints <= 0) {
            if(receptor.hasTAG<TEnemy>()) { 
                EM.getComponent<AICmp>(receptor).behaviour = SB::Diying;
                EM.removeComponent<EstadoCmp>(receptor);
            }
            else { markDestroy(receptor); } 
        }
        
        if(!agressor.hasTAG<TEnemy>()) { markDestroy(agressor); }
    }

    void markDestroy(Enty& enty_to_dele) { enty_to_dele.setDestroy(); }

    void cancelMove(EntyMan& EM, Enty& ent_move, double dt) {
        auto& state = EM.getComponent<EstadoCmp>(ent_move);
        state.wall_collision = true;
        if(state.entityCol != 0) partialVelocities(EM, ent_move, dt);
    }

    void takeWeapon(Enty& player, Enty& weapon, LevelMan& LM, TheEngine& eng) {
        //unificarlo en el level manager para que no este el codigo en input y aqui
        auto& EM = LM.getEM();
        auto& equipment = EM.getComponent<InventarioCmp>(player);
        auto& playerRender = EM.getComponent<RenderCmp2>(player);
        auto& weaponCM = EM.getComponent<WeaponCmp>(weapon);
        auto& weaponRender = EM.getComponent<RenderCmp2>(weapon);
        int ammo {}, magazine {};
        size_t aux = 0;

        if(weaponRender.n->isVisible()==true){
            
            if(weaponCM.pickIt == 0){
                
                for(auto i: equipment.inventary){ //Desequipo el arma actual y equipo la nueva
                    if(i == 2){
                        auto& wpn = EM.getComponent<WeaponCmp>(weapon);
                        equipment.inventary[aux] = 1;
                        equipment.inventary[wpn.typeWe] = 2;
                        equipment.equipada = wpn.typeWe;
                        break;
                    }
                    aux++;
                }
                playerRender.n->remove();
                switch (equipment.equipada) {
                    case 0: playerRender.n = eng.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp");
                        ammo = equipment.ammo1;
                        magazine = equipment.magazine1;
                        break;
                    case 1: playerRender.n = eng.createPlayer("assets/models/armas/escopeta.obj","assets/textures/fire.bmp");
                        ammo = equipment.ammo2;
                        magazine = equipment.magazine2;
                        break;
                    case 2: playerRender.n = eng.createPlayer("assets/models/armas/subfusil.obj","assets/textures/fire.bmp");
                        ammo = equipment.ammo3;
                        magazine = equipment.magazine3;
                        break;
                    default: break;
                }
                weaponCM.pickIt = 1;
                LM.updateInterfaceWhenReload(eng, magazine, ammo);
            }
            else if(weaponCM.pickIt == 1){
                
                switch (weaponCM.typeWe) {
                        case 0: 
                            equipment.ammo1 = 100;
                            equipment.magazine1 = 5;
                            ammo = equipment.ammo1;
                            magazine = equipment.magazine1;
                            break;
                        case 1:
                            equipment.ammo2 = 20;
                            equipment.magazine2 = 2;
                            ammo = equipment.ammo2;
                            magazine = equipment.magazine2;
                            break;
                        case 2: 
                            equipment.ammo3 = 200;
                            equipment.magazine3 = 25;
                            ammo = equipment.ammo3;
                            magazine = equipment.magazine3;
                            break;
                        default: break;
                } 
                if(weaponCM.typeWe == equipment.equipada){
                    LM.updateInterfaceWhenReload(eng, magazine, ammo);
                }


            }
            
        }
        weaponRender.n->setVisible(false);
        
        
        //weapon.setDestroy();
    }
    //
    //void openDoor() {
    //    //mostrar texto de abrir puerta
    //    //std::cout<<"Abrir puerta con la E\n";
    //}
    //
    //void takeKey() {
    //    //mostrar texto de recoger llave
    //    //std::cout<<"Recoge la llave\n";
    //}

    //void resetCollision(EstadoCmp& recept_state, EstadoCmp& agress_state) {
    //    recept_state.colision  = 0;
    //    recept_state.entityCol = 0;
    //    agress_state.colision  = 0;
    //    agress_state.entityCol = 0;
    //}
    void resetCollision(EstadoCmp& state) {
        state.colision  = 0;
        state.entityCol = 0;
    }

    void soundMonster(EntyMan& EM, Enty& e) {
        auto& monster = EM.getComponent<SoundCmp>(e);
        EM.changeSound(monster, 2);
        EM.foreach<SYSCMP_Player, SYSTAG_Player>(
            [&](Enty&, SoundCmp& voice){
                EM.changeSound(voice, 1);
            }
        );
    }

    void partialVelocities(EntyMan& EM, Enty& player, double dt) {
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

    void preCalculation(PhysicsCmp2& copy_physics, bool const is_enemy, double const dt) {
        PhySys2::calculatePosition(is_enemy, copy_physics, dt);
    }

    void secondStep(EntyMan& EM, PhysicsCmp2& copy_physics, PhysicsCmp2& phy, EstadoCmp& state, size_t const wall_id, float const dx, float const dz, double const dt) {
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

    bool checkFutureCollision(EntyMan& EM, size_t const colld_id, float const f_coordx, float const f_coordz, float const width, float const depth) const noexcept {
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
};