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
#include "../eng/engine2.hpp"
#include <chrono>
#include <cstddef>
#include <iostream>

//#include <imgui/src/imgui.h>
//#include <imgui/src/imgui_impl_glfw.h>
//#include <imgui/src/imgui_impl_opengl3.h>

void GameMan::game() {
    LevelMan      LM;
    EntyMan&      EM = LM.getEM();
    PhySys2       PhySys;
    RenSys2       RenSys;
    ColSys2       ColSys;
    InpSys2       InpSys;
    AISys         AISys;
    NodeMapSys    MapSys;
    LogicSystem   LogSys;
    SoundSystem_t SouSys;
    SpawnSystem   SpwSys;
    SelfDestSys   DstSys;
    //TheEngine     dev {1280, 720, &InpSys};
    GraphicEngine GE;
    //GE.glEng.setResolution(1920, 1080);

    RenSys.initIMGUI(GE);
    init_config(GE);
    //size_t map_ID = init_map(LM, GE, SouSys);

    //ImGui::CreateContext();
    //ImGui_ImplGlfw_InitForOpenGL(GE.getWindow(), true);

    //ImGui::Begin("Hello, world!");
    //ImGui::Text("This is some useful text."); 
    
    std::size_t player_ID = LM.createPlayer2(GE, Vec3{-35, 3.5, -5}, SouSys);
 
    LM.createSpawn2(Vec3{ -30, 0, -3  }, GE, 1);
    LM.createSpawn2(Vec3{ -84, 0, -6  }, GE, 2);
    LM.createSpawn2(Vec3{ -59, 0, -30 }, GE, 3);

    //LM.createEnemy(GE, Vec3{ -30, 2.5, -3  }, SouSys, Type_Enemy::Distance);

    LM.createWeapon2(GE, Vec3 { -30, 2.8, -13 }, W_Type::Pistol,  SouSys);
    LM.createWeapon2(GE, Vec3 { -77, 2.8, 4   }, W_Type::Shotgun, SouSys);
    LM.createWeapon2(GE, Vec3 { -58, 2.8, -31 }, W_Type::Fusil,   SouSys);
    
    //ge.glEng.useFirstUnusedPFoco(0.f, -20.f, 5.f, 10.f, "White_light", 1);
    //for (int i =0; i<6; i++) {
    //    ge.glEng.setActiveFoco(i, true);
    //}

    constexpr double dt = 1.0 / 60;

    while(!glfwWindowShouldClose(GE.getWindow())) {
        //ge.glEng.drawFocos();
        EM.update();
        RenSys.update2(EM, GE, player_ID);
        //MapSys.update(EM, player_ID, map_ID);
        InpSys.update2(LM, GE, SouSys, dt);
        AISys. update2(LM, GE, dt);
        PhySys.update (EM, dt);
        ColSys.update (EM);
        LogSys.update2(LM, GE, dt);
        PhySys.update_after_colision(EM, dt);
        SouSys.update (EM);
        SpwSys.update (LM, GE, SouSys, player_ID, 0, dt);
        DstSys.update (EM, dt);
    }
    RenSys.EndImgui(GE);
//    init_config(dev);
//    init_map(LM, dev, SouSys);
//    LM.createEmptyInterface(dev);
//
//    while(dev.run()) {
//        auto player = LM.init_level(dev, SouSys);
//        std::size_t player_ID = player.getID();
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

void GameMan::init_config(GraphicEngine& GE) {
    srand(time(NULL));
    //dev.getDevice()->getCursorControl()->setVisible(false);
    //dev.SetFont("assets/Interface/Font/chill.xml");
}

size_t GameMan::init_map(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys) {
    ColSys2::init_Hitoxes_Map2(LM);
    return LM.createMap2(GE, SouSys);
}