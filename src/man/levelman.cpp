#include "levelman.hpp"
#include "../sys/nodemapsys.hpp"
#include "../sys/soundsystem.hpp"
#include <cstddef>

void LevelMan::update(TheEngine& dev, SoundSystem_t& SouSys, double const dt, std::size_t player_ID) {
    //EM.foreach<voidCMP, EneTAGs>(
    //    [&](Enty& en, PhysicsCmp2&) {
    //        if(en.getDestroy()) createBasicEnemy(-30, 30, dev, SouSys);
    //    }
    //);
    //cleanHitsInterface(dev, dt);
    EM.foreach<voidCMP, EneTAGs>(
            [&](Enty& en, PhysicsCmp2&) {
                if(en.getDestroy()) {
                    points+=5;
                    updateInterfacePoints(dev);
                    aliveEnemys--;
                }
                //createBasicEnemy(-30, 30, dev, SouSys)
            }
        );
    //for weapons only
    EM.foreach<voidCMP3, EneTAGs3>(
        [&](Enty& en, WeaponCmp& weaponCM) {
            auto& weaponRender = EM.getComponent<RenderCmp2>(en);
            if(weaponRender.n->isVisible() == true){return;}
            weaponCM.clockForAmmo+=dt;
            if(weaponCM.clockForAmmo <= weaponCM.AmmoSpawn){return;} 
            weaponCM.clockForAmmo = 0;
            weaponRender.n->setVisible(true);
        }
    );

    double spawnX{0}, spawnZ{0};
    auto& player = EM.getEntityById(player_ID);
    
    EM.foreach<voidCMP2, EneTAGs2>(
        [&](Enty&, PhysicsCmp2& f, SalaCmp& salaSpawn, SpawnCmp& spawnCMP) {
            spawnCMP.clockSpawn+=dt;
            
            if(inRound == true && numberOfEnemysBasics > 0 && aliveEnemys < maxEnemysWave) {
                if(spawnCMP.clockSpawn <= spawnCMP.SpawnTimer){return;} 
                
                auto salaPlayer = EM.getComponent<SalaCmp>(player).sala;
                
                auto nextSalaPlayer = (salaPlayer)%9+1;
                auto prevSalaPlayer = salaPlayer-1;
                if( prevSalaPlayer < 1){
                    prevSalaPlayer = 9;
                }
                
                if(salaPlayer!= salaSpawn.sala && nextSalaPlayer!=salaSpawn.sala && prevSalaPlayer != salaSpawn.sala){
                    spawnCMP.clockSpawn = 0;                 
                    spawnX = f.x;
                    spawnZ = f.z;
                    createBasicEnemy(static_cast<float>(spawnX), static_cast<float>(spawnZ), dev, SouSys, extraHeal, waveNumber);
                    aliveEnemys++;
                    numberOfEnemysBasics--;
                    
                }
            }  
        }
    );
    if(inRound == true && numberOfEnemysBasics == 0 && aliveEnemys == 0){
        inRound = false;
        //std::cout<<"NOT In round: "<<inRound<<"\n";
    }
    else if(inRound == false){
        clockToNextWave += dt;
        //std::cout<<"Clock To next wave: "<<clockToNextWave<<"\n";
        if(clockToNextWave >= timeBtwWaves) {
            inRound = true;
            clockToNextWave = 0;
            if(extraSpeed < 31) {
                extraSpeed += 4.5f;
            }
            numberOfEnemysBasics = 2 + extraEnemys * waveNumber;
            waveNumber++;
            updateInterfaceWave(dev);
            std::string  aux        = std::to_string(100);
            std::wstring convert    = std::wstring(aux.begin(), aux.end());
            const wchar_t* HPText   = convert.c_str();
            dev.changeTextFromPointer(h1, HPText);
            
            //std::cout<<"Enemys this round: "<<numberOfEnemysBasics<<"\n";
            //std::cout<<"In round: "<<inRound<<"\n";
        }
    }
    
    //else if(inRound == true){ //only to debug without interface
    //    std::cout<<"Max Enemys Wave: "<<maxEnemysWave<<"\n";
    //    std::cout<<"Alive enemys: "<<aliveEnemys<<"\n";
    //    std::cout<<"Enemys this round: "<<numberOfEnemysBasics<<"\n";
    //    std::cout<<"Wave: "<<waveNumber<<"\n";
    //}
    
    cleanHitsInterface(dev, dt);
}

Enty& LevelMan::init_level(TheEngine& dev, SoundSystem_t& SouSys) {
    auto& player = createPlayer(dev, SouSys);
    initInterface(dev, player);
    createSpawn(80, 30, 1);
    createWeapon(110, 5, 70, dev, SouSys, 1);
    createSpawn(-8, 8, 4);
    createWeapon(-65, 5, 30, dev, SouSys, 0);
    createSpawn(35, -30, 7);
    createWeapon(40, 5, -70, dev, SouSys, 2);
    inRound = true;
    //createBasicEnemy(110, 60, dev, SouSys);
    //createBasicEnemy(120, 60, dev, SouSys);
    //createBasicEnemy(110, 70, dev, SouSys);
    //createBasicEnemy(35, -60, dev, SouSys);
    //createBasicEnemy(45, -60, dev, SouSys);
    //createBasicEnemy(35, -70, dev, SouSys);
    return player;
}

void LevelMan::initMenu(TheEngine &dev) {
    Gui imgui = dev.getGuienv();

    dev.SetFont("assets/Interface/Font/chill.xml");
    menu_init = dev.addImageToPositionInScreen("assets/pantalla_controles_2.png", dev.getWidth()/2, dev.getHeight()/2);
    
    start = imgui->addButton({ 100, 100, 400, 200 });
    start->setText(L"Comenzar");
    //start->setVisible(true);

    exit = imgui->addButton({ 100, 200, 400, 300 });
    exit->setText(L"Salir");
    //exit->setVisible(true);
}

void LevelMan::initInterface (TheEngine& dev, Enty& player) {
    //Magazine
    auto equipment = EM.getComponent<InventarioCmp> (player);
    //auto stats = EM.getComponent<EstadisticaCmp> (player);
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
    //amos
    updateInterfaceWhenReload(dev, magazine, ammo);
    //HP
    updateInterfaceHP(dev, player);
    //wave
    updateInterfaceWave(dev);
    //points
    updateInterfacePoints(dev);
}

//void LevelMan::createInterface (TheEngine& dev, Enty& player) {
//    auto heightScreen  = dev.getHeight();
//    auto widthScreen   = dev.getWidth();
//    auto widthNumbers  = heightScreen - 100;
//    auto widthNumbers2 = heightScreen - 20;
//    //hits
//    hit1 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png", widthScreen/2-200, heightScreen/2-100);
//    dev.setInvisibleImage(hit1);
//    hit2 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png", widthScreen/2+200, heightScreen/2);
//    dev.setInvisibleImage(hit2);
//    hit3 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png", widthScreen/2, heightScreen/2+100);
//    dev.setInvisibleImage(hit3);
//
//    //Magazine
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
//
//    std::string aux = std::to_string(magazine);
//    std::wstring convert = std::wstring(aux.begin(), aux.end());
//    const wchar_t* magText = convert.c_str();
//    mag = dev.addTextToPositionInScreen(magText, widthScreen/10*8,widthNumbers,widthScreen/10*9,widthNumbers2);
//    //total ammo
//    aux = std::to_string(ammo);
//    convert = std::wstring(aux.begin(), aux.end());
//    const wchar_t* ammText = convert.c_str();
//    amm1 = dev.addTextToPositionInScreen(ammText,widthScreen/10*9,widthNumbers,widthScreen,widthNumbers2);
//    separacion = dev.addTextToPositionInScreen(L"/",widthScreen/10*8.5,widthNumbers,widthScreen,widthNumbers2);
//    //HP
//    aux = std::to_string(stats.hitpoints);
//    convert = std::wstring(aux.begin(), aux.end());
//    const wchar_t* HPText = convert.c_str();
//    hp =  dev.addTextToPositionInScreen(L"VIDA:",0,widthNumbers,widthScreen/10*2,widthNumbers2);
//    h1 =  dev.addTextToPositionInScreen(HPText,widthScreen/10,widthNumbers,widthScreen/10*2,widthNumbers2);
//    //mira
//    mir = dev.addImageToPositionInScreen("assets/Interface/1280x720/mira.png", widthScreen/2, heightScreen/2);
//}

void LevelMan::createEmptyInterface (TheEngine& dev) {
    auto hSrcn  = dev.getHeight();
    auto wScrn  = dev.getWidth();
    auto wNmb   = hSrcn - 100;
    auto wNmb2  = hSrcn - 20;

    //hits
    hit1 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png",wScrn/2-200,hSrcn/2-100);
    dev.setInvisibleImage(hit1);

    hit2 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png",wScrn/2+200,hSrcn/2);
    dev.setInvisibleImage(hit2);
    
    hit3 = dev.addImageToPositionInScreen("assets/Interface/1280x720/zarpazo.png",wScrn/2,hSrcn/2+100);
    dev.setInvisibleImage(hit3);

    mag = dev.addTextToPositionInScreen(L"", wScrn/10*8,wNmb,wScrn/10*9,wNmb2);
    //mag  = dev.addImageToPositionInScreen("assets/Interface/1280x720/cinco.png", 200,460);
    //std::cout<< "MAG ES " << mag <<"\n";

    //total ammo
    amm1       = dev.addTextToPositionInScreen(L"",  wScrn/10*9,                     wNmb, wScrn, wNmb2);
    separacion = dev.addTextToPositionInScreen(L"/", static_cast<int>(wScrn/10*8.5), wNmb, wScrn, wNmb2);

    //HP
    hp         = dev.addTextToPositionInScreen(L"VIDA:", 0,                              wNmb, wScrn/10*2,                     wNmb2);
    h1         = dev.addTextToPositionInScreen(L"",      static_cast<int>(wScrn/10*1.2), wNmb, static_cast<int>(wScrn/10*2.5), wNmb2);

    //wave
    waveText   = dev.addTextToPositionInScreen(L"Wave:",0,        wNmb-100, wScrn/10*2, wNmb2);
    wave       = dev.addTextToPositionInScreen(L"",     wScrn/10, wNmb-100, wScrn/10*2, wNmb2);

    //points
    pointsUI   = dev.addTextToPositionInScreen(L"",        wScrn/10*9,                      wNmb-100, wScrn,      wNmb2);
    pointsText = dev.addTextToPositionInScreen(L"Points:", static_cast<int>(wScrn/10*7.85), wNmb-100, wScrn/10*9, wNmb2);

    //mira
    mir = dev.addImageToPositionInScreen("assets/Interface/1280x720/mira_2.png", wScrn/2, hSrcn/2+29);
}

void LevelMan::updateInterfaceMag(TheEngine& dev, int maga) {
    std::string aux = std::to_string(maga);
    std::wstring convert = std::wstring(aux.begin(), aux.end());
    const wchar_t* magText= convert.c_str();
    dev.changeTextFromPointer(mag, magText);
}

void LevelMan::updateInterfacePoints(TheEngine& dev) {
    std::string aux = std::to_string(points);
    std::wstring convert = std::wstring(aux.begin(), aux.end());
    const wchar_t* points2= convert.c_str();
    dev.changeTextFromPointer(pointsUI, points2);
}

void LevelMan::updateInterfaceWave(TheEngine& dev) {
    std::string aux = std::to_string(waveNumber);
    std::wstring convert = std::wstring(aux.begin(), aux.end());
    const wchar_t* wave2= convert.c_str();
    dev.changeTextFromPointer(wave, wave2);
}

void LevelMan::updateInterfaceWhenReload(TheEngine& dev, int maga, int amm) {
    std::string aux = std::to_string(maga);
    std::wstring convert = std::wstring(aux.begin(), aux.end());
    const wchar_t* magText = convert.c_str();
    dev.changeTextFromPointer(mag, magText);

    aux = std::to_string(amm);
    convert = std::wstring(aux.begin(), aux.end());
    const wchar_t* ammText = convert.c_str();
    dev.changeTextFromPointer(amm1, ammText);
}

void LevelMan::updateInterfaceHP(TheEngine& dev, Enty&player){
    auto stats        = EM.getComponent<EstadisticaCmp>(player);
    std::string  aux        = std::to_string(stats.hitpoints);
    std::wstring convert    = std::wstring(aux.begin(), aux.end());
    const wchar_t* HPText   = convert.c_str();
    dev.changeTextFromPointer(h1, HPText);
}

void LevelMan::updateInterfaceHit(TheEngine& dev, Enty& player) {
    updateInterfaceHP(dev, player);
    
    int random = activateHit;
    while(activateHit==random)
        random = rand()%3+1;

    activateHit = random;
    
    switch (activateHit) {
        case 1: cd1 = 1;
            dev.setVisibleImage(hit1);
        break;
        case 2: cd2 = 1;
            dev.setVisibleImage(hit2);
        break;
        case 3: cd3 = 1;
            dev.setVisibleImage(hit3);
        break;
    }
}

void LevelMan::cleanHitsInterface(TheEngine& dev ,double dt) {
    if(cd1 == 1) {
        clockHit1 += dt;
        if(clockHit1 >= cd1) {
            dev.setInvisibleImage(hit1);
            clockHit1 = 0;
            cd1 = 0;
        }
    }
    if(cd2 ==1) {
        clockHit2 += dt;
        if(clockHit2 >= cd2) {
            dev.setInvisibleImage(hit2);
            clockHit2 = 0;
            cd2 = 0;
        }
    }
    if(cd3 ==1) {
        clockHit3 += dt;
        if(clockHit3 >= cd3) {
            dev.setInvisibleImage(hit3);
            clockHit3 = 0;
            cd3 = 0;
        }
    }
}

void LevelMan::createMap(TheEngine& dev, SoundSystem_t& SouSys) {
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

Enty& LevelMan::createPlayer(TheEngine& dev, SoundSystem_t& SouSys) {
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

Enty& LevelMan::createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, int extraHeal, int waveNumber) {
    Enty& enemy = createEnemy(SouSys);
    auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=20+extraHeal*waveNumber, .damage=20, .speed=15.f+extraSpeed});
    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
    EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo2.obj","assets/textures/portal1.bmp"));
    //EM.addComponent<EstadoCmp>  (enemy, 0.945f, 4.005f, 1.01f);
    EM.addComponent<EstadoCmp>  (enemy, 1.01f, 4.005f, 1.01f);
    return enemy;
}

//Enty& LevelMan::createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
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
//Enty& LevelMan::createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
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
//Enty& LevelMan::createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
//    Enty& enemy = createEnemy(SouSys);
//    auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=1.5f});
//
//    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=4.055, .z=z_pos, .kMxVLin = stats.speed});
//    EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/personajes/monstruo3.obj","assets/textures/faerie2.bmp"));
//    EM.addComponent<EstadoCmp>  (enemy, 1.525f, 5.725f, 2.105f);
//    EM.addTag      <TTankEnemy> (enemy);
//    return enemy;
//}

Enty& LevelMan::createWeapon(float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, size_t tipo) {
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

//Enty& LevelMan::createDoor(float x_pos, float z_pos, TheEngine& dev) {
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
//Enty& LevelMan::createKey(float x_pos, float z_pos, TheEngine& dev) {
//    Enty& key = EM.createEntity();
//    EM.addComponent<PhysicsCmp2>(key, PhysicsCmp2{.x=x_pos, .y=5, .z=z_pos});
//    EM.addComponent<RenderCmp2> (key, dev.createModel("assets/models/otros/enemy.obj","assets/textures/portal1.bmp"));
//    EM.addComponent<EstadoCmp>  (key, 10.f, 10.f, 10.f);
//    EM.addTag<TInteract>(key);
//    EM.addTag<TKey>     (key);
//    return key;
//}

void LevelMan::createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth, TheEngine& /*dev*/) {
    Enty& wall = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(wall, pos_x, pos_y,  pos_z);
    EM.addComponent<EstadoCmp>  (wall, width, height, depth);
    //EM.addComponent<RenderCmp2> (wall, dev.createModel("assets/models/otros/enemy.obj","assets/textures/fire.bmp"));
    EM.addTag<TInteract>(wall);
    EM.addTag<TWall>    (wall);
}

Enty& LevelMan::createSpawn(float x_pos, float z_pos, int sala2){
    Enty& spawn = EM.createEntity();
    EM.addComponent<SalaCmp>    (spawn, SalaCmp{.sala = sala2});
    EM.addComponent<PhysicsCmp2>(spawn, PhysicsCmp2{.x=x_pos, .z=z_pos});
    EM.addComponent<SpawnCmp>   (spawn);
    EM.addTag      <TSpawn>     (spawn);
    //EM.addComponent<EstadoCmp>  (spawn, EstadoCmp{.width = 2, .height = 9, .depth = 2});
    return spawn;
}

void LevelMan::createShotgunBullets(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
int const dmg, float const spd, float const rad, double const slfD, uint8_t dispersion) {
    for(uint8_t i = 0; i < 10; i++) {
        double ang_alp = randAng(dispersion);
        double ang_bet = randAng(dispersion);
        createBullet(phy_player, eng, SS, dmg, spd, rad, slfD, ang_alp, ang_bet);
    }
}

void LevelMan::createBullet(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
int const dmg, float const spd, float const rad, double const slfD,
double const pbx, double const pby) {
    Enty& bullet = EM.createEntity();
    EM.addComponent<EstadisticaCmp>(bullet, EstadisticaCmp{ .damage = dmg, .speed = spd, .bulletRad = rad });
    EM.addComponent<PhysicsCmp2>(
        bullet, PhysicsCmp2 {
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

void LevelMan::resetLevel(TheEngine& dev) {
    const wchar_t* empty = L"";
    dev.changeTextFromPointer(amm1, empty);
    dev.changeTextFromPointer(mag, empty);
    dev.changeTextFromPointer(h1, empty);
    dev.changeTextFromPointer(pointsUI, empty);
    dev.changeTextFromPointer(wave, empty);

    mag->setVisible(false);
    hp->setVisible(false);
    separacion->setVisible(false);
    wave->setVisible(false);
    waveText->setVisible(false);
    pointsUI->setVisible(false);
    pointsText->setVisible(false);
    dev.setInvisibleImage(mir);

    EM.forall(
        [](Enty& ent) {
            //bool is_enemy_bullet_or_player = 
            //    ent.hasTAG<TEnemy>()  ||
            //    ent.hasTAG<TBullet>() ||
            //    ent.hasTAG<TWeapon>() ||
            //    ent.hasTAG<TSpawn>()  ||
            //    ent.hasTAG<TPlayer>();
            //if(is_enemy_bullet_or_player) ent.setDestroy();
            ent.setDestroy();
        }
    );

    dev.setInvisibleImage(hit1);
    dev.setInvisibleImage(hit2);
    dev.setInvisibleImage(hit3);

    waveNumber           = 1; //actual wave
    extraHeal            = 5; //extra EnemyHeal per wave
    extraSpeed           = 0;
    numberOfEnemysBasics = 2; //number of enemys per wave
    aliveEnemys          = 0;
    extraEnemys          = 3; //extra number of enemys per wave
    maxEnemysWave        = 15; //max number of enemy created
    timeBtwWaves         = 2;
    clockToNextWave      = 0; //clock unter next wave
    inRound              = false;
    points               = 0;

    updateInterfacePoints(dev);
    updateInterfaceWave(dev);   

    EM.callDestroy();
}

void LevelMan::setVisibleMenu(TheEngine& dev) {
    //menu_init = dev.addImageToPositionInScreen("assets/pantalla_controles_2.png", dev.getWidth()/2, dev.getHeight()/2);
    dev.setVisibleImage(menu_init);
    start->setVisible(true);
    exit->setVisible(true);
}

void LevelMan::setInvisibleMenu(TheEngine& dev) {
    dev.setInvisibleImage(menu_init);
    start->setVisible(false);
    exit->setVisible(false);
}

void LevelMan::createSoundEffect(SoundSystem_t& SouSys) {
    Enty& weapon = EM.createEntity();
    EM.addComponent<SoundCmp>(weapon, SouSys.createinstance(1));
    EM.addTag<TWeapon>(weapon);
    return;
}

Enty& LevelMan::createEnemy(SoundSystem_t& SouSys){
    Enty& enemy = EM.createEntity();
    defineAI(enemy);
    EM.addComponent<SoundCmp> (enemy, SouSys.createinstance(7));
    EM.addComponent<SalaCmp>  (enemy);
    EM.addTag      <TEnemy>   (enemy);
    EM.addTag      <TInteract>(enemy);
    return enemy;
}

void LevelMan::createRoom(TheEngine& dev, irr::io::path const model, irr::io::path const texture) {
    Enty& room = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(room);
    EM.addComponent<RenderCmp2> (room, dev.createModel(model, texture));
}

void LevelMan::defineAI(Enty& enemy) {
    float  num    = static_cast<float>(rand() % 360);
    double angle  = num * irr::core::PI / 180;
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

double LevelMan::randAng(uint8_t ang) {
    double alpha = rand() % ang - (ang/2);
    return alpha * irr::core::PI / 180;
}