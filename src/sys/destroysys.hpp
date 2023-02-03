#pragma once
#include "../util/types.hpp"

struct DestroySys {
    using SYSCMPs = MP::Typelist<EstadoCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, EstadoCmp& estado){
                std::cout<<e.getID()<<"\n";
                if(estado.alive == 1){
                    std::cout<<"Tamaño de vector: "<<EM.getEntities().size()<<"\n";
                    std::cout<<"Entidad "<<e.getID()<<" destruida\n";
                    EM.destroyEntity(e);
                    std::cout<<"Tamaño de vector: "<<EM.getEntities().size()<<"\n";
                }
                std::cout<<"a\n";
            }
        );
        std::cout<<"b\n";
    }
};