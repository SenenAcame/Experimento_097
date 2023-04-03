#pragma once
#include "../util/types.hpp"
#include <vector>
#include <algorithm>


struct NodeMapSys {

    using EneCMPs = MP::Typelist<PhysicsCmp2, AICmp>;
    using PlayCMPs = MP::Typelist<PhysicsCmp2>;
    using PlayTAGs = MP::Typelist<TPlayer>;
    using NodoCMPs = MP::Typelist<NodoCmp>;
    using MapTAGs = MP::Typelist<TMap>;
    using MapTAGsSpawns = MP::Typelist<TSpawn>;
    using EneTAGs = MP::Typelist<TEnemy>;

    int getSala(NodoCmp& map, float x, float z){
        int devol = -1;
        for(int i=0;i<map.salas.size();i++){
            if((map.salas.at(i).x + map.salas.at(i).tamx) >= x && (map.salas.at(i).x - map.salas.at(i).tamx) <= x && (map.salas.at(i).z + map.salas.at(i).tamz) >= z && (map.salas.at(i).z - map.salas.at(i).tamz) <= z){
                devol=i;
                //std::cout << "Soy player y estoy: x= " << x << ", z= " << z << " sala: " << devol+1 << std::endl;
            }
        }
        return devol;
    }

    void update(EntyMan& EM){
        float playerposx, playerposz;
        Enty player;
        NodoCmp map;
        EM.foreach<PlayCMPs, PlayTAGs>(
            [&](Enty& p, PhysicsCmp2& phy) {
                playerposx=phy.x;
                playerposz=phy.z;
                player=p;
            }
        );
        EM.foreach<NodoCMPs, MapTAGs>(
            [&](Enty& en, NodoCmp& n) {
                map=n;
            }
        );
        int salaplayer = getSala(map, playerposx, playerposz);
        EM.getComponent<SalaCmp>(player).sala = salaplayer; 
        EM.foreach<EneCMPs, EneTAGs>(
            [&](Enty& en, PhysicsCmp2& p, AICmp& ai) {
                int salaene = getSala(map, p.x, p.z);
                if(ai.behaviour!=SB::Diying){
                    if( salaplayer == salaene || salaene==-1){
                        if(en.hasTAG<TDistEnemy>()) 
                        EM.getComponent<SalaCmp>(en).sala = salaene;
                        if(en.hasTAG<TDistEnemy>() && sqrt((p.x-playerposx)*(p.x-playerposx)+(p.z-playerposz)*(p.z-playerposz))<40 && salaene!=-1){    
                            ai.behaviour=SB::Shoot;
                        }
                        else
                            ai.behaviour=SB::Two_Steps;
                    }
                    else{
                        EM.getComponent<SalaCmp>(player).sala = salaplayer;
                        EM.getComponent<SalaCmp>(en).sala = salaene ;
                        ai.behaviour=SB::Patrol;
                        puerta nextcoord ={0, 0};
                        float dist=MAXFLOAT;
                        for(unsigned int i=0; i<map.salas.at(salaene).puertas.size(); i++){
                            
                            float distx=playerposx-map.salas.at(salaene).puertas.at(i).x;
                            float distz=playerposz-map.salas.at(salaene).puertas.at(i).z;
                            if(dist>(sqrt((distx*distx)+(distz*distz)))){
                                dist=sqrt((distx*distx)+(distz*distz));
                                nextcoord=map.salas.at(salaene).puertas.at(i);
                            }
                        }
                        ai.ox=nextcoord.x;
                        ai.oz=nextcoord.z;
                    }
                }
            }
        );
        //EM.foreach<MapTAGsSpawns>(
        //    //poner temporizador para que no compruebe todo el rato
        //    [&](Enty& spawn, PhysicsCmp2& p, SpawnCmp& spawnC) {
        //        if( spawnC.sala == salaplayer){
        //            spawnC.active = 1;
        //        }
        //    }
//
        //    
//
        //);
    }

    std::vector<sala> static creaSalas(){
        /*float salasx[]={-52.39f, -41.91f, -34.82f, -34.87f, 7.31f,   28.71f, 46.04f,   46.04f};
        float salasz[]={140.98f, 85.41f,  43.17f,  0.91f,   -25.91f, 0.89f,  -110.79f, -146.09f};
        float tamx[]=  {62.51/2, 83.34/2, 69.6/2, 69.6/2, 15/2, 27.78/2, 62.51/2, 62.51/2};
        float tamz[]=  {41.67/2, 69.46/2, 15/2, 69.46/2, 294/2, 69.46/2, 55.56/2, 15/2};*/

        float salasx[]={107.5f, 49.f, 25.f, -33.5f, -33.5f, -21.5f, 37.5f, 95.5f, 107.5f};
        float salasz[]={57.49f, 57.5f, 33.5f, 33.5f, -25.f, -61.f, -60.98f, -60.98f, -13.f};
        float tamx[]=  {69/2, 48/2, 48/2, 69/2, 24/2, 48/2, 69/2, 48/2, 24/2};
        float tamz[]=  {69/2, 24/2, 24/2, 69/2, 48/2, 24/2, 69/2, 24/2, 72/2};



        std::vector<sala> sala;
        std::vector<puerta> puertass1;
        puertass1.push_back({72, 57.5});
        puertass1.push_back({107.5, 21.99});

        //puertass1.push_back({-63.53, 119.12});

        std::vector<puerta> puertass2;
        puertass2.push_back({74, 57.5});
        puertass2.push_back({37, 44.5});

        //puertass2.push_back({-63.53, 121.12});
        //puertass2.push_back({-33.56, 49.68});
        //puertass2.push_back({1.12, 77.19});

        std::vector<puerta> puertass3;
        puertass3.push_back({37, 46.5});
        puertass3.push_back({0, 33.5});

        //puertass3.push_back({-33.56, 51.68});
        //puertass3.push_back({-47.90, 34.68});
        //puertass3.push_back({1.12, 42.64});

        std::vector<puerta> puertass4;
        puertass4.push_back({2, 33.5});
        puertass4.push_back({-33.5, -2});

        //puertass4.push_back({-47.35, 36.68});
        //puertass4.push_back({1.12, -0.84});

        std::vector<puerta> puertass5;
        puertass5.push_back({-33.5, 0});
        puertass5.push_back({-33.5, -49.97});

        //puertass5.push_back({-1.12, 77.19});
        //puertass5.push_back({-1.12, 42.64});
        //puertass5.push_back({-1.12, -0.84});
        //puertass5.push_back({15.82, -0.84});
        //puertass5.push_back({15.82, -107.05});
        //puertass5.push_back({15.82, -146.09});

        std::vector<puerta> puertass6;
        puertass6.push_back({-33.5, -47.97});
        puertass6.push_back({3.5, -60.99});

        //puertass6.push_back({13.82, -0.84});

        std::vector<puerta> puertass7;
        puertass7.push_back({1.5, -60.99});
        puertass7.push_back({72.5, -60.99});

        //puertass7.push_back({13.82, -107.05});
        //puertass7.push_back({56.78, -137.6});

        std::vector<puerta> puertass8;
        puertass8.push_back({70.5, -60.99});
        puertass8.push_back({107.5, -48});

        //puertass8.push_back({13.82, -146.09});
        //puertass8.push_back({56.78, -139.6});

        std::vector<puerta> puertass9;
        puertass9.push_back({107.5, 23.99});
        puertass9.push_back({107.5, -50});

        std::vector<puerta> todaspuertas[]={puertass1, puertass2, puertass3, puertass4, puertass5, puertass6, puertass7, puertass8, puertass9};

        for(unsigned int i=0; i<9;i++){
            sala.push_back({salasx[i],salasz[i],tamx[i],tamz[i],todaspuertas[i]});
        }
        return sala;
    };
};