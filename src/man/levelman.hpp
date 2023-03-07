#pragma once
#include "../util/types.hpp"

struct LevelMan {
    Enty& createMap(TheEngine& dev, NodeMapSys& MapSys, SoundSystem_t& SouSys) {
        Enty& map = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(map);
        EM.addComponent<PhysicsCmp2>(map);
        EM.addComponent<RenderCmp2> (map, dev.createModel("assets/models/mapa.obj","assets/textures/wall.bmp"));
        EM.addComponent<NodoCmp>    (map, NodoCmp{.salas=MapSys.creaSalas()});
        EM.addComponent<SoundCmp>   (map, SoundCmp{.programmerSoundContext=SouSys.createinstance(0), .parametro=0, .play=true});
        EM.addTag      <TMap>       (map);
        return map;
    }

    Enty& createPlayer(TheEngine& dev, SoundSystem_t& SouSys) {
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
        return player;
    }

    Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(x_pos, 2.33, z_pos, dev, SouSys);
        EM.addComponent<RenderCmp2>     (enemy, dev.createModel("assets/models/monstruo1.obj","assets/textures/faerie2.bmp"));
        EM.addComponent<EstadisticaCmp> (enemy, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.5f});
        EM.addComponent<AICmp>          (enemy, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
        EM.addComponent<EstadoCmp>      (enemy, 0.875f, 2.33f, 0.85f); 
        return enemy;
    }

    Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(x_pos, 4.055, z_pos, dev, SouSys);
        EM.addComponent<RenderCmp2>    (enemy, dev.createModel("assets/models/monstruo2.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
        EM.addComponent<AICmp>         (enemy, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
        EM.addComponent<EstadoCmp>     (enemy, 0.945f, 4.005f, 1.01f);
        return enemy;
    }
    
    Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(x_pos, 4.055, z_pos, dev, SouSys);
        EM.addComponent<RenderCmp2>    (enemy, dev.createModel("assets/models/monstruo2.obj","assets/textures/fire.bmp"));
        EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.f});
        EM.addComponent<AICmp>         (enemy, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Shoot, .cooldown=1. });
        EM.addComponent<EstadoCmp>     (enemy, 0.945f, 4.005f, 1.01f);
        EM.addTag      <TDistEnemy>    (enemy);
        return enemy;
    }
    
    Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(x_pos, 5.725, z_pos, dev, SouSys);
        EM.addComponent<RenderCmp2>     (enemy, dev.createModel("assets/models/monstruo3.obj","assets/textures/faerie2.bmp"));
        EM.addComponent<EstadisticaCmp> (enemy, EstadisticaCmp{.hitpoints=150.f, .damage=20.f, .speed=1.f});
        EM.addComponent<AICmp>          (enemy, AICmp{ .enable=true, .arrivalRadius=1.0, .timeArrive=0.1, .behaviour=SB::Seek, .cooldown=1. });
        EM.addComponent<EstadoCmp>      (enemy, 1.525f, 5.725f, 2.105f); 
        return enemy;
    }

    Enty& createDoor(float x_pos, float z_pos, TheEngine& dev) {
        Enty& door = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(door, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
        EM.addComponent<RenderCmp2> (door, dev.createModel("assets/models/monstruo3.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (door, 10, 10, 10);
        EM.addTag<TInteract>(door);
        EM.addTag<TWall>    (door);
        EM.addTag<TDoor>    (door);
        return door;
    }

    Enty& createKey(float x_pos, float z_pos, TheEngine& dev) {
        Enty& key = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(key, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
        EM.addComponent<RenderCmp2> (key, dev.createModel("assets/models/enemy.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (key, 10, 10, 10);
        EM.addTag<TInteract>(key);
        EM.addTag<TKey>     (key);
        return key;
    }

    EntyMan& getEM() { return EM; }
private:
    Enty& createEnemy(float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys){
        Enty& enemy = EM.createEntity();
        EM.addComponent<PhysicsCmp2>    (enemy, PhysicsCmp2{.x=x_pos, .y=y_pos, .z=z_pos});
        EM.addComponent<SoundCmp>       (enemy, SouSys.createinstance(7));
        EM.addTag      <TEnemy>         (enemy);
        EM.addTag      <TInteract>      (enemy);
        return enemy;
    }

    EntyMan EM;
};