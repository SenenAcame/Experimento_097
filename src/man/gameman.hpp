#pragma once
#include "chrono"
#include "../eng/engine.hpp"
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
#include "../util/types.hpp"
#include "../cmp/debug.hpp"
#include "../cmp/physicscmp2.hpp"
#include "../man/levelman.hpp"
#include "../sys/rensys2.hpp"

struct GameMan {
    void game() {
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
        TheEngine     dev {1080, 720, &InpSys};

        srand(time(NULL));
        dev.getDevice()->getCursorControl()->setVisible(false);

        LM.createMap(dev, MapSys, SouSys);
        ColSys.init_Hitoxes_Map2(LM, dev);
        auto& player = LM.createPlayer(dev, SouSys);
        
        LM.createInterface(dev, player);

        LM.createBasicEnemy(30, 30, dev, SouSys);
        //LM.createBasicEnemy(110, 60, dev, SouSys);
        //LM.createBasicEnemy(120, 60, dev, SouSys);
        //LM.createBasicEnemy(110, 70, dev, SouSys);
        //LM.createBasicEnemy(35, -60, dev, SouSys);
        //LM.createBasicEnemy(45, -60, dev, SouSys);
        //LM.createBasicEnemy(35, -70, dev, SouSys);

        //actual moment ini
        constexpr double dt = 1.0/60;
        //auto start = std::chrono::high_resolution_clock::now();
        //constexpr int64_t maxFPS {60};
        //constexpr int64_t nanos_per_frame {1000000000/maxFPS};
        //int64_t frames = 0;

        std::size_t player_ID = player.getID();
        bool dead { false };

        while(dev.run() && !dead){
            //auto frame_start = std::chrono::high_resolution_clock::now();
            EM.      update();
            RenSys.  update(EM, dev);
            MapSys.  update(EM);
            InpSys.  update(LM, dev, SouSys, dt);
            AISys.   update(EM, dt, dev);
            PhySys.  update(EM, dt);
            ColSys.  update(EM);
            LogicSys.update(EM, dev, dt);
            PhySys.  update_after_colision(EM, dt);
            SouSys.  update(EM);
            //SpawnSys.update(EM, dev, SouSys, player, map);
            LM.      update(dev, SouSys, player);
            DestSys. update(EM, dt);
            
            dead = EM.getEntityById(player_ID).getDestroy();
            //while ((std::chrono::high_resolution_clock::now() - frame_start).count() < nanos_per_frame){}
            //++frames;
        }
    
        //RenSys.EndImgui();
        //auto end = std::chrono::high_resolution_clock::now();
        //auto ellapse =  (end - start).count(); //how many nano sec has pass
        //auto ellapseS =  double(ellapse)/1000000000.; //how many sec has pass
        //std::cout <<" TIMEPO (s): " << ellapseS << "\n";
        //std::cout <<" Frames " << frames<< "\n";
        //std::cout <<" FPS " << double(frames)/ellapseS << "\n";

        //actual moment end
        //ellapse = end-start
    }
};