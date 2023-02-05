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
                    if(e.getID()!=a.getID()){
                    //if(a.hasTAG<TMap>()){
                    //    //Aqui las que no tienen estado
                    //   
                    //}
                    if(a.hasTAG<TPlayer>() || a.hasTAG<TEnemy>() || a.hasTAG<TBullet>() ){
                        if(a.hasCMP<EstadoCmp>()){
                            
                            if( EM.getComponent<EstadoCmp>(a).colision == 0){
                                auto& phy = p;
                                auto& phy2 = EM.getComponent<PhysicsCmp2>(a);
                                float tamx=0, tamy=0, tamz=0, tamx2=0, tamy2=0, tamz2=0;
                                if(e.hasTAG<TPlayer>()|| e.hasTAG<TEnemy>()){
                                    tamx=0.8;
                                    tamy=2.5;
                                    tamz=2;
                                }
                                if(a.hasTAG<TPlayer>()|| a.hasTAG<TEnemy>()){
                                    tamx2=0.8;
                                    tamy2=2.5;
                                    tamz2=2;
                                }
                                float dx, dy, dz;
                                if((dx = phy.x - phy2.x) < 0)
                                    dx=-dx;
                                dx -= (tamx + tamx2);
                                
                                if((dy = phy.y - phy2.y) < 0)
                                    dy=-dy;
                                dy -= (tamy + tamy2);
                                if((dz = phy.z - phy2.z) < 0)
                                    dz=-dz;
                                dz -= (tamz + tamz2);

                                if(dx<=0 && dy<=0 && dz<=0){
                                    if(a.hasTAG<TBullet>()&&e.hasTAG<TEnemy>()){
                                        EM.getComponent<SoundCmp>(e).parametro=0;
                                        EM.getComponent<SoundCmp>(e).play=true;
                                    }
                                    
                                //std::cout<<"Impacto\n";
                                //si tiene he colisionado = false compruebo
                                 //auto dx = p.x - EM.getComponent<PhysicsCmp2>(a).x;
                                 //auto dy = p.y - EM.getComponent<PhysicsCmp2>(a).y;
                                 //auto dz = p.z - EM.getComponent<PhysicsCmp2>(a).z;
                                 //auto dist = std::sqrt(dx*dx+dy*dy+dz*dz);
                                 //if(dist <= 0.5 && dist!=0.0){
                                    std::cout << phy.x << " , " << phy2.x << std::endl;
                                    std::cout << phy.y << " , " << phy2.y << std::endl;
                                    std::cout << phy.z << " , " << phy2.z << std::endl<< std::endl;
                            //         std::cout<<"Impacto\n";
                            //         //marcar el estado a he colisionado con el id de E
                                    //00000010 --> colision,
                                     EM.getComponent<EstadoCmp>(a).colision = 1<<1;
                                     EM.getComponent<EstadoCmp>(a).entityCol = e.getID();
                                     if(a.hasTAG<TPlayer>() && EM.getComponent<EstadoCmp>(a).colision ==1){
                                         std::cout<<"Soy player y he chocado\n";
                                     }
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
            }
        );
    }
};