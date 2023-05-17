#pragma once
#include "gameman.hpp"
#include "../sys/soundsystem.hpp"
#include "../sys/aisys.hpp"
#include "../sys/rensys2.hpp"
#include "../sys/physys2.hpp"
#include "../sys/colsys2.hpp"
#include "../sys/inpsys2.hpp"
#include "../sys/nodemapsys.hpp"
#include "../sys/logicsystem.hpp"
#include "../sys/selfdestsys.hpp"
#include "../sys/spawnsys.hpp"
#include "../sys/rensys2.hpp"
#include "../sys/UIsys.hpp"
#include "../eng/engine2.hpp"
#include <GLFW/glfw3.h>
#include "animationman.hpp"
#include <chrono>
#include <cstddef>
#include <iostream>
#include "../sys/partsys.hpp"

void GameMan::game() {
    LevelMan      LM;
    RenSys2       RenSys;
    InpSys2       InpSys;
    SoundSystem_t SouSys;
    UIsys         UISys;
    GraphicEngine GE;
    
    //GE.glEng.setResolution(1920, 1080);
    
    RenSys.initIMGUI(GE);
    init_config(GE);
    UISys.iniText();
    
    size_t player_ID = LM.createPlayer2(GE, Vec3{-35, 3.5, -5}, SouSys);
    size_t menu = 0; //0 Ini 1 game 2 dead 3 pause 4 controls 5 sound
    
    auto window = GE.getWindow();

    while(!glfwWindowShouldClose(window) && menu == 0) {

        switch (menu) {

            case 0:{
                menu = bucleInicio(RenSys, GE, UISys);
                //std::cout<<"menu = " << menu<<"\n";
            }

            case 1:{
                while(!glfwWindowShouldClose(window) && menu == 1){
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                    UISys.inGame = 1;
                    menu = bucleJuego(LM, GE, RenSys, InpSys, SouSys, menu, player_ID, UISys) ;
                    UISys.inGame = 0;
                }
            }

            case 4:{
                while(!glfwWindowShouldClose(window) && menu == 4){
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    menu = bucleControles( GE, RenSys, UISys);
                }
            }

            case 5:{
                while(!glfwWindowShouldClose(window) && menu == 5){
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    menu = bucleSonido( GE, RenSys, UISys) ;
                }
            }

            

        }

        while(!glfwWindowShouldClose(window) && menu == 2){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            menu = bucleDead(GE, RenSys, UISys);
        }
        
    }
    RenSys.EndImgui(GE);
}

size_t GameMan::bucleInicio(RenSys2& RenSys, GraphicEngine& GE, UIsys& UISys){
    size_t abandon{0};

    while(abandon == 0 && !glfwWindowShouldClose(GE.getWindow())) {
        abandon = RenSys.updateMenuInicio(GE, UISys);
    }
    return abandon;
}


size_t GameMan::bucleJuego(LevelMan &LM, GraphicEngine &GE, RenSys2 &RenSys, InpSys2 &InpSys, SoundSystem_t& SouSys, size_t abandon, std::size_t player_ID, UIsys &UISys){
    EntyMan&      EM = LM.getEM();
    ColSys2       ColSys;
    PhySys2       PhySys; 
    AISys         AISys;
    NodeMapSys    MapSys;
    LogicSystem   LogSys;
    SpawnSystem   SpawnSys;
    SelfDestSys   DstSys;
    PartSys       PartSys;
    AnimMan AM(GE.glEng);

    bool dead { false }, pause { false };
    size_t actualMenu {abandon};
    
    std::size_t map_ID = LM.createMap2(GE, SouSys);
    ColSys.init_Hitoxes_Map2(LM);
    LM.createWeapon2(GE, Vec3 {-42, 2.8, -15}, W_Type::Fusil, SouSys);

    //ge.glEng.useFirstUnusedPFoco(0.f, -20.f, 5.f, 10.f, "White_light", 1);
    //for (int i =0; i<6; i++) {
    //    ge.glEng.setActiveFoco(i, true);
    //}

    constexpr double dt = 1.0 / 60;

    while(abandon == 1 && !glfwWindowShouldClose(GE.getWindow()) ) {
        
        switch (actualMenu) {
            
            case 3: 
                actualMenu = RenSys.updateMenuPausa( GE, UISys);
                if(actualMenu == 0){
                    abandon = actualMenu;
                }

            case 4:
                actualMenu = bucleControles( GE, RenSys, UISys);

            case 5:
                actualMenu = bucleSonido(GE,RenSys, UISys);

            default:
                EM.update();
                RenSys.update2(EM, GE, player_ID, UISys, dt);
                MapSys.update2(EM, player_ID, map_ID);
                InpSys.update2(LM, GE, SouSys, dt, UISys);
                AISys. update2(LM, GE, dt);
                PhySys.update (EM, dt);
                ColSys.update (EM);
                LogSys.update2(LM, GE, dt, UISys, dead);
                PhySys.update_after_colision(EM, dt);
                SouSys.update (EM);
                DstSys.update (EM, dt);
        
        }
        //ge.glEng.drawFocos();
    }
    LM.resetLevel();
    
    abandon = 0;

    return abandon;
}

size_t GameMan::bucleDead(GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys){
    size_t abandon { 2 };
        
    while(abandon == 2 && !glfwWindowShouldClose(GE.getWindow())) {
        //menu = RenSys.updateMenuDead(GE, UISys, menu);
        abandon = RenSys.updateMenuPausa(GE, UISys);
    }

    return abandon;
}

size_t GameMan::bucleControles(GraphicEngine &GE ,RenSys2 &RenSys, UIsys &UISys){
    size_t abandon { 4 };
        
    while(abandon == 4 && !glfwWindowShouldClose(GE.getWindow())) {
        //menu = RenSys.updateMenuDead(GE, UISys, menu);
        abandon = RenSys.updateMenuControles(GE, UISys);
    }

    return abandon;
}

size_t GameMan::bucleSonido(GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys){
    size_t abandon { 5 };
        
    while(abandon == 5 && !glfwWindowShouldClose(GE.getWindow())) {
        //menu = RenSys.updateMenuDead(GE, UISys, menu);
        abandon = RenSys.updateMenuSonido(GE, UISys);
    }

    return abandon;
}

void GameMan::init_config(GraphicEngine& GE) {
    srand(time(NULL));
}

size_t GameMan::init_map(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys) {
    ColSys2::init_Hitoxes_Map2(LM);

    // SPAWN ENEMIGOS
    LM.createEneSpawn(Vec3{ -30,  0, -3  }, GE, 0);
    LM.createEneSpawn(Vec3{ -59,  0, -30 }, GE, 3);
    LM.createEneSpawn(Vec3{ -84,  0, -6  }, GE, 6);
    LM.createEneSpawn(Vec3{ -103, 0, -32 }, GE, 11);
    LM.createEneSpawn(Vec3{ -53,  0, -77 }, GE, 13);

    // SPAWN ARMAS
    LM.createWpnSpawn(Vec3 { -30,  2.8, -13 }, GE, 0);
    LM.createWpnSpawn(Vec3 { -58,  2.8, -31 }, GE, 3);
    LM.createWpnSpawn(Vec3 { -77,  2.8, 4   }, GE, 6);
    LM.createWpnSpawn(Vec3 { -100, 2.8, -35 }, GE, 11);
    LM.createWpnSpawn(Vec3 { -57,  2.8, -78 }, GE, 13);
    // LM.createWpnSpawn(Vec3 { -60,  2.8, 32  }, GE, X); Sala X (patio)

    return LM.createMap2(GE, SouSys);
}