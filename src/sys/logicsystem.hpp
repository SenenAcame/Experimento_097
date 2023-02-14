#pragma once
#include "../util/types.hpp"

struct LogicSystem {
    using SYSCMPs = MP::Typelist<EstadoCmp, EstadisticaCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& eng) {
        EM.foreach<SYSCMPs, SYSTAGs >(
            [&](Enty& e, EstadoCmp& p, EstadisticaCmp& stats) {
                if(p.colision != 0){
                    auto& entity_colisioned       = EM.getEntityById(p.entityCol);
                    auto& entity_colisioned_stats = EM.getComponent<EstadisticaCmp>(entity_colisioned);

                    if(e.hasTAG<TPlayer>()){
                        if(entity_colisioned.hasTAG<TEnemy>() || entity_colisioned.hasTAG<TDistEnemy>()) {
                            stats.hitpoints -= entity_colisioned_stats.damage;
                            if(stats.hitpoints <= 0) { e.setDestroy(); } //set to destroy
                        }
                    }
                    else if(e.hasTAG<TEnemy>() || e.hasTAG<TDistEnemy>()){
                        if(entity_colisioned.hasTAG<TBullet>()) {
                            stats.hitpoints -= entity_colisioned_stats.damage;
                            if(stats.hitpoints <= 0) { 
                                soundMonster(EM, e);
                                e.setDestroy(); } //set to destroy
                        }
                        else if(entity_colisioned.hasTAG<TPlayer>()) {
                            entity_colisioned_stats.hitpoints -= stats.damage;
                            if(entity_colisioned_stats.hitpoints <= 0) { entity_colisioned.setDestroy(); } //set to destroy
                        }
                    }
                    else if(e.hasTAG<TBullet>()) {
                        if(entity_colisioned.hasTAG<TEnemy>() || entity_colisioned.hasTAG<TDistEnemy>()) {
                            entity_colisioned_stats.hitpoints -= stats.damage;
                            if(entity_colisioned_stats.hitpoints <= 0) { entity_colisioned.setDestroy(); } //set to destroy
                        }
                        e.setDestroy(); //set to destroy
                    }

                    ////valores por defecto
                    p.colision = 0;
                    p.entityCol = 0;
                }

                
            }
        );
    }

    void soundMonster(EntyMan& EM, Enty& e) {
    EM.getComponent<SoundCmp>(e).parametro=2;
    EM.getComponent<SoundCmp>(e).cambia=true;
    EM.getComponent<SoundCmp>(e).play=true;
    for(auto& en : EM.getEntities()){
        if(en.hasTAG<TPlayer>()){
            EM.getComponent<SoundCmp>(en).parametro=1;
            EM.getComponent<SoundCmp>(en).cambia=true;
            EM.getComponent<SoundCmp>(en).play=true;
        }
    }
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