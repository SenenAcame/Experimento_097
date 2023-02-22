#pragma once
#include "../util/types.hpp"

struct LogicSystem {
    int a = 1;
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;

    using SYSCMP_Player = MP::Typelist<SoundCmp>;
    using SYSTAG_Player = MP::Typelist<TPlayer>;

    void update(EntyMan& EM, TheEngine& eng) {
        EM.foreach<SYSCMPs, SYSTAGs >(
            [&](Enty& entity, PhysicsCmp2&, EstadoCmp& state) {
                if(state.colision != 0){
                    auto& entity_colisioned = EM.getEntityById(state.entityCol);
                    auto& colisiones_state  = EM.getComponent<EstadoCmp>(entity_colisioned);

                    if(entity.hasTAG<TPlayer>()){
                        //proceso Colision Jugador
                        colisionPlayer   (EM, entity, entity_colisioned);
                    }
                    else if(entity.hasTAG<TEnemy>()){
                        //proceso Colision Enemy
                        colisionEnemy    (EM, entity, entity_colisioned);
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
                    else if(entity.hasTAG<TWall>()){
                        //proceso Colision Wall
                        colisionWall     (EM, entity, entity_colisioned);
                    }

                    resetCollision(state, colisiones_state);
                }
            }
        );
    }

    void colisionPlayer(EntyMan& EM, Enty& current, Enty& colisioned) {
        if(colisioned.hasTAG<TWeapon>()){
            //mostrar texto de recoger arma
            takeWeapon();
        }
        else if(colisioned.hasTAG<TDoor>()){
            //mostrar texto de abrir puerta
            openDoor();
        }
        else if(colisioned.hasTAG<TWall>()){
            //moverse hacia atras
            reverseMove(EM, current);
        }
        else if(colisioned.hasTAG<TEnemy>() || colisioned.hasTAG<TEneBullet>()){
            //jugador recibe daño del enemigo o de la bala enemiga
            reciveDamge(EM, current, colisioned);
        }
    }

    void colisionEnemy(EntyMan& EM, Enty& current, Enty& colisioned) {
        if(colisioned.hasTAG<TPlayer>()){
            //enemigo hace daño al jugador
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

    void colisionWall(EntyMan& EM, Enty& current, Enty& colisioned) {
        //mover el jugador hacia atras
        if(colisioned.hasTAG<TPlayer>()){
            reverseMove(EM, colisioned);
        }
    }

    void reciveDamge(EntyMan& EM, Enty& receptor, Enty& agressor) {
        //auto& recept_stats = EM.getComponent<EstadisticaCmp>(receptor);
        //auto& agress_stats = EM.getComponent<EstadisticaCmp>(agressor);
        //
        //recept_stats.hitpoints -= agress_stats.damage;
        //
        //if(recept_stats.hitpoints <= 0) { receptor.setDestroy(); }
        //
        //if(!agressor.hasTAG<TEnemy>())  { agressor.setDestroy(); }
        //std::cout<<"Hay daño\n";
    }

    void reverseMove(EntyMan& EM, Enty& ent_move) {
        auto& phy_player = EM.getComponent<PhysicsCmp2>(ent_move);
        phy_player.v_lin = -phy_player.v_lin;
        std::cout<<"Has chocado contra un muro\n";
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

    void resetCollision(EstadoCmp& recept_state, EstadoCmp& agress_state) {
        recept_state.colision  = 0;
        recept_state.entityCol = 0;
        agress_state.colision  = 0;
        agress_state.entityCol = 0;
        //std::cout<<"Reseteo de colisiones\n";
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
};

// Viejo codigo del update del sistema de logica

//EM.foreach<SYSCMPs, SYSTAGs >(
//    [&](Enty& e, EstadoCmp& p, EstadisticaCmp& stats) {
//        if(p.colision !=0){
//            if(e.hasTAG<TPlayer>()){
//                if(EM.getEntityById(p.entityCol).hasTAG<TEnemy>()){
//                    stats.hitpoints -=EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).damage;
//                    if(stats.hitpoints <=0){
//                        //p.alive=1; //set to destroy
//                        e.setDestroy();
//                    }
//                    //std::cout<<"SOY Jugador: "<<e.getID()<<"Tenia: "<<stats.hitpoints<<" HE CHOCADO CON UNA BALA: "<<p.entityCol<<
//                    //" y ahora tengo" <<stats.hitpoints<<"\n";
//                }
//            }
//            else if(e.hasTAG<TEnemy>()){          
//                if(EM.getEntityById(p.entityCol).hasTAG<TBullet>()){
//                    stats.hitpoints -= EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).damage;
//                    if(stats.hitpoints <=0){
//                        //p.alive=1; //set to destroy
//                        e.setDestroy();
//                        //std::cout<<"Ahora tengo estado "<<p.alive<<"\n";
//                    }
//                    // std::cout<<"SOY ENTIDAD: "<<e.getID()<<" Tenia: "<<stats.hitpoints<<" HE CHOCADO CON UNA BALA: "<<p.entityCol<<
//                    // " y ahora tengo" <<stats.hitpoints<<"\n";
//                }
//                else if(EM.getEntityById(p.entityCol).hasTAG<TPlayer>()){
//                    EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints -= stats.damage;
//                    if(EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints<=0){
//                        //EM.getComponent<EstadoCmp>(EM.getEntityById(p.entityCol)).alive = 1; //set to destroy
//                        EM.getEntityById(p.entityCol).setDestroy();
//                    }
//                }
//                else if(EM.getEntityById(p.entityCol).hasTAG<TEnemy>()){
//                    //std::cout<<"SOY ENTIDAD: "<<e.getID()<<" HE CHOCADO CON UN Enemigo: "<<p.entityCol<<"\n";
//                }
//            }
//            else if(e.hasTAG<TBullet>()){
//                if(EM.getEntityById(p.entityCol).hasTAG<TEnemy>()){
//                    EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints -= stats.damage;
//                    if(EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints<=0){
//                        //EM.getComponent<EstadoCmp>(EM.getEntityById(p.entityCol)).alive = 1;
//                        EM.getEntityById(p.entityCol).setDestroy(); //set to destroy
//                    }
//                }
//                //p.alive = 1; //set to destroy
//                e.setDestroy();
//            }
//            ////valores por defecto
//            p.colision = 0;
//            p.entityCol = 0;
//        }
//    }
//);