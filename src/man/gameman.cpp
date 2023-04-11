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
#include <chrono>
#include <cstddef>
#include <iostream>
#include "../eng/engine2.hpp"

void GameMan::game() {
    LevelMan      LM;
    EntyMan&      EM = LM.getEM();
    PhySys2       PhySys;
    RenSys2       RenSys;
    ColSys2       ColSys;
    InpSys2       InpSys;
    AISys         AISys;
    NodeMapSys    MapSys;
    LogicSystem   LogicSys;
    SoundSystem_t SouSys;
    //SpawnSystem   SpawnSys;
    SelfDestSys   DestSys;
    //TheEngine     dev {1280, 720, &InpSys};
    GraphicEngine ge;

    Enty& player = EM.createEntity();
    EM.addComponent<PhysicsCmp2>   (player, PhysicsCmp2{});
    EM.addComponent<RenderCmp2>    (player, 
        RenderCmp2{ .node=ge.glEng.createModel(
            nullptr,
            Vec3{0,0,0},
            Vec3{0,0,0},
            Vec3{0,0,0},
            "assets/models/personajes/monstruo2.obj"
        )}
    );
    

    while(!glfwWindowShouldClose(ge.glEng.getWindow())) {

        RenSys.drawWorld(ge);
    }
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
//            EM.      update();
//            RenSys.  update(EM, dev);
//            MapSys.  update(EM);
//            InpSys.  update(LM, dev, SouSys, dt);
//            AISys.   update(EM, dt, dev);
//            PhySys.  update(EM, dt);
//            ColSys.  update(EM);
//            LogicSys.update(LM, dev, dt);
//            PhySys.  update_after_colision(EM, dt);
//            SouSys.  update(EM);
//            //SpawnSys.update(EM, dev, SouSys, player, map);
//            //LM.      update(dev, SouSys, dt);
//            LM.      update(dev, SouSys, dt, player);
//            DestSys. update(EM, dt);
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

void GameMan::init_config(TheEngine& dev) {
    srand(time(NULL));
    dev.getDevice()->getCursorControl()->setVisible(false);
    dev.SetFont("assets/Interface/Font/chill.xml");
}

void GameMan::init_map(LevelMan& LM, TheEngine& dev, SoundSystem_t& SouSys) {
    LM.createMap(dev, SouSys);
    ColSys2::init_Hitoxes_Map2(LM, dev);
}