#pragma once
#include <cstdint>

struct InventarioCmp {
    int equipada = 0;
    //1 =  desbloqueada, 0 = no, 2 = arma actual
    size_t inventary [3] = {2, 1, 1}; //0 = pistola, 1 = escopeta, 2 = ametralladora
    //size_t keys_inv  [1] = {0}; //Inventario para las llaves
    
    //weapon1
    int ammo1           = 100;
    int Maxmagazine1    = 5;
    int magazine1       = 5;
    double reloadTime1  {0.8};
    double clockReload1 {0};
    double retroceso1   {-10.0};
    //double cadenceWeapon1{1}; // 1 vez por segundo
    

    //weapon2
    int ammo2           = 20;
    int Maxmagazine2    = 2;
    int magazine2       = 2;
    double reloadTime2  {1.5};
    double clockReload2 {0};
    double retroceso2   {-30.0};
    //double cadenceWeapon2 {0.2}; //5 veces por segundo

    //weapon3
    int ammo3              = 200;
    int Maxmagazine3       = 25;
    int magazine3          = 25;
    double cadenceWeapon3 {0.05}; 
    double reloadTime3    {1.1};
    double clockReload3   {0};
    double retroceso3     {-4.1};
    

    size_t reloading = 0; //0 not reloading 1 reloading
    double clockCadence{};
    double clockReload {};
    

    static constexpr uint8_t id {5}; //0000100000
};