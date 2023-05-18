#pragma once
#include <cstdint>

enum class SB{
    //Arrive,
    //Seek,
    Shoot,
    Patrol,
    Persue,
    Two_Steps,
    Diying
};
struct nodomap;

struct AICmp {
    double rad   { 1.0 },     ang { 0 };
    double flock_x { 0 }, flock_z { 0 };
    double      ox { 0 },      oz { 0 };
    double arrivalRadius { 1.0 };
    double timeArrive    { 0.5 };
    double cooldown      { 0.1 };
    double time          { 0.0 };
    bool   enable        { true };
    bool   shoot         { false };
    std::vector<nodomap> ruta {};
    double cooldown_ruta {3.0};
    /*double random        {static_cast<double>((rand()%15)/10)};
    int    xrand         {rand()%1};
    int    zrand         {rand()%1};*/
    SB     behaviour     { SB::Two_Steps };

    std::size_t entyID { 0 };

    static constexpr uint8_t id { 4 }; //0000010000
};