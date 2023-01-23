#pragma once
#include "../util/types.hpp"
#include <iostream>

struct LogicSystem {
    using SYSCMPs = MP::Typelist<EstadoCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs >(
            [&](Enty& e, EstadoCmp& p) {
                if(p.colision !=0){
                    if(EM.getEntityById(p.entityCol).hasTAG<TBullet>()){
                  //std::cout<<"XDNT\n";
                        std::cout<<"SOY ENTIDAD: "<<e.getID()<<" HE CHOCADO CON UNA BALA: "<<p.entityCol<<"\n";
                    }
                    else if(EM.getEntityById(p.entityCol).hasTAG<TEnemy>()){
                        std::cout<<"SOY ENTIDAD: "<<e.getID()<<" HE CHOCADO CON UN Enemigo: "<<p.entityCol<<"\n";
    
                    }
                }
                ////valores por defecto
                p.colision = 0;
                p.entityCol = 0;
            }
        );
    }
};