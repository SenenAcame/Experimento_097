#pragma once
#include "../util/types.hpp"
#include <irrlicht/IGUIImage.h>

struct LevelMan {
    using EneTAGs = MP::Typelist<TEnemy>;
    using voidCMP = MP::Typelist<PhysicsCmp2>;

    void update(TheEngine& dev, SoundSystem_t& SouSys){
        EM.foreach<voidCMP, EneTAGs>(
            [&](Enty& en, PhysicsCmp2&) {
                if(en.getDestroy()){
                    if(en.hasTAG<TDistEnemy>()){
                        createDistEnemy(-20, -20, dev, SouSys);
                    }
                    else if(en.hasTAG<TSmallEnemy>()){
                        createSmallEnemy(-20, -20, dev, SouSys);
                    }
                    else if(en.hasTAG<TTankEnemy>()){
                        createTankEnemy(-20, -20, dev, SouSys);
                    }
                    else{
                        createBasicEnemy(-20, -20, dev, SouSys);
                    }
                }
            }
        );
    }

    void createInterface (TheEngine& dev){
        
        //Magazine
        wchar_t* prueba = L"PRUEBA 1";
        mag = dev.addTextToPositionInScreen(prueba, 10,10,260,22);
        //mag  = dev.addImageToPositionInScreen("assets/Interface/1280x720/cinco.png", 200,460);
        //std::cout<< "MAG ES " << mag <<"\n";
        //total ammo
        //amm1 = dev.addImageToPositionInScreen("assets/Interface/1280x720/uno.png" , 400,450);
        //amm2 = dev.addImageToPositionInScreen("assets/Interface/1280x720/cero.png", 460,410);
        //amm3 = dev.addImageToPositionInScreen("assets/Interface/1280x720/cero.png", 540,410);
        //HP
        //h1 =  dev.addImageToPositionInScreen("assets/Interface/1280x720/uno.png" , -360,450);
        //h2 =  dev.addImageToPositionInScreen("assets/Interface/1280x720/cero.png", -260,410);
        //h3 =  dev.addImageToPositionInScreen("assets/Interface/1280x720/cero.png", -170,410);

        //mira
        mir = dev.addImageToPositionInScreen("assets/Interface/1280x720/mira.png", 26, 150);

    }

    void updateInterfaceAmmo(TheEngine& dev){

       //std::cout<< "VOY A MAG ES " << mag <<"\n";
       //dev.changeImageFromPointer(mag,"assets/Interface/1280x720/cero.png");
       wchar_t* prueba = L"CAMBIADO";
       dev.changeTextFromPointer(mag, prueba);
       


    }

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
        EM.addComponent<EstadoCmp>     (player, 0.945f, 4.005f, 1.01f);
        EM.addComponent<EstadisticaCmp>(player, EstadisticaCmp{.hitpoints=100.f, .damage=10.f, .speed=40.f});
        EM.addComponent<InventarioCmp> (player);
        EM.addComponent<SoundCmp>      (player, SouSys.createinstance(8));
        EM.addComponent<SalaCmp>       (player);
        EM.addTag      <TPlayer>       (player);
        EM.addTag      <TInteract>     (player);
        return player;
    }

    Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=5.f, .damage=20.f, .speed=15.f});
        
        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo2.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
        return enemy;
    }

    Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=3.f});
        
        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=2.33, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo1.obj","assets/textures/faerie2.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.875f, 2.33f, 0.85f);
        EM.addTag      <TSmallEnemy>(enemy);
        return enemy;
    }

    Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.5f});

        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo2.obj","assets/textures/fire.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
        EM.addTag      <TDistEnemy> (enemy);
        return enemy;
    }
    
    Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100.f, .damage=20.f, .speed=1.5f});

        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo3.obj","assets/textures/faerie2.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 1.525f, 5.725f, 2.105f);
        EM.addTag      <TTankEnemy> (enemy);
        return enemy;
    }

    Enty& createWeapon(float x_pos, float y_pos, float z_pos, 
    TheEngine& dev, SoundSystem_t& SouSys, size_t tipo, int ammo, int magazine, double reloadTimer){
        Enty& weapon = EM.createEntity  ();
        EM.addComponent<PhysicsCmp2>    (weapon, PhysicsCmp2{.x=x_pos, .y=y_pos, .z=z_pos});
        switch (tipo) {
            
            case 0:
                EM.addComponent<RenderCmp2>     (weapon, dev.createModel("assets/models/armas/pistola.obj","assets/textures/faerie2.bmp"));        
                
            break;

            case 1:
                EM.addComponent<RenderCmp2>     (weapon, dev.createModel("assets/models/armas/escopeta.obj","assets/textures/faerie2.bmp"));        
                
            break;

            case 2:
                EM.addComponent<RenderCmp2>     (weapon, dev.createModel("assets/models/armas/subfusil.obj","assets/textures/faerie2.bmp"));        
                
            break;

            default:
            break;
        
        }
        
        EM.addComponent<WeaponCmp>      (weapon, WeaponCmp{.typeWe = tipo, .ammo= ammo, .magazine= magazine, .reload= reloadTimer});
        EM.addComponent<SoundCmp>       (weapon, SouSys.createinstance(1));
        EM.addComponent<EstadoCmp>      (weapon, 1.525f, 5.725f, 2.105f); 
        EM.addTag      <TWeapon>        (weapon);
        EM.addTag      <TInteract>      (weapon);
        return weapon;
    }

    Enty& createDoor(float x_pos, float z_pos, TheEngine& dev) {
        Enty& door = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(door, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
        EM.addComponent<RenderCmp2> (door, dev.createModel("assets/models/monstruo3.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (door, 10.f, 10.f, 10.f);
        EM.addTag<TInteract>(door);
        EM.addTag<TWall>    (door);
        EM.addTag<TDoor>    (door);
        return door;
    }

    Enty& createKey(float x_pos, float z_pos, TheEngine& dev) {
        Enty& key = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(key, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
        EM.addComponent<RenderCmp2> (key, dev.createModel("assets/models/enemy.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (key, 10.f, 10.f, 10.f);
        EM.addTag<TInteract>(key);
        EM.addTag<TKey>     (key);
        return key;
    }

    EntyMan& getEM() { return EM; }
private:
    Enty& createEnemy(SoundSystem_t& SouSys){
        Enty& enemy = EM.createEntity();
        defineAI(enemy);
        EM.addComponent<SoundCmp> (enemy, SouSys.createinstance(7));
        EM.addComponent<SalaCmp>  (enemy);
        EM.addTag      <TEnemy>   (enemy);
        EM.addTag      <TInteract>(enemy);
        return enemy;
    }

    void defineAI(Enty& enemy) {
        int num = rand() % 360;
        double angle = num * irr::core::PI / 180;
        double radius = 20.0;
        EM.addComponent<AICmp>(
            enemy, 
            AICmp {
                .rad = radius,
                .ang = angle,
                .flock_x = cos(angle) * radius, 
                .flock_z = sin(angle) * radius, 
                .arrivalRadius = 1., 
                .timeArrive = 0.1, 
                .cooldown = 1., 
                .enable = true, 
                .behaviour = SB::Two_Steps 
            }
        );
    }

    EntyMan EM;

    TheEngine::IGUIText*  mag  {};
    TheEngine::IGUIText*  h1   {};
    TheEngine::IGUIText*  h2   {};
    TheEngine::IGUIText*  h3   {};
    TheEngine::IGUIText*  amm1 {};
    TheEngine::IGUIText*  amm2 {};
    TheEngine::IGUIText*  amm3 {};
    TheEngine::IGUIImage*  mir  {};

};