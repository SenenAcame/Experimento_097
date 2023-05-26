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
    RenSys2        RenSys;
    InpSys2        InpSys;
    LevelMan       LM;
    SoundSystem_t& SouSys = LM.getSouSys();
    UIsys          UISys;
    GraphicEngine  GE;
    
    GE.setWindowResolution(1280, 720);
    
    RenSys.initIMGUI(GE);
    init_config(GE);
    UISys.iniText(GE);
    
    size_t player_ID = LM.createPlayer2(GE, Vec3{-35, 3.5, -5}, SouSys);
    LM.getEM().getBoard().entyID = player_ID;

    size_t playing = 0; //0 Ini 1 game 2 dead 3 pause 4 controls 5 sound
    size_t menu = 0; //0 Ini 1 game 2 dead 3 pause 4 controls 5 sound
    
    auto window = GE.getWindow();

    while(!GE.getCloseWindow() && playing == 0) {
        switch (menu) {
            case 0:{
                menu = bucleInicio(RenSys, GE, UISys);
                break;
            }

            case 1:{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                while(!GE.getCloseWindow() && menu == 1){
                    UISys.inGame = 1;
                    menu = bucleJuego(LM, GE, RenSys, InpSys, SouSys, menu, UISys) ;
                    UISys.inGame = 0;
                }
                break;
            }

            case 2:{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                while(!GE.getCloseWindow() && menu == 2){
                    menu = bucleDead(GE, RenSys, UISys);
                }
                break;
            }

            case 4:{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                while(!GE.getCloseWindow() && menu == 4){
                    menu = bucleControles( GE, RenSys, UISys);
                }
                break;
            }

            case 5:{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                while(!GE.getCloseWindow() && menu == 5){
                    menu = bucleSonido( GE, RenSys, UISys, SouSys) ;
                }
                break;
            }
        }
    }
    RenSys.EndImgui(GE);
}

size_t GameMan::bucleInicio(RenSys2& RenSys, GraphicEngine& GE, UIsys& UISys){
    size_t abandon { 0 };

    while(abandon == 0 && !GE.getCloseWindow()) {
        abandon = RenSys.updateMenuInicio(GE, UISys);
    }

    return abandon;
}


size_t GameMan::bucleJuego(LevelMan &LM, GraphicEngine &GE, RenSys2 &RenSys, InpSys2 &InpSys, SoundSystem_t& SouSys, size_t abandon, UIsys &UISys){
    EntyMan&    EM = LM.getEM();
    ColSys2     ColSys;
    PhySys2     PhySys; 
    AISys       AISys;
    NodeMapSys  MapSys;
    LogicSystem LogSys;
    SpawnSystem SpwSys;
    SelfDestSys DstSys;
    PartSys     PartSys;
    AnimMan     AM(GE,RenSys, UISys);

    bool dead { false };
    size_t actualMenu {abandon};
    soundsEffects(EM, SouSys);
    
    std::size_t map_ID = LM.createMap2(GE, SouSys);
    init_map(LM, GE, SouSys);

    //LM.createWeapon2(GE, Vec3{ -40, 2.8, -5 }, W_Type::Pistol,  SouSys);
    //LM.createWeapon2(GE, Vec3{ -40, 2.8, -5 }, W_Type::Shotgun, SouSys);
    //LM.createWeapon2(GE, Vec3{ -40, 2.8, -5 }, W_Type::Fusil,   SouSys);

    //LM.createNormalEnemy  (GE, Vec3{ -40, 2.8, -5 }, SouSys);
    //LM.createTankEnemy    (GE, Vec3{ -40, 3.2, -5 }, SouSys);
    //LM.createDistanceEnemy(GE, Vec3{ -40, 2.5, -5 }, SouSys);

    //LM.createNormalEnemyAnim  (GE, Vec3{ -40,   1, -5 }, SouSys);
    //LM.createTankEnemyAnim    (GE, Vec3{ -40, 1.6, -5 }, SouSys);
    //LM.createDistanceEnemyAnim(GE, Vec3{ -40, 2.5, -5 }, SouSys);

    constexpr double dt = 1.0 / 60;
    auto start = std::chrono::high_resolution_clock::now();
    constexpr int64_t maxFPS {60};
    constexpr int64_t nanos_per_frame {1000000000/maxFPS};
    int64_t frames = 0;

    while(abandon == 1 && !dead && !GE.getCloseWindow() ) {
        switch (actualMenu) {
            case 3: {
                glfwSetInputMode(GE.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                actualMenu = RenSys.updateMenuPausa( GE, UISys, EM, SouSys);
                UISys.pause =false;
                if(actualMenu == 0) {
                    abandon = actualMenu;
                }
                break;
            }
            case 4: {
                glfwSetInputMode(GE.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                actualMenu = bucleControles( GE, RenSys, UISys);
                break;
            }
            case 5: {
                glfwSetInputMode(GE.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                actualMenu = bucleSonido(GE,RenSys, UISys, SouSys);
                break;
            }
            default: {
                auto frame_start = std::chrono::high_resolution_clock::now();
                glfwSetInputMode(GE.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                EM.update();
                RenSys.update2(EM, GE, UISys, dt);
                MapSys.update3(EM, map_ID, dt);
                InpSys.update2(LM, GE, SouSys, dt, UISys);
                AISys. update2(LM, GE, dt);
                PhySys.update (EM, dt);
                ColSys.update (EM);
                LogSys.update2(LM, GE, dt, UISys, dead);
                PhySys.update_after_colision(EM, dt);
                SouSys.update (EM);
                SpwSys.update (LM, GE, SouSys, dt);
                DstSys.update (EM, dt);
                if(UISys.pause == true) actualMenu = 3;
                 while ((std::chrono::high_resolution_clock::now() - frame_start).count() < nanos_per_frame){
                    //std::cout<<"FRAME START: " << (std::chrono::high_resolution_clock::now() - frame_start).count() << "\n";
                    //std::cout<<"NANOS PER FRAME: " << nanos_per_frame <<"\n";
                }
                ++frames;
                break;
            }
        }
    }
    
    LM.resetLevel(EM.getBoard().entyID, GE, SouSys, UISys);
    
    if(dead) abandon = 2;
    else     abandon = 0;
    return abandon;
}

size_t GameMan::bucleDead(GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys){
    size_t abandon { 2 };
        
    while(abandon == 2 && !GE.getCloseWindow()) {
        abandon = RenSys.updateMenuDead(GE, UISys);
    }

    return abandon;
}

size_t GameMan::bucleControles(GraphicEngine &GE ,RenSys2 &RenSys, UIsys &UISys){
    size_t abandon { 4 };
        
    while(abandon == 4 && !GE.getCloseWindow()) {
        abandon = RenSys.updateMenuControles(GE, UISys);
    }

    return abandon;
}

size_t GameMan::bucleSonido(GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys, SoundSystem_t& Sou){
    size_t abandon { 5 };
    
    while(abandon == 5 && !GE.getCloseWindow()) {
        //menu = RenSys.updateMenuDead(GE, UISys, menu);
        abandon = RenSys.updateMenuSonido(GE, UISys, Sou);
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
    LM.createEneSpawn(Vec3{ -60,  0, 28  }, GE, 16);

    // SPAWN ARMAS
    LM.createWpnSpawn(Vec3 { -30,  2.8, -13 }, GE, 0);
    LM.createWpnSpawn(Vec3 { -58,  2.8, -31 }, GE, 3);
    LM.createWpnSpawn(Vec3 { -77,  2.8, 4   }, GE, 6);
    LM.createWpnSpawn(Vec3 { -100, 2.8, -35 }, GE, 11);
    LM.createWpnSpawn(Vec3 { -57,  2.8, -78 }, GE, 13);
    LM.createWpnSpawn(Vec3 { -60,  2.8, 40  }, GE, 16);

    return LM.createMap2(GE, SouSys);
}

void GameMan::soundsEffects(EntyMan& EM, SoundSystem_t& SouSys){
    /*auto& pulso=EM.createEntity();
    EM.addComponent<SoundCmp>      (pulso, SoundCmp{.programmerSoundContext = SouSys.createinstance(3)});
    EM.addTag      <TPulso>        (pulso);*/

    /*auto& pasos=EM.createEntity();
    EM.addComponent<SoundCmp>      (pasos, SouSys.createinstance(4));
    EM.addTag      <TPasos>        (pasos);*/

    auto& ronda=EM.createEntity();
    EM.addComponent<SoundCmp>      (ronda, SouSys.createinstance(8));
    EM.addTag      <TRonda>        (ronda);
}