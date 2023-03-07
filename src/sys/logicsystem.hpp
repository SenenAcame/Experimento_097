#pragma once
#include "../util/types.hpp"
#include "colsys2.hpp"
#include "physys2.hpp"

struct LogicSystem {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;
    using SYSCMP_Player = MP::Typelist<SoundCmp>;
    using SYSTAG_Player = MP::Typelist<TPlayer>;
    static constexpr double PI { std::numbers::pi };

    void update(EntyMan& EM, TheEngine& eng, double dt) {
        EM.foreach<SYSCMPs, SYSTAGs >(
            [&](Enty& entity, PhysicsCmp2&, EstadoCmp& state) {
                if(entity.hasTAG<TEnemy>()){ //aumentar el clock del enemigo aqui 
                    EM.getComponent<EstadisticaCmp>(entity).ClockAttackEnemy += dt;
                }
                if(state.colision != 0){
                    auto& entity_colisioned = EM.getEntityById(state.entityCol);
                    auto& colisiones_state  = EM.getComponent<EstadoCmp>(entity_colisioned);

                    if(entity.hasTAG<TPlayer>()){
                        //proceso Colision Jugador
                        colisionPlayer   (EM, entity, entity_colisioned, dt);
                    }
                    else if(entity.hasTAG<TEnemy>()){
                        //proceso Colision Enemy
                        //std::cout<<"CHOCO CON PLAYER Y TENGO UN ATTACKCLOCK DE: " <<EM.getComponent<EstadisticaCmp>(entity).ClockAttackEnemy <<"\n";
                        colisionEnemy    (EM, entity, entity_colisioned, dt);
                    }
                    else if(entity.hasTAG<TBullet>()){
                        //proceso Colision Bullet
                        colisionBullet   (EM, entity, entity_colisioned);
                    }
                    else if(entity.hasTAG<TEneBullet>()){
                        //proceso Colision EnemyBullet
                        colisionEneBullet(EM, entity, entity_colisioned);
                    }
                    else if(entity.hasTAG<TWeapon>()){
                        //proceso Colision Weapon
                        colisionWeapon   (EM, entity, entity_colisioned);
                    }
                    else if(entity.hasTAG<TDoor>()){
                        //proceso Colision Door
                        colisionDoor     (EM, entity, entity_colisioned);
                    }
                    else if(entity.hasTAG<TDoor>()){
                        //proceso Colision Key
                        colisionKey     (EM, entity, entity_colisioned);
                    }

                    if(entity.hasTAG<TWall>()){
                        //proceso Colision Wall
                        colisionWall     (EM, entity, entity_colisioned, dt);
                    }

                    resetCollision(state, colisiones_state);
                }
            }
        );
    }

    void colisionPlayer(EntyMan& EM, Enty& current, Enty& colisioned, double dt) {
        if(colisioned.hasTAG<TWall>()){
            //moverse hacia atras
            reverseMove(EM, current, dt);
        }

        if(colisioned.hasTAG<TWeapon>()){
            //mostrar texto de recoger arma
            takeWeapon();
        }
        else if(colisioned.hasTAG<TDoor>()){
            //mostrar texto de abrir puerta
            openDoor();
        }
        else if(colisioned.hasTAG<TKey>()) {
            //mostrar texto de recoger llave
            takeKey();
        }
        else if(colisioned.hasTAG<TEnemy>() || colisioned.hasTAG<TEneBullet>()){
            //jugador recibe daño del enemigo o de la bala enemiga
            if(colisioned.hasTAG<TEnemy>()){
                auto& enemyStats = EM.getComponent<EstadisticaCmp>(colisioned);
                if(enemyStats.ClockAttackEnemy < enemyStats.attackSpeedEnemy) { return; }
                enemyStats.ClockAttackEnemy = 0;
            }
            reciveDamge(EM, current, colisioned);
        }
        
    }

    void colisionEnemy(EntyMan& EM, Enty& current, Enty& colisioned, double dt) {
        if(colisioned.hasTAG<TPlayer>()){
            //enemigo hace daño al jugador
            auto& enemyStats = EM.getComponent<EstadisticaCmp>(current);
            if(enemyStats.ClockAttackEnemy < enemyStats.attackSpeedEnemy)
            { return; }
            enemyStats.ClockAttackEnemy = 0;
            reciveDamge(EM, colisioned, current);
        }
        else if(colisioned.hasTAG<TBullet>()){
            //enemigo recibe daño de la bala
            reciveDamge(EM, current, colisioned);
        }
    }

    void colisionBullet(EntyMan& EM, Enty& current, Enty& colisioned) {
        if(colisioned.hasTAG<TEnemy>()){
            //bala hace daño al enemigo
            reciveDamge(EM, colisioned, current);
        }
        else if(colisioned.hasTAG<TWall>()){
            //bala impacta en muro
            markDestroy(current);
        }
    }

    void colisionEneBullet(EntyMan& EM, Enty& current, Enty& colisioned) {
        if(colisioned.hasTAG<TPlayer>()){
            //bala enemiga hace daño al jugador
            reciveDamge(EM, colisioned, current);
        }
    }

    void colisionWeapon(EntyMan& EM, Enty& current, Enty& colisioned){
        if(colisioned.hasTAG<TPlayer>()){
            //mostrar texto de recoger arma
            takeWeapon();
        }
    }

    void colisionDoor(EntyMan& EM, Enty& current, Enty& colisioned) {
        if(colisioned.hasTAG<TPlayer>()) {
            //mostrar texto de abrir puerta
            openDoor();
        }
    }

    void colisionWall(EntyMan& EM, Enty& current, Enty& colisioned, double dt) {
        if(colisioned.hasTAG<TPlayer>()){
            //mover el jugador hacia atras
            reverseMove(EM, colisioned, dt);
        }
        else if(colisioned.hasTAG<TBullet>()) {
            //destruir la bala
            markDestroy(colisioned);
        }
    }

    void colisionKey(EntyMan& EM, Enty& current, Enty& colisioned) {
        if(colisioned.hasTAG<TPlayer>()){
            //mostrar texto de recoger llave
            takeKey();
        }
    }

    void reciveDamge(EntyMan& EM, Enty& receptor, Enty& agressor) {
        auto& recept_stats = EM.getComponent<EstadisticaCmp>(receptor);
        auto& agress_stats = EM.getComponent<EstadisticaCmp>(agressor);
        
        recept_stats.hitpoints -= agress_stats.damage;
        
        if(recept_stats.hitpoints <= 0) { markDestroy(receptor); }
        
        if(!agressor.hasTAG<TEnemy>())  { markDestroy(agressor); }
        if(receptor.hasTAG<TPlayer>()) std::cout<<"Hay daño\n";
    }

    void markDestroy(Enty& enty_to_dele) {
        enty_to_dele.setDestroy();
    }

    void reverseMove(EntyMan& EM, Enty& ent_move, double dt) {
        auto& phy_player = EM.getComponent<PhysicsCmp2>(ent_move);
        uint8_t collisioned = preCalculation(EM, ent_move, dt);
        if(collisioned) phy_player.v_lin = 0;
    }

    void openDoor() {
        //mostrar texto de abrir puerta
        //std::cout<<"Abrir puerta con la E\n";
    }

    void takeWeapon() {
        //mostrar texto de recoger arma
        //std::cout<<a<<" Recoger arma con la E\n";
        //++a;
    }

    void takeKey() {
        //mostrar texto de recoger llave
        //std::cout<<"Recoge la llave\n";
    }

    void resetCollision(EstadoCmp& recept_state, EstadoCmp& agress_state) {
        recept_state.colision  = 0;
        recept_state.entityCol = 0;
        agress_state.colision  = 0;
        agress_state.entityCol = 0;
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

    uint8_t preCalculation(EntyMan& EM, Enty& player, double dt) {
        //COPIA de componente fisico
        auto copy_physics = EM.getComponent<PhysicsCmp2>(player);
        auto& state     = EM.getComponent<EstadoCmp>(player);
        auto& wall      = EM.getEntityById(state.entityCol);
        auto& wall_state= EM.getComponent<EstadoCmp>(wall);
        auto& wall_physc= EM.getComponent<PhysicsCmp2>(wall);
        float dx, dz;

        //precalculo de coordenadas
        copy_physics.orieny += dt * copy_physics.v_ang;
        if      (copy_physics.orieny > 2*PI) copy_physics.orieny -= 2*PI;
        else if (copy_physics.orieny < 0)    copy_physics.orieny += 2*PI;
        copy_physics.vx =  copy_physics.v_lin * std::sin(copy_physics.orieny);
        copy_physics.vz =  copy_physics.v_lin * std::cos(copy_physics.orieny);
        copy_physics.x += dt * copy_physics.vx;
        copy_physics.z += dt * copy_physics.vz;

        //comprobar colision en siquiente posicion
        dx = abs(copy_physics.x - wall_physc.x) - (state.width + wall_state.width);
        dz = abs(copy_physics.z - wall_physc.z) - (state.depth + wall_state.depth);

        if(dx<=0 && dz<=0) return 1;
        return 0;
    }

};