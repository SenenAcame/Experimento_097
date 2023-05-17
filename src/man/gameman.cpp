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

//#include <imgui/src/imgui.h>
//#include <imgui/src/imgui_impl_glfw.h>
//#include <imgui/src/imgui_impl_opengl3.h>



void GameMan::game() {
    LevelMan      LM;
    RenSys2       RenSys;
    InpSys2       InpSys;
    SoundSystem_t SouSys;
    SpawnSystem   SpwSys;
    SelfDestSys   DstSys;
    UIsys         UISys;
    //TheEngine     dev {1280, 720, &InpSys};
    GraphicEngine GE;
    PartSys       PartSys;
    AnimMan AM(GE.glEng);

    //GE.glEng.setResolution(1920, 1080);

    RenSys.initIMGUI(GE);
    init_config(GE);
    
    size_t map_ID = init_map(LM, GE, SouSys);
    size_t player_ID = LM.createPlayer2(GE, Vec3{-35, 3.5, -5}, SouSys);

    bool abandon {false};
    std::size_t player_ID = LM.createPlayer2(GE, Vec3{-35, 3.5, -5}, SouSys);
    auto window = GE.getWindow();

    while(!glfwWindowShouldClose(window)){

        bucleInicio(RenSys, GE, UISys);

        while(!glfwWindowShouldClose(window) && !abandon){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            abandon = bucleJuego(LM, GE, RenSys, InpSys, SouSys, abandon, player_ID, UISys) ;
            
        }
        abandon = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if(!abandon) abandon = bucleDead(LM, GE, RenSys, UISys);
        abandon = false;
    }
    RenSys.EndImgui(GE);

    
}

void GameMan::bucleInicio(RenSys2& RenSys, GraphicEngine& GE, UIsys& UISys){
    bool menu{true};

    while(menu && !glfwWindowShouldClose(GE.getWindow())) {
        menu = RenSys.updateMenuInicio(GE, UISys, menu);
        
    }
    
}

bool GameMan::bucleJuego(LevelMan &LM, GraphicEngine &GE, RenSys2 &RenSys, InpSys2 &InpSys, SoundSystem_t& SouSys, bool abandon, std::size_t player_ID, UIsys &UISys){
    
    EntyMan&      EM = LM.getEM();
    ColSys2       ColSys;
    PhySys2       PhySys; 
    AISys         AISys;
    NodeMapSys    MapSys;
    LogicSystem   LogSys;

    //SpawnSystem   SpawnSys;
    SelfDestSys   DstSys;
    //RenSys.initIMGUI(GE);

    bool dead { false }, pause { false };

    //ImGui::CreateContext();
    //ImGui_ImplGlfw_InitForOpenGL(GE.getWindow(), true);

    //ImGui::Begin("Hello, world!");
    //ImGui::Text("This is some useful text."); 

    
    std::size_t map_ID    = LM.createMap2(GE, SouSys);
    ColSys.init_Hitoxes_Map2(LM);
    LM.createWeapon2(GE, Vec3 {-42, 2.8, -15}, W_Type::Fusil, SouSys);
    //LM.createNormalEnemy(GE, Vec3{-42, 2.8, -15}, SouSys);
    
    //ge.glEng.useFirstUnusedPFoco(0.f, -20.f, 5.f, 10.f, "White_light", 1);
    //for (int i =0; i<6; i++) {
    //    ge.glEng.setActiveFoco(i, true);
    //}

    constexpr double dt = 1.0 / 60;

    while(!dead && !abandon && !glfwWindowShouldClose(GE.getWindow()) ) {
        
        if(pause) {
            pause = RenSys.updateMenuPausa( GE, UISys, abandon);
            abandon = pause;
        }
        else{

            EM.update();
            //ImGui::Text("This is some useful text.");
            RenSys.update2(EM, GE, player_ID, UISys, dt);
            //MapSys.update(EM, player_ID, map_ID);
            InpSys.update2(LM, GE, SouSys, dt, UISys);
            AISys. update2(EM, dt);
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
    abandon = true;
    return abandon;
    //RenSys.EndImgui(GE);
//    init_config(dev);
//    init_map(LM, dev, SouSys);
//    LM.createEmptyInterface(dev);
//
//    while(dev.run()) {
//        auto player = LM.init_level(dev, SouSys);
//        size_t player_ID = player.getID();
//        bool dead { false };
//
//        //actual moment ini
//        constexpr double dt = 1.0/60;
//        auto start = std::chrono::high_resolution_clock::now();
//        constexpr int64_t maxFPS {60};
//        constexpr int64_t nanos_per_frame {1000000000/maxFPS};
//        int64_t frames = 0;
//        
//        while(!dead && dev.run()){
//            auto frame_start = std::chrono::high_resolution_clock::now();
//   ->       EM.      update();
//   ->       RenSys.  update(EM, dev);
//   ->       MapSys.  update(EM);
//   ->       InpSys.  update(LM, dev, SouSys, dt);
//   ->       AISys.   update(EM, dt, dev);
//   ->       PhySys.  update(EM, dt);
//   ->       ColSys.  update(EM);
//   ->       LogicSys.update(LM, dev, dt);
//   ->       PhySys.  update_after_colision(EM, dt);
//            SouSys.  update(EM);
//            //SpawnSys.update(EM, dev, SouSys, player, map);
//            //LM.      update(dev, SouSys, dt);
//            LM.      update(dev, SouSys, dt, player);
//   ->       DestSys. update(EM, dt);
//
//            dead = EM.getEntityById(player_ID).getDestroy();
//
//            while ((std::chrono::high_resolution_clock::now() - frame_start).count() < nanos_per_frame){}
//            ++frames;
//        }
//        LM.resetLevel(dev);
//
//        auto end = std::chrono::high_resolution_clock::now();
//        auto ellapse =  (end - start).count(); //how many nano sec has pass
//        auto ellapseS =  double(ellapse)/1000000000.; //how many sec has pass
//        std::cout <<" TIMEPO (s): " << ellapseS << "\n";
//        std::cout <<" Frames " << frames<< "\n";
//        std::cout <<" FPS " << double(frames)/ellapseS << "\n";
//    }
//    //RenSys.EndImgui();
}

bool GameMan::bucleDead(LevelMan& LM, GraphicEngine& GE, RenSys2& RenSys, UIsys& UISys){

    EntyMan&  EM = LM.getEM();
    bool menu { true };
        
    while(menu && !glfwWindowShouldClose(GE.getWindow())) {
        //menu = RenSys.updateMenuDead(GE, UISys, menu);
        menu = RenSys.updateMenuPausa(GE, UISys, menu);
    }

    return menu;

}

void GameMan::init_config(GraphicEngine& GE) {
    srand(time(NULL));
    //dev.getDevice()->getCursorControl()->setVisible(false);
    //dev.SetFont("assets/Interface/Font/chill.xml");
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