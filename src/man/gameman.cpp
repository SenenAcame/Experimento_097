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
    RenSys2   RenSys;
    LevelMan  LM;
    TheEngine dev { 1000, 1000, &InpSys };
    
    PhySys2       PhySys;
    ColSys2       ColSys;
    AISys         AISys;
    NodeMapSys    MapSys;
    LogicSystem   LogicSys;
    SoundSystem_t SouSys;
    //SpawnSystem   SpawnSys;
    SelfDestSys   DestSys;

    //dev.getDevice();
    LM.initMenu(dev);

    while(dev.run()) {
        //////////////////////////////////////////////////////////////
        //  Menu inicial

        initial_menu(LM, dev, RenSys, InpSys);
    
        /////////////////////////////////////////////////////////////
        // Bucle principal del juego

        EntyMan&  EM = LM.getEM();

        init_config(dev);
        init_map(LM, dev, SouSys);
        LM.createEmptyInterface(dev);
    
        auto& player = LM.init_level(dev, SouSys);
        std::size_t player_ID = player.getID();
        bool dead { false }, pause { false };

        //actual moment ini
        constexpr double dt = 1.0/60;
        auto start = std::chrono::high_resolution_clock::now();
        constexpr int64_t maxFPS {60};
        constexpr int64_t nanos_per_frame {1000000000/maxFPS};
        int64_t frames = 0;

        while(!dead && dev.run()){
            auto frame_start = std::chrono::high_resolution_clock::now();
            
            if(pause) {
                RenSys.update(EM, dev);
                pause = InpSys.update_pause(dev, pause);
            }
            else {
                EM.      update();
                RenSys.  update(EM, dev);
                MapSys.  update(EM);
                InpSys.  update(LM, dev, SouSys, dt);
                AISys.   update(EM, dt, dev);
                PhySys.  update(EM, dt);
                ColSys.  update(EM);
                LogicSys.update(LM, dev, dt);
                PhySys.  update_after_colision(EM, dt);
                //SouSys.  update(EM);
                //SpawnSys.update(EM, dev, SouSys, player, map);
                //LM.      update(dev, SouSys, dt);
                LM.      update(dev, SouSys, dt, player_ID);
                DestSys. update(EM, dt);

                pause = InpSys.update_pause(dev, pause);
                dead  = EM.getEntityById(player_ID).getDestroy();
            }            

            while ((std::chrono::high_resolution_clock::now() - frame_start).count() < nanos_per_frame) {}
            ++frames;
        }

        LM.resetLevel(dev);

        auto end = std::chrono::high_resolution_clock::now();
        auto ellapse =  (end - start).count(); //how many nano sec has pass
        auto ellapseS =  double(ellapse)/1000000000.; //how many sec has pass
        std::cout <<" TIMEPO (s): " << ellapseS << "\n";
        std::cout <<" Frames " << frames<< "\n";
        std::cout <<" FPS " << double(frames)/ellapseS << "\n";
    }
    //RenSys.EndImgui();
}

void GameMan::initial_menu(LevelMan& LM, TheEngine& dev, RenSys2& RenSys, InpSys2& InpSys) {
    EntyMan&  EM = LM.getEM();
    bool menu { true };

    LM.setVisibleMenu(dev);
    dev.getDevice()->getCursorControl()->setVisible(true);
    
    while(menu && dev.run()) {
        RenSys.update(EM, dev);
        menu = InpSys.update_menu(LM, dev);
    }

    LM.setInvisibleMenu(dev);
}

void GameMan::init_config(TheEngine& dev) {
    srand(static_cast<unsigned int>(time(NULL)));
    dev.getDevice()->getCursorControl()->setVisible(false);
    //dev.SetFont("assets/Interface/Font/chill.xml");
}

void GameMan::init_map(LevelMan& LM, TheEngine& dev, SoundSystem_t& SouSys) {
    LM.createMap(dev, SouSys);
    ColSys2::init_Hitoxes_Map2(LM, dev);
}