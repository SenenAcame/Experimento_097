#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include "../sys/nodemapsys.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <irrlicht/IGUIImage.h>
#include <string>

struct SoundSystem_t;

struct LevelMan {
    using voidCMP = MP::Typelist<PhysicsCmp2>;
    using SYSCMP_Sound = MP::Typelist<SoundCmp>;
    using EneTAGs = MP::Typelist<TEnemy>;
    using voidCMP2 = MP::Typelist<PhysicsCmp2, SalaCmp, SpawnCmp>;
    using EneTAGs2 = MP::Typelist<TSpawn>;
    using voidCMP3 = MP::Typelist<WeaponCmp>;
    using EneTAGs3 = MP::Typelist<TWeapon>;
    using SYSTAG_Ronda = MP::Typelist<TRonda>;
    using SYSTAG_Pulso  = MP::Typelist<TPulso>;

    void update(TheEngine& dev, SoundSystem_t& SouSys, double const dt, Enty& player) ;
    Enty& init_level(TheEngine& dev, SoundSystem_t& SouSys);

    void initInterface (TheEngine& dev, Enty& player);
    //void createInterface (TheEngine& dev, Enty& player);
    void createEmptyInterface (TheEngine& dev);
    void updateInterfaceMag(TheEngine& dev, int maga);
    void updateInterfacePoints(TheEngine& dev);
    void updateInterfaceWave(TheEngine& dev);
    void updateInterfaceWhenReload(TheEngine& dev, int maga, int amm);
    void updateInterfaceHP(TheEngine& dev, Enty&player);
    void updateInterfaceHit(TheEngine& dev, Enty& player);
    void cleanHitsInterface(TheEngine& dev ,double dt);
    void notificationNewRound(TheEngine& dev);

    void passRound(TheEngine& dev, Enty& player);

    void createMap(TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createPlayer(TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, int extraHeal, int waveNumber);
    Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    //Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    //Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    //Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createWeapon(float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, size_t tipo);
    //Enty& createDoor(float x_pos, float z_pos, TheEngine& dev);
    //Enty& createKey(float x_pos, float z_pos, TheEngine& dev);
    void createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth, TheEngine& dev);
    Enty& createSpawn(float x_pos, float z_pos, TheEngine& dev, int sala2);
    void createShotgunBullets(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
        int const dmg, float const spd, float const rad, double const slfD, uint8_t dispersion);
    void createBullet(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
        int const dmg, float const spd, float const rad, double const slfD,
        double const pbx = 0, double const pby = 0);
    void resetLevel(TheEngine& dev);
    EntyMan& getEM() { return EM; }
private:
    void createSoundEffect(SoundSystem_t& SouSys);
    Enty& createEnemy(SoundSystem_t& SouSys);
    void createRoom(TheEngine& dev, irr::io::path const model, irr::io::path const texture);
    void defineAI(Enty& enemy);
    double randAng(uint8_t ang);

   EntyMan EM;

    //Waves
    int    waveNumber           = 1; //actual wave
    double extraHeal            = 5; //extra EnemyHeal per wave
    float  extraSpeed           = 0; //extra speed per round
    int    numberOfEnemysBasics = 2; //number of enemys per wave
    int    numberOfTankEnemys = 0;
    int    numberOfDistEnemys = 0;
    int    totalEnemys          = 2;
    int    aliveEnemys          = 0;
    double extraEnemys          = 3; //extra number of enemys per wave
    int    maxEnemysWave        = 11; //max number of enemy created
    double timeBtwWaves         = 4;
    double clockToNextWave      = 0; //clock unter next wave
    bool   inRound              = false;
    int    points               = 0;



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

    TheEngine::IGUIText*  wave {};
    TheEngine::IGUIText*  waveText {};

    TheEngine::IGUIText*  wave2 {};
    TheEngine::IGUIText*  waveText2 {};

    TheEngine::IGUIText*  pointsUI {};
    TheEngine::IGUIText*  pointsText {};

    //Hits

    int activateHit {0};

    double cd1 {0}, cd2 {0}, cd3 {0};
    double clockHit1 {}, clockHit2 {}, clockHit3 {};
    TheEngine::IGUIImage* hit1 {};
    TheEngine::IGUIImage* hit2 {};
    TheEngine::IGUIImage* hit3 {};
};