#pragma once
#include "../util/types.hpp"
#include <vector>
#include <algorithm>


struct NodeMapSys {

    using EneCMPs = MP::Typelist<PhysicsCmp2, AICmp>;
    //using PlayTAGs = MP::Typelist<TPlayer>;
    using NodoCMPs = MP::Typelist<NodoCmp>;
    using MapTAGs = MP::Typelist<TMap>;
    using EneTAGs = MP::Typelist<TEnemy>;

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
                        std::cout << "Soy player y estoy: x= " << x << ", z= " << z << std::endl;
                    }
                }
            }
        );
        return sala;
    }

    void update(EntyMan& EM, auto cam){
        sala salaplayer = salaPlayer(EM, cam->getPosition().X, cam->getPosition().Z);
        EM.foreach<NodoCMPs, MapTAGs>(
            [&](Enty& en, NodoCmp& n) {
                EM.foreach<EneCMPs, EneTAGs>(
                    [&](Enty& en, PhysicsCmp2& p, AICmp& ai) {
                        sala salaene = enemySala(EM, p, n);
                        if(salaplayer.x==salaene.x && salaplayer.z==salaene.z){
                            ai.behaviour=SB::Seek;
                        }
                        else{
                            ai.behaviour=SB::Patrol;
                            puerta nextcoord ={0, 0};
                            float dist=MAXFLOAT;
                            for(unsigned int i=0; i<salaene.puertas.size(); i++){
                                float distx=salaplayer.x-salaene.puertas.at(i).x;
                                float distz=salaplayer.z-salaene.puertas.at(i).z;
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
    }

    std::vector<sala> creaSalas(){
        float salasx[]={-39.61f, -29.12f, -22.18f, -22.18f, 17.68f,  36.79f, 54.1f,  54.1f};
        float salasz[]={144.49f, 88.92f,  48.98f,  9.04f,   -23.32f, 9.08f,  -83.5f, -116.46f};
        float tamx[]=  {62.51/2, 83.34/2, 69.6/2, 69.6/2, 10.27/2, 27.78/2, 62.51/2, 62.51/2};
        float tamz[]=   {41.67/2, 69.46/2, 10.42/2, 69.46/2, 294/2, 69.46/2, 55.56/2, 10.42/2};

        std::vector<sala> sala;
        std::vector<puerta> puertass1;
        puertass1.push_back({-57.66, 122.65});

        std::vector<puerta> puertass2;
        puertass2.push_back({-57.66, 124.65});
        puertass2.push_back({-12.28, 53.19});
        puertass2.push_back({11.62, 88.96});

        std::vector<puerta> puertass3;
        puertass3.push_back({-45.35, 42.77});
        puertass3.push_back({-12.28, 55.19});
        puertass3.push_back({11.62, 88.96});

        std::vector<puerta> puertass4;
        puertass4.push_back({-45.35, 44.77});
        puertass4.push_back({11.62, 9.04});

        std::vector<puerta> puertass5;
        puertass5.push_back({13.62, 88.96});
        puertass5.push_back({13.62, 47.24});
        puertass5.push_back({13.62, 9.04});
        puertass5.push_back({21.89, 12.72});
        puertass5.push_back({21.89, -83.08});
        puertass5.push_back({21.89, -116.36});

        std::vector<puerta> puertass6;
        puertass6.push_back({23.89, 12.72});

        std::vector<puerta> puertass7;
        puertass7.push_back({21.89, -83.08});
        puertass7.push_back({61.10, -112.29});

        std::vector<puerta> puertass8;
        puertass8.push_back({23.89, -116.36});
        puertass8.push_back({61.10, -110.29});

        sala.push_back({salasx[0],salasz[0],tamx[0],tamz[0],puertass1});
        sala.push_back({salasx[1],salasz[1],tamx[1],tamz[1],puertass2});
        sala.push_back({salasx[2],salasz[2],tamx[2],tamz[2],puertass3});
        sala.push_back({salasx[3],salasz[3],tamx[3],tamz[3],puertass4});
        sala.push_back({salasx[4],salasz[4],tamx[4],tamz[4],puertass5});
        sala.push_back({salasx[5],salasz[5],tamx[5],tamz[5],puertass6});
        sala.push_back({salasx[6],salasz[6],tamx[6],tamz[6],puertass7});
        sala.push_back({salasx[7],salasz[7],tamx[7],tamz[7],puertass8});

        return sala;
    };
};