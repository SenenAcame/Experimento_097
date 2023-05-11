#pragma once
#include "../util/types.hpp"
#include "../util/waves_aux.hpp"
//#include "../eng/engine.hpp"
#include <cstddef>
#include <numbers>

struct SoundSystem_t;
struct GraphicEngine;

struct TwoAngles {
    double alfa { 0 }, beta { 0 };
};

struct LevelMan {
    using voidCMP = MP::Typelist<PhysicsCmp2>;
    using EneTAGs = MP::Typelist<TEnemy>;
    using voidCMP2 = MP::Typelist<PhysicsCmp2, SalaCmp, SpawnCmp>;
    using EneTAGs2 = MP::Typelist<TSpawn>;
    using voidCMP3 = MP::Typelist<WeaponCmp>;
    using EneTAGs3 = MP::Typelist<TWeapon>;

    static constexpr auto PI { std::numbers::pi };

    //void update(TheEngine& dev, SoundSystem_t& SouSys, double const dt, Enty& player) ;
    //Enty& init_level(TheEngine& dev, SoundSystem_t& SouSys);
    //void initInterface (TheEngine& dev, Enty& player);
    ////void createInterface (TheEngine& dev, Enty& player);
    //void createEmptyInterface (TheEngine& dev);

    //void updateInterfaceMag(TheEngine& dev, int maga);
    //void updateInterfacePoints(TheEngine& dev);
    //void updateInterfaceWave(TheEngine& dev);
    //void updateInterfaceWhenReload(TheEngine& dev, int maga, int amm);
    //void updateInterfaceHP(TheEngine& dev, Enty&player);
    //void updateInterfaceHit(TheEngine& dev, Enty& player);

    //void cleanHitsInterface(TheEngine& dev ,double dt);

    ///*VIEJO*/ void createMap(TheEngine& dev, SoundSystem_t& SouSys);
    /*NUEVO*/ std::size_t createMap2(GraphicEngine& GE, SoundSystem_t& SouSys);

    ///*VIEJO*/ Enty& createPlayer(TheEngine& dev, SoundSystem_t& SouSys);
    /*NUEVO*/ std::size_t createPlayer2(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys);

    ///*VIEJO*/ Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, int extraHeal, int waveNumber);
    /*NUEVO*/ Enty& createNormalEnemy (GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus = {1,1,1});
    /*NUEVO*/ Enty& createDistanceEnemy(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys);

    ///*VIEJO*/ void createBullet(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
    //    int const dmg, float const spd, float const rad, double const slfD,
    //    double const pbx = 0, double const pby = 0);
    /*NUEVO*/ void createBullet2(GraphicEngine& GE, PhysicsCmp2& pos, EstadisticaCmp&& stats, 
        Vec3 dir, SoundSystem_t& SouSys, double const slfD = 2., double const pbx = 0, double const pby = 0);

    ///*VIEJO*/ void createShotgunBullets(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
    //    int const dmg, float const spd, float const rad, double const slfD, uint8_t dispersion);
    /*NUEVO*/ void createShotgunBullets2(GraphicEngine& GE, PhysicsCmp2& pos, EstadisticaCmp&& stats, 
        Vec3 dir, SoundSystem_t& SouSys, double const slfD = 2., uint8_t dispersion = 10);
        
    /*NUEVO*/ void createEneBullet(GraphicEngine& GE, PhysicsCmp2&& phy, int dmg);

    ///*VIEJO*/ Enty& createWeapon (float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, size_t tipo);
    /*NUEVO*/ Enty& createWeapon2(GraphicEngine& GE, Vec3 pos, W_Type tipo, SoundSystem_t& SouSys);
    
    void createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth);
    
    TNodo* createModelHitbox(GraphicEngine& GE, Vec3 pos, Vec3 scale, TNodo* padre);

    void viewBB(GraphicEngine& GE, Enty& ent);

    //Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    ///*VIEJO*/ Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    //Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    //Enty& createWeapon(float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, size_t tipo);
    //Enty& createDoor(float x_pos, float z_pos, TheEngine& dev);
    //Enty& createKey(float x_pos, float z_pos, TheEngine& dev);
    
    ///*VIEJO*/ Enty& createSpawn(float x_pos, float z_pos, TheEngine& dev, int sala2);
    /*NUEVO*/ Enty& createSpawn2(Vec3 pos, GraphicEngine& GE, int room);
    
    //void resetLevel(TheEngine& dev);
    EntyMan& getEM() { return EM; }
private:
    //void createSoundEffect(SoundSystem_t& SouSys);
    //Enty& createEnemy(SoundSystem_t& SouSys);
    //void createRoom(TheEngine& dev, irr::io::path const model, irr::io::path const texture);
    TwoAngles disperShotgun(uint8_t disp);
    TwoAngles normalize(TwoAngles angs);
    void defineAI(Enty& enemy, SB patron, double cd);
    double randAng(uint8_t ang);

    EntyMan EM;

    //Waves
    double extraHeal            = 5; //extra EnemyHeal per wave
    float  extraSpeed           = 0; //extra speed per round

    int    waveNumber           = 1; //actual wave

    int    numberOfEnemysBasics = 2; //number of enemys per wave
    int    aliveEnemys          = 0;
    double extraEnemys          = 3; //extra number of enemys per wave
    int    maxEnemysWave        = 11; //max number of enemy created
    
    double timeBtwWaves         = 4;
    double clockToNextWave      = 0; //clock unter next wave

    bool   inRound              = false;
    
    int    points               = 0;

    //INTERFACE
    //TheEngine::IGUIText*  mag  {};
    ////wchar_t*        magText{};
    //TheEngine::IGUIText*  h1   {};
    //TheEngine::IGUIText*  hp   {};
    ////wchar_t*        HPText{};
    //TheEngine::IGUIText*  amm1 {};
    //TheEngine::IGUIText*  separacion {};
    ////wchar_t*        ammText{};
    //TheEngine::IGUIImage* mir  {};
    //TheEngine::IGUIText*  wave {};
    //TheEngine::IGUIText*  waveText {};
    //TheEngine::IGUIText*  pointsUI {};
    //TheEngine::IGUIText*  pointsText {};

    //Hits
    int activateHit {0};
    double cd1 {0}, cd2 {0}, cd3 {0};
    double clockHit1 {}, clockHit2 {}, clockHit3 {};
    //TheEngine::IGUIImage* hit1 {};
    //TheEngine::IGUIImage* hit2 {};
    //TheEngine::IGUIImage* hit3 {};
};