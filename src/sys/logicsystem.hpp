#pragma once
#include "../util/types.hpp"

struct LogicSystem {
    using SYSCMPs = MP::Typelist<EstadoCmp, EstadisticaCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs >(
            [&](Enty& e, EstadoCmp& p, EstadisticaCmp& stats) {
                if(p.colision !=0){
                    if(e.hasTAG<TPlayer>()){
                        if(EM.getEntityById(p.entityCol).hasTAG<TEnemy>()){
                            stats.hitpoints -=EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).damage;
                            if(stats.hitpoints <=0){
                                //p.alive=1; //set to destroy
                                e.setDestroy();
                            }
                            //std::cout<<"SOY Jugador: "<<e.getID()<<"Tenia: "<<stats.hitpoints<<" HE CHOCADO CON UNA BALA: "<<p.entityCol<<
                            //" y ahora tengo" <<stats.hitpoints<<"\n";
                        }
                    }
                    else if(e.hasTAG<TEnemy>()){
                        
                        if(EM.getEntityById(p.entityCol).hasTAG<TBullet>()){
                            
                            stats.hitpoints -= EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).damage;
                            if(stats.hitpoints <=0){
                                //p.alive=1; //set to destroy
                                e.setDestroy();
                                //std::cout<<"Ahora tengo estado "<<p.alive<<"\n";
                            }
                           // std::cout<<"SOY ENTIDAD: "<<e.getID()<<" Tenia: "<<stats.hitpoints<<" HE CHOCADO CON UNA BALA: "<<p.entityCol<<
                           // " y ahora tengo" <<stats.hitpoints<<"\n";
                        }
                        else if(EM.getEntityById(p.entityCol).hasTAG<TPlayer>()){

                            EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints -= stats.damage;
                            if(EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints<=0){
                                //EM.getComponent<EstadoCmp>(EM.getEntityById(p.entityCol)).alive = 1; //set to destroy
                                EM.getEntityById(p.entityCol).setDestroy();
                            }

                        }
                        else if(EM.getEntityById(p.entityCol).hasTAG<TEnemy>()){
                            //std::cout<<"SOY ENTIDAD: "<<e.getID()<<" HE CHOCADO CON UN Enemigo: "<<p.entityCol<<"\n";

                        }
                    }
                    else if(e.hasTAG<TBullet>()){
                        if(EM.getEntityById(p.entityCol).hasTAG<TEnemy>()){
                            EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints -= stats.damage;
                            if(EM.getComponent<EstadisticaCmp>(EM.getEntityById(p.entityCol)).hitpoints<=0){
                                //EM.getComponent<EstadoCmp>(EM.getEntityById(p.entityCol)).alive = 1;
                                EM.getEntityById(p.entityCol).setDestroy(); //set to destroy
                            }
                        }
                        //p.alive = 1; //set to destroy
                        e.setDestroy();
                    }
                    ////valores por defecto
                    p.colision = 0;
                    p.entityCol = 0;
                }
            }
        );
    }
};