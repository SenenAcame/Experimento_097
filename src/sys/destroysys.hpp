#pragma once
#include "../util/types.hpp"

struct DestroySys {
    using SYSCMPs = MP::Typelist<EstadoCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, EstadoCmp& estado){
                if(estado.alive == 1){
                    std::cout<<"Entidad "<<e.getID()<<" destruida\n";
                    EM.destroyEntity(e);
                }
            }
        );
    }
};