#pragma once
#include "../util/types.hpp"

struct LogicSystem {
    using SYSCMPs = MP::Typelist<EstadoCmp, EstadisticaCmp>;
    using SYSTAGs = MP::Typelist<>;

    using SYSCMP_Player = MP::Typelist<SoundCmp>;
    using SYSTAG_Player = MP::Typelist<TPlayer>;

    void update(EntyMan& EM, TheEngine& eng) {
        EM.foreach<SYSCMPs, SYSTAGs >(
            [&](Enty& e, EstadoCmp& p, EstadisticaCmp& stats) {
                if(p.colision != 0){
                    auto& entity_colisioned       = EM.getEntityById(p.entityCol);
                    auto& entity_colisioned_stats = EM.getComponent<EstadisticaCmp>(entity_colisioned);

                    if(e.hasTAG<TPlayer>()){
                        colisionPlayer(e, entity_colisioned, entity_colisioned_stats);
                    }
                    else if(e.hasTAG<TEnemy>()){
                        colisionEnemy(EM, e, entity_colisioned, stats, entity_colisioned_stats);
                    }
                    else if(e.hasTAG<TBullet>()) {
                        colisionBullet(e, entity_colisioned, stats, entity_colisioned_stats);
                    }
                    ////valores por defecto
                    p.colision = 0;
                    p.entityCol = 0;
                }
            }
        );
    }

    void colisionPlayer(Enty& current, Enty& colisioned, EstadisticaCmp& col_stats) {
        if(colisioned.hasTAG<TEnemy>()) {
            col_stats.hitpoints -= col_stats.damage;
            if(col_stats.hitpoints <= 0) { current.setDestroy(); } //set to destroy
        }
    }

    void colisionEnemy(EntyMan& EM, Enty& current, Enty& colisioned, EstadisticaCmp& curr_stats, EstadisticaCmp& col_stats) {
        if(colisioned.hasTAG<TBullet>()) {
            curr_stats.hitpoints -= col_stats.damage;
            if(curr_stats.hitpoints <= 0) { 
                soundMonster(EM, current);
                current.setDestroy(); //set to destroy
            }
        } 
        else if(colisioned.hasTAG<TPlayer>()) {
            col_stats.hitpoints -= curr_stats.damage;
            if(col_stats.hitpoints <= 0) { colisioned.setDestroy(); } //set to destroy
        }
    }

    void colisionBullet(Enty& current, Enty& colisioned, EstadisticaCmp& curr_stats, EstadisticaCmp& col_stats) {
        if(colisioned.hasTAG<TEnemy>()) {
            col_stats.hitpoints -= curr_stats.damage;
            if(col_stats.hitpoints <= 0) { colisioned.setDestroy(); } //set to destroy
        }
        current.setDestroy(); //set to destroy
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