#include "main.hpp"
#include "man/levelman.hpp"
#include "sys/rensys2.hpp"

void game2() {
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
    SpawnSystem   SpawnSys;
    SelfDestSys   DestSys;
    TheEngine     dev {1080, 720, &InpSys};

    
    
    srand(time(NULL));
    ColSys.init_Hitoxes_Map(EM, dev);
    dev.getDevice()->getCursorControl()->setVisible(false);

    Enty& map    = LM.createMap(dev, MapSys, SouSys);
    Enty& player = LM.createPlayer(dev, SouSys);

    LM.createInterface(dev,player);
    //LM.updateInterfaceAmmo(dev);
    //Enty& door   = LM.createDoor(52.39, -140.98, dev);
    //Enty& key    = LM.createKey(-40, -20, dev);

    //LM.createBasicEnemy(-25, -20, dev, SouSys);
    //LM.createBasicEnemy(-20, -25, dev, SouSys);
    //LM.createBasicEnemy(-30, -20, dev, SouSys);
    //LM.createBasicEnemy(-20, -30, dev, SouSys);
    //LM.createBasicEnemy(-25, -25, dev, SouSys);

    //Enty& weapon = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (weapon,10,0,20);
    //EM.addComponent<RenderCmp2>     (weapon, dev.createModel("assets/models/pistola.obj","assets/textures/fire.bmp"));
    //
    //Enty& w2 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (w2,10,0,20);
    //EM.addComponent<RenderCmp2>     (w2, dev.createModel("assets/models/player_arm.obj","assets/textures/fire.bmp"));

    //Enty& w3 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>(w3, 12.5, 0, 9);
    //EM.addComponent<RenderCmp2> (w3, dev.createModel("assets/models/enemy.obj","assets/textures/fire.bmp"));
    //EM.addComponent<EstadoCmp>  (w3, 0, 0, 0);
    //EM.addTag      <TInteract>  (w3);
    //EM.addTag      <TWall>      (w3);
    //EM.addTag      <TWeapon>    (w3);

//Lab1
    //Enty& enemy1 = LM.createSmallEnemy(-20, -20, dev, SouSys);
    //Enty& enemy2 = LM.createBasicEnemy(-40,   0, dev, SouSys);
    //weapon
    //Enty& weaponEsco = LM.createWeapon(-50.f, 5.725, -20.f, dev, SouSys, 1 ,20 ,2 ,1.4);
    //Enty& weaponAME  = LM.createWeapon(-20.f, 5.725, -20.f, dev, SouSys, 2 ,20 ,2 ,1.4);

//patio1
    //Enty& enemy3  = LM.createBasicEnemy(-23.68, 100.41, dev, SouSys);
    //Enty& enemy4  = LM.createSmallEnemy (-43.68,  85.41, dev, SouSys);

//lab3
    //Enty& enemy5 = LM.createTankEnemy(23.68, 20.41, dev, SouSys);
    //Enty& enemy6 = LM.createBasicEnemy(35, -20, dev, SouSys);

//finalpasillo2
    //Enty& enemy7 = LM.createTankEnemy(10, -100, dev, SouSys);

//lab4
    //Enty& enemy9 = LM.createDistEnemy(50, -100, dev, SouSys);
    //Enty& enemy10 = LM.createDistEnemy(60, 90, dev, SouSys);

    //Enty& spawn = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>(spawn, PhysicsCmp2{ .x=-10.f, .z=20.f });
    //EM.addComponent<SpawnCmp>   (spawn);
    //EM.addTag      <TSpawn>     (spawn);

//    SouSys.startsound(EM.getComponent<SoundCmp>(map));
//
//    Enty& playerwalksou = EM.createEntity();
//    EM.addComponent<SoundCmp>(playerwalksou, SouSys.createinstance(4));
//
//    Enty& playerdamagesou = EM.createEntity();
//    EM.addComponent<SoundCmp>(playerdamagesou, SouSys.createinstance(3));
//
//    Enty& weaponsou = EM.createEntity();
//    EM.addComponent<SoundCmp>(weaponsou, SouSys.createinstance(1));
//    EM.addTag      <TWeapon> (weaponsou);

    constexpr double dt = 1.0/60;
    //actual moment ini
    auto start = std::chrono::high_resolution_clock::now();
    constexpr int64_t maxFPS {60};
    constexpr int64_t nanos_per_frame {1000000000/maxFPS};
    int64_t frames =0;

    while(dev.run()){
        auto frame_start = std::chrono::high_resolution_clock::now();
        EM.      update();
        RenSys.  update(EM, dev);
        MapSys.  update(EM);
        ColSys.  update(EM);
        InpSys.  update(EM, dev, SouSys, 1.0/maxFPS);
        AISys.   update(EM, dt, dev);
        LogicSys.update(EM, dev, dt);
        PhySys.  update(EM, dt);
        SouSys.  update(EM);
        LogicSys.update(EM, dev, dt);
        SpawnSys.update(EM, dev, SouSys, player, map);
        LM.      update(dev, SouSys, player);
        DestSys. update(EM, dt);

        while ((std::chrono::high_resolution_clock::now() - frame_start).count() < nanos_per_frame){}
        ++frames;
    }
    
    //RenSys.EndImgui();
    auto end = std::chrono::high_resolution_clock::now();
    auto ellapse =  (end - start).count(); //how many nano sec has pass
    auto ellapseS =  double(ellapse)/1000000000.; //how many sec has pass

    std::cout <<" TIMEPO (s): " << ellapseS << "\n";
    std::cout <<" Frames " << frames<< "\n";
    std::cout <<" FPS " << double(frames)/ellapseS << "\n";

    //actual moment end
    //ellapse = end-start
}

int main(){
    //game();
    game2();
}