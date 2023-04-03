#pragma once
#include "../util/types.hpp"
#include "../sys/nodemapsys.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <irrlicht/IGUIImage.h>
#include <string>

struct LevelMan {
    using voidCMP = MP::Typelist<PhysicsCmp2>;
    using EneTAGs = MP::Typelist<TEnemy>;
    using voidCMP2 = MP::Typelist<PhysicsCmp2>;
    using EneTAGs2 = MP::Typelist<TSpawn>;

    void update(TheEngine& dev, SoundSystem_t& SouSys, double const dt){
        EM.foreach<voidCMP, EneTAGs>(
            [&](Enty& en, PhysicsCmp2&) {
                
                if(en.getDestroy()) {std::cout<<"Enemigo muerto \n";
                aliveEnemys--; numberOfEnemysBasics--;}
                
                //createBasicEnemy(-30, 30, dev, SouSys)
                ;
            }
        );
        double spawnX{0}, spawnY{0};
        EM.foreach<voidCMP2, EneTAGs2>(
        [&](Enty& en, PhysicsCmp2& f) {
            if(inRound == true && numberOfEnemysBasics > 0 && aliveEnemys < maxEnemysWave){
                spawnX = f.x;
                spawnY = f.y;
                createBasicEnemy(-30, 30, dev, SouSys, extraHeal, waveNumber);
                aliveEnemys++;
                
            }
                
        }
        );
        if(inRound == true && numberOfEnemysBasics == 0){
            inRound = false;
            
            std::cout<<"NOT In round: "<<inRound<<"\n";

        }
       
        else if(inRound == false){
            clockToNextWave += dt;
            std::cout<<"Clock To next wave: "<<clockToNextWave<<"\n";
            if(clockToNextWave >= timeBtwWaves){
                inRound = true;
                clockToNextWave = 0;
                numberOfEnemysBasics = 2+extraEnemys*waveNumber;
                waveNumber++;
                std::cout<<"Enemys this round: "<<numberOfEnemysBasics<<"\n";
                std::cout<<"In round: "<<inRound<<"\n";
            }
        }
        else if(inRound == true){ //only to debug without interface
            std::cout<<"Max Enemys Wave: "<<maxEnemysWave<<"\n";
            std::cout<<"Alive enemys: "<<aliveEnemys<<"\n";
            std::cout<<"Enemys this round: "<<numberOfEnemysBasics<<"\n";
            std::cout<<"Wave: "<<waveNumber<<"\n";
        }
        cleanHitsInterface(dev, dt);
    }

    auto& init_level(TheEngine& dev, SoundSystem_t& SouSys) {
        auto& player = createPlayer(dev, SouSys);
        createInterface(dev, player);
        createWeapon(-65, 5, 30, dev, SouSys, 2);
        
        inRound = true;
        //createBasicEnemy(110, 60, dev, SouSys);
        //createBasicEnemy(120, 60, dev, SouSys);
        //createBasicEnemy(110, 70, dev, SouSys);
        //createBasicEnemy(35, -60, dev, SouSys);
        //createBasicEnemy(45, -60, dev, SouSys);
        //createBasicEnemy(35, -70, dev, SouSys);
        return player;
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

    //void updateInterface(TheEngine& dev, Enty& player) {
    //    auto equipment = EM.getComponent<InventarioCmp> (player);
    //    auto stats = EM.getComponent<EstadisticaCmp> (player);
    //    int magazine = 0;
    //    int ammo     = 0;
    //    switch (equipment.equipada) {
    //        case 0: magazine = equipment.magazine1; 
    //                ammo = equipment.ammo1;
    //        break;
    //        case 1: magazine = equipment.magazine2;
    //                ammo = equipment.ammo2;
    //        break;
    //        case 2: magazine = equipment.magazine3;
    //                ammo = equipment.ammo3;
    //        break;
    //        default: break;
    //    }
    //}

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
                clockHit1 = 0;
                cd1 = 0;
            }
        }
        if(cd2 ==1){
            clockHit2+=dt;
            if(clockHit2>=cd2){
                dev.setInvisibleImage(hit2);
                clockHit2 = 0;
                cd2 = 0;
            }
        }
        if(cd3 ==1){
            clockHit3+=dt;
            if(clockHit3>=cd3){
                dev.setInvisibleImage(hit3);
                clockHit3 = 0;
                cd3 = 0;
            }
        }
    }

    void createMap(TheEngine& dev, SoundSystem_t& SouSys) {
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
        EM.addComponent<NodoCmp>    (map, NodoCmp{.salas = NodeMapSys::creaSalas()});
        EM.addComponent<SoundCmp>   (map, SoundCmp{.programmerSoundContext = SouSys.createinstance(0), .parametro = 0, .play = true});
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

    Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, int extraHeal, int waveNumber) {
        Enty& enemy = createEnemy(SouSys);
        auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=50+extraHeal*waveNumber, .damage=20, .speed=15.f});
        
        EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
        EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo2.obj","assets/textures/portal1.bmp"));
        EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
        return enemy;
    }

    //Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
    //    Enty& enemy = createEnemy(SouSys);
    //    auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=3.f});
    //    
    //    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=2.33, .z=z_pos, .kMxVLin = stats.speed});
    //    EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo1.obj","assets/textures/faerie2.bmp"));
    //    EM.addComponent<EstadoCmp>  (enemy, 0.875f, 2.33f, 0.85f);
    //    EM.addTag      <TSmallEnemy>(enemy);
    //    return enemy;
    //}
    //
    //Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
    //    Enty& enemy = createEnemy(SouSys);
    //    auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=1.5f});
    //
    //    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
    //    EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo2.obj","assets/textures/fire.bmp"));
    //    EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
    //    EM.addTag      <TDistEnemy> (enemy);
    //    return enemy;
    //}
    //
    //Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
    //    Enty& enemy = createEnemy(SouSys);
    //    auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=1.5f});
    //
    //    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
    //    EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo3.obj","assets/textures/faerie2.bmp"));
    //    EM.addComponent<EstadoCmp>  (enemy, 1.525f, 5.725f, 2.105f);
    //    EM.addTag      <TTankEnemy> (enemy);
    //    return enemy;
    //}
    //
    Enty& createWeapon(float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, size_t tipo){
        Enty& weapon = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(weapon, PhysicsCmp2{.x=x_pos, .y=y_pos, .z=z_pos});
        switch (tipo) {
            case 0:
                EM.addComponent<RenderCmp2>(weapon, dev.createModel("assets/models/armas/pistola.obj","assets/textures/faerie2.bmp"));
                break;
            case 1:
                EM.addComponent<RenderCmp2>(weapon, dev.createModel("assets/models/armas/escopeta.obj","assets/textures/faerie2.bmp"));
                break;
            case 2:
                EM.addComponent<RenderCmp2>(weapon, dev.createModel("assets/models/armas/subfusil.obj","assets/textures/faerie2.bmp"));
                break;
            default: break;
        }
        EM.addComponent<WeaponCmp>(weapon, tipo);
        EM.addComponent<SoundCmp>(weapon, SouSys.createinstance(1));
        EM.addComponent<EstadoCmp>(weapon, 1.f, 1.f, 3.f); 
        EM.addTag      <TWeapon> (weapon);
        EM.addTag      <TInteract>(weapon);
        return weapon;
    }
    //
    //Enty& createDoor(float x_pos, float z_pos, TheEngine& dev) {
    //    Enty& door = EM.createEntity();
    //    EM.addComponent<PhysicsCmp2>(door, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
    //    EM.addComponent<RenderCmp2> (door, dev.createModel("assets/models/personajes/monstruo3.obj","assets/textures/portal1.bmp"));
    //    EM.addComponent<EstadoCmp>  (door, 10.f, 10.f, 10.f);
    //    EM.addTag<TInteract>(door);
    //    EM.addTag<TWall>    (door);
    //    EM.addTag<TDoor>    (door);
    //    return door;
    //}
    //
    //Enty& createKey(float x_pos, float z_pos, TheEngine& dev) {
    //    Enty& key = EM.createEntity();
    //    EM.addComponent<PhysicsCmp2>(key, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
    //    EM.addComponent<RenderCmp2> (key, dev.createModel("assets/models/otros/enemy.obj","assets/textures/portal1.bmp"));
    //    EM.addComponent<EstadoCmp>  (key, 10.f, 10.f, 10.f);
    //    EM.addTag<TInteract>(key);
    //    EM.addTag<TKey>     (key);
    //    return key;
    //}

    void createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth, TheEngine& dev) {
        Enty& wall = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(wall, pos_x, pos_y,  pos_z);
        EM.addComponent<EstadoCmp>  (wall, width, height, depth);
        //EM.addComponent<RenderCmp2> (wall, dev.createModel("assets/models/otros/enemy.obj","assets/textures/fire.bmp"));
        EM.addTag      <TInteract>  (wall);
        EM.addTag      <TWall>      (wall);
    }

    void createShotgunBullets(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
    int const dmg, float const spd, float const rad, double const slfD, uint8_t dispersion) {
        for(uint8_t i = 0; i < 10; i++) {
            double ang_alp = randAng(dispersion);
            double ang_bet = randAng(dispersion);
            createBullet(phy_player, eng, SS, dmg, spd, rad, slfD, ang_alp, ang_bet);
        }
    }

    void createBullet(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
    int const dmg, float const spd, float const rad, double const slfD,
    double const pbx = 0, double const pby = 0) {
        Enty& bullet = EM.createEntity();
        EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{ .damage = dmg, .speed = spd, .bulletRad = rad });
        EM.addComponent<PhysicsCmp2>(
        bullet, PhysicsCmp2{
                .x = phy_player.x,
                .y = phy_player.y,
                .z = phy_player.z,
                .vx=  sin(phy_player.orieny + pby) * cos(phy_player.orienx + pbx) * spd,
                .vy= -sin(phy_player.orienx + pbx) * spd,
                .vz=  cos(phy_player.orieny + pby) * cos(phy_player.orienx + pbx) * spd
            }
        );
        EM.addComponent<RenderCmp2> (bullet, eng.createSphere(rad));
        EM.addComponent<EstadoCmp>  (bullet);
        EM.addComponent<SoundCmp>   (bullet, SoundCmp{.programmerSoundContext=SS.createinstance(1), .parametro=2, .play=true, .cambia=true});
        EM.addComponent<SelfDestCmp>(bullet, slfD);
        EM.addTag<TBullet>          (bullet);
        EM.addTag<TInteract>        (bullet);
    }

    void resetLevel(TheEngine& dev) {
        const wchar_t* empty = L"";
        dev.changeTextFromPointer(amm1, empty);
        dev.changeTextFromPointer(mag, empty);
        dev.changeTextFromPointer(h1, empty);

        EM.forall(
            [](Enty& ent) {
                bool is_enemy_bullet_or_player = 
                    ent.hasTAG<TEnemy>()  ||
                    ent.hasTAG<TBullet>() ||
                    ent.hasTAG<TPlayer>();
                if(is_enemy_bullet_or_player) ent.setDestroy();
            }
        );

        dev.setInvisibleImage(hit1);
        dev.setInvisibleImage(hit2);
        dev.setInvisibleImage(hit3);

        EM.callDestroy();
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

    double randAng(uint8_t ang) {
        float alpha = rand() % ang - (ang/2);
        return alpha * irr::core::PI / 180;
    }

    EntyMan EM;

    //Waves
    int    waveNumber           = 1; //actual wave
    double extraHeal            = 5; //extra EnemyHeal per wave
    int    numberOfEnemysBasics = 2; //number of enemys per wave
    int    aliveEnemys          = 0;
    double extraEnemys          = 2; //extra number of enemys per wave
    int    maxEnemysWave        = 5; //max number of enemy created
    double timeBtwWaves         = 4;
    double clockToNextWave      = 0; //clock unter next wave
    bool   inRound              = false;


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
    
    int activateHit {0};
    
    double cd1 {0}, cd2 {0}, cd3 {0};
    double clockHit1 {}, clockHit2 {}, clockHit3 {};
    TheEngine::IGUIImage* hit1 {};
    TheEngine::IGUIImage* hit2 {};
    TheEngine::IGUIImage* hit3 {};

};