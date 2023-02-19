#pragma once
#include "../util/types.hpp"

struct ColSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<TInteract>;

    void update(EntyMan& EM) {
        //std::cout<<"\n";
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& main_entity, PhysicsCmp2& main_phy, EstadoCmp& main_stats) {
                EM.foreach<SYSCMPs, SYSTAGs>(
                    [&](Enty& collisioned_entity, PhysicsCmp2& collisioned_phy, EstadoCmp& collisioned_stats){
                        if((main_entity.getID() != collisioned_entity.getID()) && 
                           (collisioned_stats.colision == 0))
                        {
                            float tamx = 0, tamy = 0, tamz = 0, tamx2 = 0, tamy2 = 0, tamz2 = 0;
                            float dx, dy, dz;

                            tamx = tamx2 = 0.8;
                            tamy = tamy2 = 2.5;
                            tamz = tamz2 = 2;

                            if((dx = main_phy.x - collisioned_phy.x) < 0)
                                dx = -dx;
                            dx -= (tamx + tamx2);

                            if((dy = main_phy.y - collisioned_phy.y) < 0)
                                dy = -dy;
                            dy -= (tamy + tamy2);

                            if((dz = main_phy.z - collisioned_phy.z) < 0)
                                dz = -dz;
                            dz -= (tamz + tamz2);

                            if(dx<=0 && dy<=0 && dz<=0){
                                if(collisioned_entity.hasTAG<TBullet>() && main_entity.hasTAG<TEnemy>()){
                                    auto& sound = EM.getComponent<SoundCmp>(main_entity);
                                    EM.changeSound(sound, 0);
                                }
                                collisioned_stats.colision  = 1<<1;
                                collisioned_stats.entityCol = main_entity.getID();
                                
                                main_stats.colision = 1<<1;
                                main_stats.entityCol = collisioned_entity.getID();
                            }
                        }
                    }
                );
                //std::cout<<"Soy "<<main_entity.getID()<<" y he colisionado contra "<<main_stats.entityCol<<"\n";
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