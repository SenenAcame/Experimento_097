#pragma once
#include "../util/types.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <irrlicht/IGUIImage.h>
#include <string>


struct LevelMan {
    using EneTAGs = MP::Typelist<TEnemy>;
    using voidCMP = MP::Typelist<PhysicsCmp2>;

    void update(TheEngine& dev, SoundSystem_t& SouSys, Enty& player, double dt){
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
        updateInterface   (dev, player);
        cleanHitsInterface(dev, dt);
    }

    void createInterface (TheEngine& dev, Enty& player){
        
        auto heightScreen   = dev.getHeight();
        auto widthScreen    = dev.getWidth();
        auto widthNumbers   = heightScreen-100;
        auto widthNumbers2  = heightScreen-20;
        //hits
        hit1 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png",widthScreen/2-200,heightScreen/2-100);
        dev.setInvisibleImage(hit1);
        hit2 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png",widthScreen/2+200,heightScreen/2);
        dev.setInvisibleImage(hit2);
        hit3 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png",widthScreen/2,heightScreen/2+100);
        dev.setInvisibleImage(hit3);

        //Magazine
        auto equipment = EM.getComponent<InventarioCmp> (player);
        auto stats = EM.getComponent<EstadisticaCmp> (player);
        int magazine = 0;
        int ammo     = 0;
        switch (equipment.equipada) {
            case 0: magazine = equipment.magazine1; 
                    ammo = equipment.ammo1;        
                    
            break;
            case 1: magazine = equipment.magazine2;
                    ammo = equipment.ammo2;
                    
            break;
            case 2: magazine = equipment.magazine3;
                    ammo = equipment.ammo3;
                    
            break;
            default: break;
        }
        std::string aux = std::to_string(magazine);
        std::wstring convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* magText = convert.c_str();
        mag = dev.addTextToPositionInScreen(magText, widthScreen/10*8,widthNumbers,widthScreen/10*9,widthNumbers2);
        //mag  = dev.addImageToPositionInScreen("assets/Interface/1280x720/cinco.png", 200,460);
        //std::cout<< "MAG ES " << mag <<"\n";
        //total ammo
        aux = std::to_string(ammo);
        convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* ammText = convert.c_str();
        amm1 = dev.addTextToPositionInScreen(ammText,widthScreen/10*9,widthNumbers,widthScreen,widthNumbers2);
        separacion = dev.addTextToPositionInScreen(L"/",widthScreen/10*8.5,widthNumbers,widthScreen,widthNumbers2);
        //HP
        aux = std::to_string(stats.hitpoints);
        convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* HPText = convert.c_str();
        hp =  dev.addTextToPositionInScreen(L"VIDA:",0,widthNumbers,widthScreen/10*2,widthNumbers2);
        h1 =  dev.addTextToPositionInScreen(HPText,widthScreen/10,widthNumbers,widthScreen/10*2,widthNumbers2);

        //mira
        mir = dev.addImageToPositionInScreen("assets/Interface/1280x720/mira.png", widthScreen/2, heightScreen/2);

    }


    void updateInterfaceMag(TheEngine& dev, int maga){
        
        std::string aux = std::to_string(maga);
        std::wstring convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* magText= convert.c_str();
        dev.changeTextFromPointer(mag, magText);
    }


    void updateInterfaceWhenReload(TheEngine& dev, int maga, int amm){

        std::string aux = std::to_string(maga);
        std::wstring convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* magText= convert.c_str();
        dev.changeTextFromPointer(mag, magText);

        aux = std::to_string(amm);
        convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* ammText = convert.c_str();
        dev.changeTextFromPointer(amm1, ammText);
    }

    void updateInterfaceHit(TheEngine& dev, Enty& player){

        auto stats        = EM.getComponent<EstadisticaCmp> (player);
        std::string  aux        = std::to_string(stats.hitpoints);
        std::wstring convert    = std::wstring(aux.begin(), aux.end());
        const wchar_t* HPText   = convert.c_str();
        dev.changeTextFromPointer(h1, HPText);

        int random = activateHit;
        while(activateHit==random){
            random = rand()%3+1;
        }
    
        activateHit = random;
        
        
        switch (activateHit) {

            case 1:
                cd1 = 1;
                dev.setVisibleImage(hit1);
            break;

            case 2:
                cd2 = 1;
                dev.setVisibleImage(hit2);
            break;

            case 3:
                cd3 = 1;
                dev.setVisibleImage(hit3);
            break;

        
        }

    }

    void cleanHitsInterface(TheEngine& dev ,double dt){

        if(cd1 == 1){
            clockHit1+=dt;
            if(clockHit1>=cd1){
                dev.setInvisibleImage(hit1);
            }
        }
        if(cd2 ==1){
            clockHit2+=dt;
            if(clockHit2>=cd2){
                dev.setInvisibleImage(hit2);
            }
        }
        if(cd3 ==1){
            clockHit3+=dt;
            if(clockHit3>=cd3){
                dev.setInvisibleImage(hit3);
            }
        }

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
        EM.addComponent<EstadisticaCmp>(player, EstadisticaCmp{.hitpoints=100, .damage=10, .speed=40.f});
        EM.addComponent<InventarioCmp> (player);
        EM.addComponent<SoundCmp>      (player, SouSys.createinstance(8));
        EM.addComponent<SalaCmp>       (player);
        EM.addTag      <TPlayer>       (player);
        EM.addTag      <TInteract>     (player);
        return player;
    }

    Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=5, .damage=20, .speed=15.f});
        
        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo2.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
        return enemy;
    }

    Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=3.f});
        
        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=2.33, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo1.obj","assets/textures/faerie2.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.875f, 2.33f, 0.85f);
        EM.addTag      <TSmallEnemy>(enemy);
        return enemy;
    }

    Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=1.5f});

        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo2.obj","assets/textures/fire.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
        EM.addTag      <TDistEnemy> (enemy);
        return enemy;
    }
    
    Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=1.5f});

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

    //INTERFACE
    TheEngine::IGUIText*  mag  {};
    //wchar_t*        magText{};
    TheEngine::IGUIText*  h1   {};
    TheEngine::IGUIText*  hp   {};
    //wchar_t*        HPText{};
    TheEngine::IGUIText*  amm1 {};
    TheEngine::IGUIText*  separacion {};
    //wchar_t*        ammText{};
    TheEngine::IGUIImage* mir  {};

    //Hits
    
    int                   activateHit {0};
    TheEngine::IGUIImage* hit1        {};
    double                cd1         {0};
    double                clockHit1   {};
    TheEngine::IGUIImage* hit2        {};
    double                cd2         {0};
    double                clockHit2   {};
    TheEngine::IGUIImage* hit3        {};
    double                cd3         {0};
    double                clockHit3   {};

};