#pragma once
#include "../util/types.hpp"

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2& p) {
                //para todas las e comparo con todas las a
                for(auto& a : EM.getEntities()){
                    //if(a.hasTAG<TMap>()){
                    //    //Aqui las que no tienen estado
                    //   
                    //}
                    if(a.hasTAG<TEnemy>() || a.hasTAG<TBullet>() ){
                        if(a.hasCMP<EstadoCmp>()){
                            
                            if( EM.getComponent<EstadoCmp>(a).colision == 0){
                                //std::cout<<"Impacto\n";
                                //si tiene he colisionado = false compruebo
                                 auto dx = p.x - EM.getComponent<PhysicsCmp2>(a).x;
                                 auto dy = p.y - EM.getComponent<PhysicsCmp2>(a).y;
                                 auto dz = p.z - EM.getComponent<PhysicsCmp2>(a).z;
                                 auto dist = std::sqrt(dx*dx+dy*dy+dz*dz);
                                 if(dist <= 0.5 && dist!=0.0){
                            //         std::cout<<"Impacto\n";
                            //         //marcar el estado a he colisionado con el id de E
                                     EM.getComponent<EstadoCmp>(a).colision = 1;
                                     EM.getComponent<EstadoCmp>(a).entityCol = e.getID();
                                     //std::cout<<EM.getComponent<EstadoCmp>(a).colision <<"Impacto\n";
                                     //std::cout<<EM.getComponent<EstadoCmp>(a).entityCol <<"Impacto\n";

                                }
                            }
                        }

                    }
                    
                   
                    
                    
                }
                //for(auto& a : EM.getStorage().getStorage<PhysicsCmp2>()) {
                //    auto dx = p.x - a.x;
                //    auto dy = p.y - a.y;
                //    auto dz = p.z - a.z;
                //    auto dist = std::sqrt(dx*dx+dy*dy+dz*dz);
                //    if(dist <= 0.5 && dist!=0.0){
                //        std::cout<<"Impacto\n";
//
                //        //EM.destroyEntity(e);
                //        //EM.removeComponent<RenderCmp2>(e);
                //    }
                //}
            }
        );
    }
};