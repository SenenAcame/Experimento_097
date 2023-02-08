#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "../util/types.hpp"

struct NodeMapSys {

    int k=0;

    using PhyCMPs = MP::Typelist<PhysicsCmp2>;
    using PlayTAGs = MP::Typelist<TPlayer>;
    using NodoCMPs = MP::Typelist<NodoCmp>;
    using MapTAGs = MP::Typelist<TMap>;
    using EneTAGs = MP::Typelist<TEnemy>;

    nodo createNode(float posx, float posz, float tamax, float tamaz){
        nodo nodo{posx, posz, tamax, tamaz};
        return nodo;
    }

    nodo findNodeEne(EntyMan& EM, PhysicsCmp2& p, NodoCmp& mapa){
        nodo nodo = createNode(0,0,0,0);
        for(int i=0;i<mapa.nodos.size();i++){
            //Me devuelve la posicion 0,0 y salta error en 111


            std::cout << i << ". " << mapa.nodos.at(i).x + mapa.nodos.at(i).tamx << " >= " << p.x << " , " << mapa.nodos.at(i).x - mapa.nodos.at(i).tamx << " <= " << p.x << std::endl;
            std::cout << mapa.nodos.at(i).z + mapa.nodos.at(i).tamz << " >= " << p.z << " , " << mapa.nodos.at(i).z - mapa.nodos.at(i).tamz << " <= " << p.z << std::endl << std::endl;
            if((mapa.nodos.at(i).x + mapa.nodos.at(i).tamx) >= p.x && (mapa.nodos.at(i).x - mapa.nodos.at(i).tamx) <= p.x && (mapa.nodos.at(i).z + mapa.nodos.at(i).tamz) >= p.z && (mapa.nodos.at(i).z - mapa.nodos.at(i).tamz) <= p.z){
                return mapa.nodos.at(i);
            }
        }
        //std::cout << "patata" << std::endl << std::endl ;
        return nodo;
    };

    nodo findNodePlayer(EntyMan& EM){
        nodo nodo = createNode(0,0,0,0);
        EM.foreach<PhyCMPs, PlayTAGs>(
            [&](Enty& e, PhysicsCmp2& p) {
                EM.foreach<NodoCMPs, MapTAGs>(
                    [&](Enty& en, NodoCmp& n) {
                        for(int i=0;i<n.nodos.size();i++){
                            //std::cout << i << ". " << n.nodos.at(i).x + n.nodos.at(i).tamx << " >= " << p.x << " , " << n.nodos.at(i).x - n.nodos.at(i).tamx << " <= " << p.x << std::endl;
                            //std::cout << n.nodos.at(i).z + n.nodos.at(i).tamz << " >= " << p.z << " , " << n.nodos.at(i).z - n.nodos.at(i).tamz << " <= " << p.z << std::endl << std::endl;
            
                            if((n.nodos.at(i).x + n.nodos.at(i).tamx) >= p.x && (n.nodos.at(i).x - n.nodos.at(i).tamx) <= p.x && (n.nodos.at(i).z + n.nodos.at(i).tamz) >= p.z && (n.nodos.at(i).z - n.nodos.at(i).tamz) <= p.z){
                                //std::cout << "Jugador " << n.nodos.at(i).x << " , " << n.nodos.at(i).z << std::endl;
                                nodo=n.nodos.at(i);
                            }
                        }
                    }
                );
            }
        );
        return nodo;
    };

    void update(EntyMan& EM){
        /*std::vector<nodo> ruta;
        std::vector<nodo> novalen;
        nodo final;
        nodo player = findNodePlayer(EM);
        nodo enemy;
        EM.foreach<NodoCMPs, MapTAGs>(
            [&](Enty& e, NodoCmp& mapa) {
                EM.foreach<PhyCMPs, EneTAGs>(
                    [&](Enty& en, PhysicsCmp2& p) {
                        enemy = findNodeEne(EM, p, mapa);
                        final = findRute(enemy, player, ruta, novalen);

                        std::cout << "final " << final.x << " , " << final.z << std::endl << std::endl;
                    }
                );
            }
        );*/

    };

    nodo findRute(nodo& enemy, nodo& player, std::vector<nodo>& ruta, std::vector<nodo>& novalen){
        
        if((enemy.x==0 && enemy.z==0) || (player.x==0 && player.z==0))
            return {0,0,0,0};
        nodo next = enemy;
        bool final = true;
        bool entra = true;
        bool novale = true;
        float dist=10000.0f;
        if(next.x == player.x && next.z == player.z){
            final=false;
            ruta.push_back(next);
        }
        else if(next.x == 0 && next.z==0){
            final=false;
        }
        else if(player.x == 0 && player.z==0){
            final=false;
        }
        while(final){
            
            for(int i=0; i<next.nodos.size() && final; i++){
                
                for(int j=0; j<novalen.size();j++){
                    if(next.nodos.at(i).x == novalen.at(j).x && next.nodos.at(i).z == novalen.at(j).z){
                        novale=false;
                    }
                }
                if(novale){
                    entra = false;
                    if(next.nodos.at(i).x == player.x && next.nodos.at(i).z == player.z){
                        next = next.nodos.at(i);
                        final = false;
                    }
                    float dist2 = sqrt((next.nodos.at(i).x - player.x) * (next.nodos.at(i).x - player.x) + (next.nodos.at(i).z - player.z) * (next.nodos.at(i).z - player.z));
                    if(dist2 < dist){
                        
                        dist = dist2;
                        next = next.nodos.at(i);
                    }
                }
            }
            if(entra){
                ruta.pop_back();
                novalen.push_back(next);
                next = enemy;
            }
            else{
                ruta.push_back(next);
                if(next.x == player.x && next.z == player.z){
                    final=false;
                }
                else{
                    findRute(next, player, ruta, novalen);
                    final=false;
                }
            }
        }
        return ruta.at(0);
    }

    void createNodes(NodoCmp& n){

        n.nodos.push_back(createNode(31.27,   -144.49,    22.91,  20.83));
        n.nodos.push_back(createNode(57.66,   -144.49,    3.47,   20.83));
        n.nodos.push_back(createNode(66,      -144.49,    4.86,   20.83));
        n.nodos.push_back(createNode(66,      -88.2,      4.79,   34.73));
        n.nodos.push_back(createNode(57.66,   -88.2,      3.47,   34.73));

        n.nodos.push_back(createNode(34.97,   -88.2,      19.22,  34.73));
        n.nodos.push_back(createNode(12.28,   -88.2,      3.47,   34.73));
        n.nodos.push_back(createNode(-9,      -108.04,    3.54,   15.61));
        n.nodos.push_back(createNode(-9,      -88.96,     3.54,   3.47));
        n.nodos.push_back(createNode(-9,      -69.84,     3.54,   15.64));

        n.nodos.push_back(createNode(-17.68,  -108.04,    5.14,   15.61));
        n.nodos.push_back(createNode(-17.68,  -88.95,     5.14,   3.47));
        n.nodos.push_back(createNode(-17.68,  -69.83,     5.14,   15.6));
        n.nodos.push_back(createNode(-17.68,  -48.98,     5.14,   5.21));
        n.nodos.push_back(createNode(-1.91,   -48.98,     10.71,  5.21));

        n.nodos.push_back(createNode(12.28,   -48.98,     3.47,   5.21));
        n.nodos.push_back(createNode(28.64,   -48.98,     12.89,  5.21));
        n.nodos.push_back(createNode(45.18,   -48.98,     3.64,   5.21));
        n.nodos.push_back(createNode(53.33,   -48.98,     4.08,   5.21));
        n.nodos.push_back(createNode(53.33,   -9.04,      4.08,   34.73));

        n.nodos.push_back(createNode(45.18,   -9.04,      3.64,   34.73));
        n.nodos.push_back(createNode(14.53,   -28.14,     27,     15.64));
        n.nodos.push_back(createNode(14.53,   -28.14,     27,     3.47));
        n.nodos.push_back(createNode(14.53,   10.06,      27,     15.62));
        n.nodos.push_back(createNode(-17.68,  -28.14,     5.2,    15.65));

        n.nodos.push_back(createNode(-17.68,  -28.14,     5.2,    3.47));
        n.nodos.push_back(createNode(-36.79,  -35.13,     13.88,  8.64));
        n.nodos.push_back(createNode(-36.79,  -12.72,     13.88,  13.72));
        n.nodos.push_back(createNode(-36.79,  13.33,      13.88,  12.32));
        n.nodos.push_back(createNode(-17.68,  37.02,      5.21,   42.58));

        n.nodos.push_back(createNode(-54.06,  67.66,      31.25,  11.94));
        n.nodos.push_back(createNode(-54.06,  83.08,      31.25,  3.47));
        n.nodos.push_back(createNode(-74.94,  107.81,     10.37,  3.47));
        n.nodos.push_back(createNode(-74.94,  116.49,     10.37,  5.21));
        n.nodos.push_back(createNode(-61.1,   98.92,      3.47,   12.37));

        n.nodos.push_back(createNode(-61.1,   116.49,     3.47,   5.21));
        n.nodos.push_back(createNode(-43.69,  98.92,      12.37,  20.84));
        n.nodos.push_back(createNode(-40.21,  116.49,     17.41,  5.21));
        n.nodos.push_back(createNode(-17.64,  83.08,      5.16,   3.47));
        n.nodos.push_back(createNode(-17.64,  98.92,      5.16,   12.37));

        n.nodos.push_back(createNode(-17.64,  116.49,     5.16,   5.21));
        n.nodos.push_back(createNode(-17.64,  146.01,     5.16,   24.31));
        nodosContinuos(&n.nodos);
    }

    void nodosContinuos(std::vector<nodo>* nodos){

        nodos->at(0).nodos.push_back(nodos->at(1));

        nodos->at(1).nodos.push_back(nodos->at(0));
        nodos->at(1).nodos.push_back(nodos->at(2));
        nodos->at(1).nodos.push_back(nodos->at(4));

        nodos->at(2).nodos.push_back(nodos->at(1));

        nodos->at(3).nodos.push_back(nodos->at(4));

        nodos->at(4).nodos.push_back(nodos->at(1));
        nodos->at(4).nodos.push_back(nodos->at(3));
        nodos->at(4).nodos.push_back(nodos->at(5));

        nodos->at(5).nodos.push_back(nodos->at(4));
        nodos->at(5).nodos.push_back(nodos->at(6));

        nodos->at(6).nodos.push_back(nodos->at(5));
        nodos->at(6).nodos.push_back(nodos->at(7));
        nodos->at(6).nodos.push_back(nodos->at(8));
        nodos->at(6).nodos.push_back(nodos->at(9));
        nodos->at(6).nodos.push_back(nodos->at(15));

        nodos->at(7).nodos.push_back(nodos->at(6));
        nodos->at(7).nodos.push_back(nodos->at(8));

        nodos->at(8).nodos.push_back(nodos->at(6));
        nodos->at(8).nodos.push_back(nodos->at(7));
        nodos->at(8).nodos.push_back(nodos->at(9));
        nodos->at(8).nodos.push_back(nodos->at(11));

        nodos->at(9).nodos.push_back(nodos->at(6));
        nodos->at(9).nodos.push_back(nodos->at(8));

        nodos->at(10).nodos.push_back(nodos->at(11));

        nodos->at(11).nodos.push_back(nodos->at(8));
        nodos->at(11).nodos.push_back(nodos->at(10));
        nodos->at(11).nodos.push_back(nodos->at(12));

        nodos->at(12).nodos.push_back(nodos->at(11));
        nodos->at(12).nodos.push_back(nodos->at(13));

        nodos->at(13).nodos.push_back(nodos->at(12));
        nodos->at(13).nodos.push_back(nodos->at(14));
        nodos->at(13).nodos.push_back(nodos->at(24));

        nodos->at(14).nodos.push_back(nodos->at(13));
        nodos->at(14).nodos.push_back(nodos->at(15));

        nodos->at(15).nodos.push_back(nodos->at(6));
        nodos->at(15).nodos.push_back(nodos->at(14));
        nodos->at(15).nodos.push_back(nodos->at(16));

        nodos->at(16).nodos.push_back(nodos->at(15));
        nodos->at(16).nodos.push_back(nodos->at(17));

        nodos->at(17).nodos.push_back(nodos->at(16));
        nodos->at(17).nodos.push_back(nodos->at(18));
        nodos->at(17).nodos.push_back(nodos->at(20));

        nodos->at(18).nodos.push_back(nodos->at(17));

        nodos->at(19).nodos.push_back(nodos->at(20));

        nodos->at(20).nodos.push_back(nodos->at(17));
        nodos->at(20).nodos.push_back(nodos->at(19));
        nodos->at(20).nodos.push_back(nodos->at(21));
        nodos->at(20).nodos.push_back(nodos->at(22));
        nodos->at(20).nodos.push_back(nodos->at(23));

        nodos->at(21).nodos.push_back(nodos->at(20));
        nodos->at(21).nodos.push_back(nodos->at(22));

        nodos->at(22).nodos.push_back(nodos->at(20));
        nodos->at(22).nodos.push_back(nodos->at(21));
        nodos->at(22).nodos.push_back(nodos->at(23));
        nodos->at(22).nodos.push_back(nodos->at(25));

        nodos->at(23).nodos.push_back(nodos->at(20));
        nodos->at(23).nodos.push_back(nodos->at(22));

        nodos->at(24).nodos.push_back(nodos->at(13));
        nodos->at(24).nodos.push_back(nodos->at(25));
        nodos->at(24).nodos.push_back(nodos->at(27));

        nodos->at(25).nodos.push_back(nodos->at(22));
        nodos->at(25).nodos.push_back(nodos->at(24));
        nodos->at(25).nodos.push_back(nodos->at(27));
        nodos->at(25).nodos.push_back(nodos->at(29));

        nodos->at(26).nodos.push_back(nodos->at(27));

        nodos->at(27).nodos.push_back(nodos->at(24));
        nodos->at(27).nodos.push_back(nodos->at(25));
        nodos->at(27).nodos.push_back(nodos->at(26));
        nodos->at(27).nodos.push_back(nodos->at(28));

        nodos->at(28).nodos.push_back(nodos->at(27));

        nodos->at(29).nodos.push_back(nodos->at(25));
        nodos->at(29).nodos.push_back(nodos->at(38));

        nodos->at(30).nodos.push_back(nodos->at(31));

        nodos->at(31).nodos.push_back(nodos->at(30));
        nodos->at(31).nodos.push_back(nodos->at(32));
        nodos->at(31).nodos.push_back(nodos->at(34));
        nodos->at(31).nodos.push_back(nodos->at(36));
        nodos->at(31).nodos.push_back(nodos->at(38));

        nodos->at(32).nodos.push_back(nodos->at(31));
        nodos->at(32).nodos.push_back(nodos->at(34));

        nodos->at(33).nodos.push_back(nodos->at(35));

        nodos->at(34).nodos.push_back(nodos->at(31));
        nodos->at(34).nodos.push_back(nodos->at(32));
        nodos->at(34).nodos.push_back(nodos->at(35));
        nodos->at(34).nodos.push_back(nodos->at(36));

        nodos->at(35).nodos.push_back(nodos->at(33));
        nodos->at(35).nodos.push_back(nodos->at(34));
        nodos->at(35).nodos.push_back(nodos->at(37));

        nodos->at(36).nodos.push_back(nodos->at(31));
        nodos->at(36).nodos.push_back(nodos->at(34));

        nodos->at(37).nodos.push_back(nodos->at(35));
        nodos->at(37).nodos.push_back(nodos->at(40));

        nodos->at(38).nodos.push_back(nodos->at(29));
        nodos->at(38).nodos.push_back(nodos->at(31));
        nodos->at(38).nodos.push_back(nodos->at(39));

        nodos->at(39).nodos.push_back(nodos->at(38));
        nodos->at(38).nodos.push_back(nodos->at(40));

        nodos->at(40).nodos.push_back(nodos->at(39));
        nodos->at(40).nodos.push_back(nodos->at(37));
        nodos->at(40).nodos.push_back(nodos->at(41));

        nodos->at(41).nodos.push_back(nodos->at(40));
    }
};