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
    using EneTAGs = MP::Typelist<>;

    sala enemySala(EntyMan& EM, PhysicsCmp2& p, NodoCmp& mapa){
        sala sala = {0,0,0,0};
        for(int i=0;i<mapa.salas.size();i++){
            if((mapa.salas.at(i).x + mapa.salas.at(i).tamx) >= p.x && (mapa.salas.at(i).x - mapa.salas.at(i).tamx) <= p.x && (mapa.salas.at(i).z + mapa.salas.at(i).tamz) >= p.z && (mapa.salas.at(i).z - mapa.salas.at(i).tamz) <= p.z){
                return mapa.salas.at(i);
            }
        }
        return sala;
    };

    /*sala salaPlayer(EntyMan& EM){
        sala sala = {0,0,0,0};
        EM.foreach<PhyCMPs, PlayTAGs>(
            [&](Enty& e, PhysicsCmp2& p) {
                EM.foreach<NodoCMPs, MapTAGs>(
                    [&](Enty& en, NodoCmp& n) {
                        for(int i=0;i<n.salas.size();i++){
                            if((n.salas.at(i).x + n.salas.at(i).tamx) >= p.x && (n.salas.at(i).x - n.salas.at(i).tamx) <= p.x && (n.salas.at(i).z + n.salas.at(i).tamz) >= p.z && (n.salas.at(i).z - n.salas.at(i).tamz) <= p.z){
                                sala=n.salas.at(i);
                                std::cout << "Soy player y estoy: x= " << p.x << ", z= " << p.z << std::endl;
                            }
                        }
                    }
                );
            }
        );
        return sala;
    };*/

    sala salaPlayer(EntyMan& EM, float x, float z){
        sala sala={0,0,0,0};
        EM.foreach<NodoCMPs, MapTAGs>(
            [&](Enty& en, NodoCmp& n) {
                for(int i=0;i<n.salas.size();i++){
                    if((n.salas.at(i).x + n.salas.at(i).tamx) >= x && (n.salas.at(i).x - n.salas.at(i).tamx) <= x && (n.salas.at(i).z + n.salas.at(i).tamz) >= z && (n.salas.at(i).z - n.salas.at(i).tamz) <= z){
                        sala=n.salas.at(i);
                        //std::cout << "Soy player y estoy: x= " << x << ", z= " << z << std::endl;
                    }
                }
            }
        );
        return sala;
    }

    void update(EntyMan& EM){
        float playerposx, playerposz;
        EM.foreach<PlayCMPs, PlayTAGs>(
            [&](Enty& p, PhysicsCmp2& phy) {
                playerposx = phy.x;
                playerposz = phy.z;
            }
        );
        sala salaplayer = salaPlayer(EM, playerposx, playerposz);
        
        EM.foreach<NodoCMPs, MapTAGs>(
            [&](Enty& en, NodoCmp& n) {
                EM.foreach<EneCMPs, EneTAGs>(
                    [&](Enty& en, PhysicsCmp2& p, AICmp& ai) {
                        sala salaene = enemySala(EM, p, n);
                        if(salaplayer.x==salaene.x && salaplayer.z==salaene.z){
                            if(en.hasTAG<TDistEnemy>() && sqrt((p.x-playerposx)*(p.x-playerposx)+(p.z-playerposz)*(p.z-playerposz))<40){    
                                ai.behaviour=SB::Shoot;
                            }
                            else
                                ai.behaviour=SB::Seek;
                        }
                        else{
                            ai.behaviour=SB::Patrol;
                            puerta nextcoord ={0, 0};
                            float dist=MAXFLOAT;
                            for(unsigned int i=0; i<salaene.puertas.size(); i++){
                                float distx=playerposx-salaene.puertas.at(i).x;
                                float distz=playerposz-salaene.puertas.at(i).z;
                                if(dist>(sqrt((distx*distx)+(distz*distz)))){
                                    dist=sqrt((distx*distx)+(distz*distz));
                                    nextcoord=salaene.puertas.at(i);
                                }
                            }
                            ai.ox=nextcoord.x;
                            ai.oz=nextcoord.z;
                        }
                    }
                );
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

    std::vector<sala> creaSalas(){
        float salasx[]={-52.39f, -41.91f, -34.82f, -34.87f, 7.31f,   28.71f, 46.04f,   46.04f};
        float salasz[]={140.98f, 85.41f,  43.17f,  0.91f,   -25.91f, 0.89f,  -110.79f, -146.09f};
        float tamx[]=  {62.51/2, 83.34/2, 69.6/2, 69.6/2, 15/2, 27.78/2, 62.51/2, 62.51/2};
        float tamz[]=  {41.67/2, 69.46/2, 15/2, 69.46/2, 294/2, 69.46/2, 55.56/2, 15/2};

        std::vector<sala> sala;
        std::vector<puerta> puertass1;
        puertass1.push_back({-63.53, 119.12});

        std::vector<puerta> puertass2;
        puertass2.push_back({-63.53, 121.12});
        puertass2.push_back({-33.56, 49.68});
        puertass2.push_back({1.12, 77.19});

        std::vector<puerta> puertass3;
        puertass3.push_back({-33.56, 51.68});
        puertass3.push_back({-47.90, 34.68});
        puertass3.push_back({1.12, 42.64});

        std::vector<puerta> puertass4;
        puertass4.push_back({-47.35, 36.68});
        puertass4.push_back({1.12, -0.84});

        std::vector<puerta> puertass5;
        puertass5.push_back({-1.12, 77.19});
        puertass5.push_back({-1.12, 42.64});
        puertass5.push_back({-1.12, -0.84});
        puertass5.push_back({15.82, -0.84});
        puertass5.push_back({15.82, -107.05});
        puertass5.push_back({15.82, -146.09});

        std::vector<puerta> puertass6;
        puertass6.push_back({13.82, -0.84});

        std::vector<puerta> puertass7;
        puertass7.push_back({13.82, -107.05});
        puertass7.push_back({56.78, -137.6});

        std::vector<puerta> puertass8;
        puertass8.push_back({13.82, -146.09});
        puertass8.push_back({56.78, -139.6});

        std::vector<puerta> todaspuertas[]={puertass1, puertass2, puertass3, puertass4, puertass5, puertass6, puertass7, puertass8};

        for(unsigned int i=0; i<8;i++){
            sala.push_back({salasx[i],salasz[i],tamx[i],tamz[i],todaspuertas[i]});
        }
        return sala;
    };
};