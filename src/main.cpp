#include "main.hpp"
#include "util/types.hpp"

void game2() {
    EntyMan       EM;
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
    TheEngine dev {1080, 720, &InpSys};

    ColSys.init_Hitoxes_Map(EM, dev);

    dev.getDevice()->getCursorControl()->setVisible(false);
    auto cam = dev.getCamera();

    Enty& map = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(map);
    EM.addComponent<PhysicsCmp2>(map);
    EM.addComponent<RenderCmp2> (map, dev.createModel("assets/models/mapa.obj","assets/textures/wall.bmp"));
    EM.addComponent<NodoCmp>    (map, NodoCmp{.salas=MapSys.creaSalas()});
    EM.addComponent<SoundCmp>   (map, SoundCmp{.programmerSoundContext=SouSys.createinstance(0), .parametro=0, .play=true});
    EM.addTag      <TMap>       (map);

    Enty& player = EM.createEntity();
    EM.addComponent<PhysicsCmp2>   (player, PhysicsCmp2{.x=-60.f, .y=5, .z=155.f});
    EM.addComponent<RenderCmp2>    (player, dev.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp"));
    EM.addComponent<InputCmp2>     (player, InputCmp2{ });
    EM.addComponent<EstadoCmp>     (player, 1.f, 90.f, 1.f);
    EM.addComponent<EstadisticaCmp>(player, EstadisticaCmp{.hitpoints=100.f, .damage=10.f, .speed=40.f});
    EM.addComponent<InventarioCmp> (player);
    EM.addComponent<SoundCmp>      (player, SouSys.createinstance(8));
    EM.addTag      <TPlayer>       (player);
    EM.addTag      <TInteract>     (player);

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
    //Enty& enemy1 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy1, PhysicsCmp2{ .x=-20.0f, .z=-20.0f});
    //EM.addComponent<RenderCmp2>     (enemy1, dev.createModel("assets/models/monstruo2.obj","assets/textures/fire.bmp"));
    //EM.addComponent<AICmp>          (enemy1, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Shoot, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy1, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy1, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy1, 1.f, 1.f, 1.f);
    //EM.addTag      <TDistEnemy>     (enemy1);
    //EM.addTag      <TEnemy>         (enemy1);
    //EM.addTag      <TInteract>      (enemy1);

    //Enty& enemy2 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy2, PhysicsCmp2{.x=-40.0f});
    //EM.addComponent<RenderCmp2>     (enemy2, dev.createModel("assets/models/enemy.obj","assets/textures/faerie2.bmp"));
    //EM.addComponent<AICmp>          (enemy2, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy2, EstadisticaCmp{.hitpoints=150.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy2, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy2, 1.f, 1.f, 1.f); 
    //EM.addTag      <TEnemy>         (enemy2);
    //EM.addTag      <TInteract>      (enemy2);

//patio1
    //Enty& enemy3 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy3, PhysicsCmp2{.x=-43.68f, .y=5.725f, .z=85.41f});
    //EM.addComponent<RenderCmp2>     (enemy3, dev.createModel("assets/models/monstruo3.obj","assets/textures/portal1.bmp"));
    //EM.addComponent<AICmp>          (enemy3, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy3, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy3, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy3, 1.525f, 5.725f, 2.105f); 
    //EM.addTag      <TEnemy>         (enemy3);
    //EM.addTag      <TInteract>      (enemy3);
    
    //Enty& enemy11 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy11, PhysicsCmp2{.x=-43.68f, .y=4.055f, .z=85.41f});
    //EM.addComponent<RenderCmp2>     (enemy11, dev.createModel("assets/models/monstruo2.obj","assets/textures/portal1.bmp"));
    //EM.addComponent<AICmp>          (enemy11, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy11, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy11, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy11, 0.945f, 4.005f, 1.01f); 
    //EM.addTag      <TEnemy>         (enemy11);
    //EM.addTag      <TInteract>      (enemy11);

    //Enty& enemy4 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy4, PhysicsCmp2{.x=-23.68f, .y=2.33f, .z=100.41});
    //EM.addComponent<RenderCmp2>     (enemy4, dev.createModel("assets/models/monstruo1.obj","assets/textures/portal1.bmp"));
    //EM.addComponent<AICmp>          (enemy4, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy4, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy4, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy4, 0.875f, 2.33f, 0.85f); 
    //EM.addTag      <TEnemy>         (enemy4);
    //EM.addTag      <TInteract>      (enemy4);

//lab3
    //Enty& enemy5 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy5, PhysicsCmp2{.x=23.68f, .z=20.41});
    //EM.addComponent<RenderCmp2>     (enemy5, dev.createModel("assets/models/monstruo2.obj","assets/textures/portal1.bmp"));
    //EM.addComponent<AICmp>          (enemy5, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy5, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy5, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy5, 1.f, 1.f, 1.f); 
    //EM.addTag      <TEnemy>         (enemy5);
    //EM.addTag      <TInteract>      (enemy5);

    //Enty& enemy6 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy6, PhysicsCmp2{ .x=35.0f, .z=-20.0f});
    //EM.addComponent<RenderCmp2>     (enemy6, dev.createModel("assets/models/monstruo2.obj","assets/textures/fire.bmp"));
    //EM.addComponent<AICmp>          (enemy6, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Shoot, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy6, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy6, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy6, 1.f, 1.f, 1.f);
    //EM.addTag      <TDistEnemy>     (enemy6);
    //EM.addTag      <TEnemy>         (enemy6);
    //EM.addTag      <TInteract>      (enemy6);

//finalpasillo2
    //Enty& enemy7 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy7, PhysicsCmp2{.x=10.0f, .z=-100});
    //EM.addComponent<RenderCmp2>     (enemy7, dev.createModel("assets/models/enemy.obj","assets/textures/faerie2.bmp"));
    //EM.addComponent<AICmp>          (enemy7, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy7, EstadisticaCmp{.hitpoints=150.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy7, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy7, 1.f, 1.f, 1.f); 
    //EM.addTag      <TEnemy>         (enemy7);
    //EM.addTag      <TInteract>      (enemy7);

    //Enty& enemy8 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy8, PhysicsCmp2{ .x=10.0f, .z=-160.0f});
    //EM.addComponent<RenderCmp2>     (enemy8, dev.createModel("assets/models/monstruo2.obj","assets/textures/fire.bmp"));
    //EM.addComponent<AICmp>          (enemy8, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Shoot, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy8, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy8, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy8, 1.f, 1.f, 1.f);
    //EM.addTag      <TDistEnemy>     (enemy8);
    //EM.addTag      <TEnemy>         (enemy8);
    //EM.addTag      <TInteract>      (enemy8);

//lab4
    //Enty& enemy9 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy9, PhysicsCmp2{ .x=50.0f, .z=-100.0f});
    //EM.addComponent<RenderCmp2>     (enemy9, dev.createModel("assets/models/monstruo2.obj","assets/textures/fire.bmp"));
    //EM.addComponent<AICmp>          (enemy9, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Shoot, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy9, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy9, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy9, 1.f, 1.f, 1.f);
    //EM.addTag      <TDistEnemy>     (enemy9);
    //EM.addTag      <TEnemy>         (enemy9);
    //EM.addTag      <TInteract>      (enemy9);

    //Enty& enemy10 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy10, PhysicsCmp2{.x=60.f, .z=-90.f});
    //EM.addComponent<RenderCmp2>     (enemy10, dev.createModel("assets/models/monstruo2.obj","assets/textures/portal1.bmp"));
    //EM.addComponent<AICmp>          (enemy10, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy10, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy10, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy10, 1.f, 1.f, 1.f); 
    //EM.addTag      <TEnemy>         (enemy10);
    //EM.addTag      <TInteract>      (enemy10);



    //Enty& enemy3 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>    (enemy3, PhysicsCmp2{.x=-19.f, .z=30.f});
    //EM.addComponent<RenderCmp2>     (enemy3, dev.createModel("assets/models/enemy.obj","assets/textures/faerie2.bmp"));
    //EM.addComponent<AICmp>          (enemy3, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
    //EM.addComponent<EstadisticaCmp> (enemy3, EstadisticaCmp{.hitpoints=100.f, .damage=10.f, .speed=1.f});
    //EM.addComponent<SoundCmp>       (enemy3, SouSys.createinstance(7));
    //EM.addComponent<EstadoCmp>      (enemy3);
    //EM.addTag      <TEnemy>         (enemy3);
    //EM.addTag      <TInteract>      (enemy3);

    //Enty& spawn = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>(spawn, PhysicsCmp2{ .x=-10.f, .z=20.f });
    //EM.addComponent<SpawnCmp>   (spawn);
    //EM.addTag      <TSpawn>     (spawn);

    //SouSys.startsound(EM.getComponent<SoundCmp>(map));

    //Enty& playerwalksou = EM.createEntity();
    //EM.addComponent<SoundCmp>(playerwalksou, SouSys.createinstance(4));

    //Enty& playerdamagesou = EM.createEntity();
    //EM.addComponent<SoundCmp>(playerdamagesou, SouSys.createinstance(3));

    //Enty& weaponsou = EM.createEntity();
    //EM.addComponent<SoundCmp>(weaponsou, SouSys.createinstance(1));
    //EM.addTag      <TWeapon> (weaponsou);

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
        MapSys.  update(EM, cam);
        AISys.   update(EM, dt, dev);
        InpSys.  update(EM, dev, SouSys, 1.0/maxFPS);
        ColSys.  update(EM);
        LogicSys.update(EM, dev, dt);
        PhySys.  update(EM, dt);
        SouSys.  update(EM);
        LogicSys.update(EM, dev, dt);
        SpawnSys.update(EM, dev, SouSys, player, map);
        DestSys. update(EM, dt);

        while ((std::chrono::high_resolution_clock::now() - frame_start).count() < nanos_per_frame){}
        ++frames;
    }
    
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