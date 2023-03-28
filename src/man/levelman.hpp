#pragma once
#include "../util/types.hpp"
#include "../sys/nodemapsys.hpp"
#include <irrlicht/IGUIImage.h>
#include <string>


struct LevelMan {
    using EneTAGs = MP::Typelist<TEnemy>;
    using voidCMP = MP::Typelist<PhysicsCmp2>;

    void update(TheEngine& dev, SoundSystem_t& SouSys, Enty& player){
        EM.foreach<voidCMP, EneTAGs>(
            [&](Enty& en, PhysicsCmp2&) {
                if(en.getDestroy()) createBasicEnemy(-30, 30, dev, SouSys);
            }
        );
        updateInterface(dev, player);
    }

    void createInterface (TheEngine& dev, Enty& player){
        
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
        mag = dev.addTextToPositionInScreen(magText, 1000,690,1080,710);
        //mag  = dev.addImageToPositionInScreen("assets/Interface/1280x720/cinco.png", 200,460);
        //std::cout<< "MAG ES " << mag <<"\n";
        //total ammo
        aux = std::to_string(ammo);
        convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* ammText = convert.c_str();
        amm1 = dev.addTextToPositionInScreen(ammText,900,690,1000,710);
        //HP
        aux = std::to_string(stats.hitpoints);
        convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* HPText = convert.c_str();
        h1 =  dev.addTextToPositionInScreen(HPText,100,690,200,710);

        //mira
        mir = dev.addImageToPositionInScreen("assets/Interface/1280x720/mira.png", 26, 150);

    }

    void updateInterface(TheEngine& dev, Enty& player){

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
        
        std::string aux = std::to_string(ammo);
        std::wstring convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* ammText = convert.c_str();
        dev.changeTextFromPointer(amm1, ammText);

        aux = std::to_string(magazine);
        convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* magText= convert.c_str();
        dev.changeTextFromPointer(mag, magText);

        aux = std::to_string(stats.hitpoints);
        convert = std::wstring(aux.begin(), aux.end());
        const wchar_t* HPText= convert.c_str();
        dev.changeTextFromPointer(h1, HPText);
       
    }

    void createMap(TheEngine& dev, NodeMapSys& MapSys, SoundSystem_t& SouSys) {
        irr::io::path models[6] = {
            "assets/models/mapas/mapa_simple_partes/Sala_1.obj",
            "assets/models/mapas/mapa_simple_partes/Sala_2.obj",
            "assets/models/mapas/mapa_simple_partes/Sala_3.obj",
            "assets/models/mapas/mapa_simple_partes/Pasillo_1.obj",
            "assets/models/mapas/mapa_simple_partes/Pasillo_2.obj",
            "assets/models/mapas/mapa_simple_partes/Pasillo_3.obj",
        };
        irr::io::path textures[6] = {
            "assets/textures/mapa/textura_Sala_1.png",
            "assets/textures/mapa/textura_sala_2.png",
            "assets/textures/mapa/textura_sala_3.png",
            "assets/textures/mapa/textura_pasillo_1.png",
            "assets/textures/mapa/textura_pasillo_2.png",
            "assets/textures/mapa/textura_pasillo_3.png",
        };

        Enty& map = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(map);
        EM.addComponent<NodoCmp>    (map, NodoCmp{.salas=MapSys.creaSalas()});
        EM.addComponent<SoundCmp>   (map, SoundCmp{.programmerSoundContext=SouSys.createinstance(0), .parametro=0, .play=true});
        EM.addTag      <TMap>       (map);
        
        for(uint8_t i {0}; i<6; i++) 
            createRoom(dev, models[i], textures[i]);
    }

    Enty& createPlayer(TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& player = EM.createEntity();
        EM.addComponent<PhysicsCmp2>   (player, PhysicsCmp2{.x=-30.f, .y=5, .z=20.f});
        EM.addComponent<RenderCmp2>    (player, dev.createPlayer("assets/models/armas/pistola.obj","assets/textures/fire.bmp"));
        EM.addComponent<InputCmp2>     (player, InputCmp2{ });
        //EM.addComponent<EstadoCmp>     (player, 0.945f, 4.005f, 1.01f);
        EM.addComponent<EstadoCmp>     (player, 1.5f, 4.f, 1.5f);
        EM.addComponent<EstadisticaCmp>(player, EstadisticaCmp{.hitpoints=100, .damage=5, .speed=40.f});
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
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo2.obj","assets/textures/portal1.bmp"));
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
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo2.obj","assets/textures/fire.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
        EM.addTag      <TDistEnemy> (enemy);
        return enemy;
    }
    
    Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=1.5f});

        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo3.obj","assets/textures/faerie2.bmp"));
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
        EM.addComponent<RenderCmp2> (door, dev.createModel("assets/models/personajes/monstruo3.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (door, 10.f, 10.f, 10.f);
        EM.addTag<TInteract>(door);
        EM.addTag<TWall>    (door);
        EM.addTag<TDoor>    (door);
        return door;
    }

    Enty& createKey(float x_pos, float z_pos, TheEngine& dev) {
        Enty& key = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(key, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
        EM.addComponent<RenderCmp2> (key, dev.createModel("assets/models/otros/enemy.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (key, 10.f, 10.f, 10.f);
        EM.addTag<TInteract>(key);
        EM.addTag<TKey>     (key);
        return key;
    }

    void createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth, TheEngine& dev) {
        Enty& wall = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(wall, pos_x, pos_y,  pos_z);
        EM.addComponent<EstadoCmp>  (wall, width, height, depth);
        //EM.addComponent<RenderCmp2> (wall, dev.createModel("assets/models/otros/enemy.obj","assets/textures/fire.bmp"));
        EM.addTag      <TInteract>  (wall);
        EM.addTag      <TWall>      (wall);
    }

    void createBullet(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
    float const dmg, float const spd, float const rad, double const slfD,
    double const pbx = 0, double const pby = 0, double const pbz = 0) {
        Enty& bullet = EM.createEntity();
        EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{ .damage = dmg, .speed = spd, .bulletRad = rad });
        EM.addComponent<PhysicsCmp2>(
        bullet, PhysicsCmp2{
                .x = phy_player.x + pbx,
                .y = phy_player.y + pby,
                .z = phy_player.z + pbz,
                .vx=  sin(phy_player.orieny) * cos(phy_player.orienx) * spd,
                .vy= -sin(phy_player.orienx) * spd,
                .vz=  cos(phy_player.orieny) * cos(phy_player.orienx) * spd
            }
        );
        EM.addComponent<RenderCmp2> (bullet, eng.createSphere(rad));
        EM.addComponent<EstadoCmp>  (bullet);
        EM.addComponent<SoundCmp>   (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
        EM.addComponent<SelfDestCmp>(bullet, slfD);
        EM.addTag<TBullet>          (bullet);
        EM.addTag<TInteract>        (bullet);
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

    void createRoom(TheEngine& dev, irr::io::path const model, irr::io::path const texture) {
        Enty& room = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(room);
        EM.addComponent<RenderCmp2> (room, dev.createModel(model, texture));
    }

    void defineAI(Enty& enemy) {
        int num = rand() % 360;
        double angle = num * irr::core::PI / 180;
        double radius = 30.0;
        EM.addComponent<AICmp>(
            enemy, 
            AICmp {
                .rad = radius,
                .ang = angle,
                .flock_x = cos(angle) * radius, 
                .flock_z = sin(angle) * radius, 
                .arrivalRadius = 1., 
                .timeArrive = 0.1, 
                .cooldown = 0.1, 
                .enable = true, 
                .behaviour = SB::Two_Steps 
            }
        );
    }

    EntyMan EM;

    TheEngine::IGUIText*  mag  {};
    //wchar_t*        magText{};
    TheEngine::IGUIText*  h1   {};
    //wchar_t*        HPText{};
    TheEngine::IGUIText*  amm1 {};
    //wchar_t*        ammText{};
    TheEngine::IGUIImage* mir  {};

};