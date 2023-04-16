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
#include <iostream>

void GameMan::game() {
    InpSys2   InpSys;
    TheEngine dev {1080, 720, &InpSys};
    RenSys2   RenSys;
    LevelMan  LM;
    EntyMan&  EM = LM.getEM();

    PhySys2       PhySys;
    ColSys2       ColSys;
    AISys         AISys;
    NodeMapSys    MapSys;
    LogicSystem   LogicSys;
    SoundSystem_t SouSys;
    //SpawnSystem   SpawnSys;
    SelfDestSys   DestSys;

//////////////////////////////////////////////////////////////
//  Menu inicial

    dev.addImageToPositionInScreen("assets/pantalla_controles_2.png", dev.getWidth()/2, dev.getHeight()/2);

    while(dev.run()) {
        bool dead { false };

        while(!dead && dev.run()) {
            RenSys.update(EM, dev);
//            InpSys.update_menu();
        }
    }
    
/////////////////////////////////////////////////////////////
// Bucle principal del juego

//    init_config(dev);
//    init_map(LM, dev, SouSys);
//    LM.createEmptyInterface(dev);
//    
//    while(dev.run()) {
//        auto& player = LM.init_level(dev, SouSys);
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
//            //SouSys.  update(EM);
//            //SpawnSys.update(EM, dev, SouSys, player, map);
//            //LM.      update(dev, SouSys, dt);
//            LM.      update(dev, SouSys, dt, player_ID);
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

//void GameMan::initial_menu(TheEngine& dev) {
//    dev.addImageToPositionInScreen("assets/pantalla_controles_2.png", dev.getWidth()/2, dev.getHeight()/2);
//
//    while(dev.run()) {
//        bool dead { false };
//
//        while(!dead && dev.run()) {
//            RenSys.update(EM, dev);
//        }
//    }
//}

void GameMan::init_config(TheEngine& dev) {
    srand(time(NULL));
    dev.getDevice()->getCursorControl()->setVisible(false);
    dev.SetFont("assets/Interface/Font/chill.xml");
}

void GameMan::init_map(LevelMan& LM, TheEngine& dev, SoundSystem_t& SouSys) {
    LM.createMap(dev, SouSys);
    ColSys2::init_Hitoxes_Map2(LM, dev);
}