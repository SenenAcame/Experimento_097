#pragma once
#include <cstdint>

struct puerta {
    float x {}, z {};
};

struct punto {
    float x {}, z {};
};

struct nodomap {
    int num={-1};
    punto coord;
    std::vector<nodomap> nodos_adya;
    float total={0};
    float estimado={0};
    nodomap* padre={nullptr};
    nodomap(){
        this->num=-1;
        this->coord={0,0};
    }
    nodomap(const int& n, const punto& coorde){
        this->num=n;
        this->coord=coorde;
    }
    void putnodo(const std::vector<nodomap> adya){
        for(int i=0; i<adya.size();i++){
            this->nodos_adya.push_back(adya.at(i));
        }
    }
    nodomap& operator=(const nodomap& n){
        this->num=n.num;
        this->coord=n.coord;
        this->nodos_adya.clear();
        for(int i=0; i<n.nodos_adya.size();i++){
            this->nodos_adya.push_back(n.nodos_adya.at(i));
        }
        this->padre=n.padre;
        return *this;
    }
};

struct sala {
    float  x {}, z {};
    float  tamx {}, tamz {};
    std::vector<puerta> puertas;
    std::size_t open { 0 }; //0 = is close sala 1 = open sala
};

struct NodoCmp {
    std::vector<sala> salas;
    std::vector<nodomap> nodos;

    static constexpr uint8_t id { 8 };
};