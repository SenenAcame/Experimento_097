#pragma once
#include "../util/types.hpp"

struct ColSys2 {
    using SYSCMPs  = MP::Typelist<PhysicsCmp2>;
    using SYSCMPs2 = MP::Typelist<EstadoCmp>;
    using SYSTAGs  = MP::Typelist<>;

    void update(EntyMan& EM) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2& p) {
                EM.foreach<SYSCMPs2, SYSTAGs>(
                    [&](Enty& a, EstadoCmp& est){
                        if((e.getID()!=a.getID()) &&
                           (a.hasTAG<TPlayer>() || a.hasTAG<TEnemy>() || a.hasTAG<TBullet>()) &&
                           (est.colision == 0))
                        {
                            auto& phy = p;
                            auto& phy2 = EM.getComponent<PhysicsCmp2>(a);
                            float tamx=0, tamy=0, tamz=0, tamx2=0, tamy2=0, tamz2=0;
                            float dx, dy, dz;
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
                                if(a.hasTAG<TBullet>() && e.hasTAG<TEnemy>()){
                                    EM.getComponent<SoundCmp>(e).parametro=0;
                                    EM.getComponent<SoundCmp>(e).cambia=true;
                                    EM.getComponent<SoundCmp>(e).play=true;
                                }
                                est.colision = 1<<1;
                                est.entityCol = e.getID();
                                if(a.hasTAG<TPlayer>() && est.colision ==1){
                                    std::cout<<"Soy player y he chocado\n";
                                }
                            }
                        }
                    }
                );
            }
        );
    }
};


// Viejo codigo del update del sistema de colisiones

//EM.foreach<SYSCMPs, SYSTAGs>(
//    [&](Enty& e, PhysicsCmp2& p) {
//        for(auto& a : EM.getEntities()){
//            if(e.getID()!=a.getID()){
//                if(a.hasTAG<TPlayer>() || a.hasTAG<TEnemy>() || a.hasTAG<TBullet>() ){
//                    if(a.hasCMP<EstadoCmp>()){
//                        if( EM.getComponent<EstadoCmp>(a).colision == 0){
//                            auto& phy = p;
//                            auto& phy2 = EM.getComponent<PhysicsCmp2>(a);
//                            float tamx=0, tamy=0, tamz=0, tamx2=0, tamy2=0, tamz2=0;
//                            if(e.hasTAG<TPlayer>()|| e.hasTAG<TEnemy>()){
//                                tamx=0.8;
//                                tamy=2.5;
//                                tamz=2;
//                            }
//                            if(a.hasTAG<TPlayer>()|| a.hasTAG<TEnemy>()){
//                                tamx2=0.8;
//                                tamy2=2.5;
//                                tamz2=2;
//                            }
//                            float dx, dy, dz;
//                            if((dx = phy.x - phy2.x) < 0)
//                                dx=-dx;
//                            dx -= (tamx + tamx2);
//                            if((dy = phy.y - phy2.y) < 0)
//                                dy=-dy;
//                            dy -= (tamy + tamy2);
//                            if((dz = phy.z - phy2.z) < 0)
//                                dz=-dz;
//                            dz -= (tamz + tamz2);
//                            if(dx<=0 && dy<=0 && dz<=0){
//                                if(a.hasTAG<TBullet>()&&e.hasTAG<TEnemy>()){
//                                    SS.changesound(EM.getComponent<SoundCmp>(e),0);
//                                    SS.startsound(EM.getComponent<SoundCmp>(e));
//                                }
//                                EM.getComponent<EstadoCmp>(a).colision = 1<<1;
//                                EM.getComponent<EstadoCmp>(a).entityCol = e.getID();
//                                if(a.hasTAG<TPlayer>() && EM.getComponent<EstadoCmp>(a).colision ==1){
//                                    std::cout<<"Soy player y he chocado\n";
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//);