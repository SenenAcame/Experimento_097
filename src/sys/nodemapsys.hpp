#pragma once
#include <iostream>
#include <vector>
#include "../util/types.hpp"

struct NodeMapSys {

    nodo createNode(float posx, float posz, float tamax, float tamaz){
        nodo nodo{posx, posz, tamax, tamaz};
        return nodo;
    }

    nodo findNodeEne(posene){

    };

    nodo findNodePlayer(posplayer){
        
    };

    std::vector<nodo> findRute(entity){

    };

    std::vector<nodo> createNodes(){
        std::vector<nodo> nodos;

        nodos.push_back(createNode(31.27,   -144.49,    22.91,  20.83));
        nodos.push_back(createNode(57.66,   -144.49,    3.47,   20.83));
        nodos.push_back(createNode(66,      -144.49,    4.86,   20.83));
        nodos.push_back(createNode(66,      -88.2,      4.79,   34.73));
        nodos.push_back(createNode(57.66,   -88.2,      3.47,   34.73));

        nodos.push_back(createNode(34.97,   -88.2,      19.22,  34.73));
        nodos.push_back(createNode(12.28,   -88.2,      3.47,   34.73));
        nodos.push_back(createNode(-9,      -108.04,    3.54,   15.61));
        nodos.push_back(createNode(-9,      -88.96,     3.54,   3.47));
        nodos.push_back(createNode(-9,      -69.84,     3.54,   15.64));

        nodos.push_back(createNode(-17.68,  -108.04,    5.14,   15.61));
        nodos.push_back(createNode(-17.68,  -88.95,     5.14,   3.47));
        nodos.push_back(createNode(-17.68,  -69.83,     5.14,   15.6));
        nodos.push_back(createNode(-17.68,  -48.98,     5.14,   5.21));
        nodos.push_back(createNode(-1.91,   -48.98,     10.71,  5.21));

        nodos.push_back(createNode(12.28,   -48.98,     3.47,   5.21));
        nodos.push_back(createNode(28.64,   -48.98,     12.89,  5.21));
        nodos.push_back(createNode(45.18,   -48.98,     3.64,   5.21));
        nodos.push_back(createNode(53.33,   -48.98,     4.08,   5.21));
        nodos.push_back(createNode(53.33,   -9.04,      4.08,   34.73));

        nodos.push_back(createNode(45.18,   -9.04,      3.64,   34.73));
        nodos.push_back(createNode(14.53,   -28.14,     27,     15.64));
        nodos.push_back(createNode(14.53,   -28.14,     27,     3.47));
        nodos.push_back(createNode(14.53,   10.06,      27,     15.62));
        nodos.push_back(createNode(-17.68,  -28.14,     5.2,    15.65));

        nodos.push_back(createNode(-17.68,  -28.14,     5.2,    3.47));
        nodos.push_back(createNode(-36.79,  -35.13,     13.88,  8.64));
        nodos.push_back(createNode(-36.79,  -12.72,     13.88,  13.72));
        nodos.push_back(createNode(-36.79,  13.33,      13.88,  12.32));
        nodos.push_back(createNode(-17.68,  37.02,      5.21,   42.58));

        nodos.push_back(createNode(-54.06,  67.66,      31.25,  11.94));
        nodos.push_back(createNode(-54.06,  83.08,      31.25,  3.47));
        nodos.push_back(createNode(-74.94,  107.81,     10.37,  3.47));
        nodos.push_back(createNode(-74.94,  116.49,     10.37,  5.21));
        nodos.push_back(createNode(-61.1,   98.92,      3.47,   12.37));

        nodos.push_back(createNode(-61.1,   116.49,     3.47,   5.21));
        nodos.push_back(createNode(-43.69,  98.92,      12.37,  20.84));
        nodos.push_back(createNode(-40.21,  116.49,     17.41,  5.21));
        nodos.push_back(createNode(-17.64,  83.08,      5.16,   3.47));
        nodos.push_back(createNode(-17.64,  98.92,      5.16,   12.37));

        nodos.push_back(createNode(-17.64,  116.49,     5.16,   5.21));
        nodos.push_back(createNode(-17.64,  146.01,     5.16,   24.31));
        nodosContinuos(&nodos);

        return nodos;
    };

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