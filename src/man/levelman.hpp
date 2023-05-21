#pragma once
#include "../util/types.hpp"
#include "../util/waves_aux.hpp"
#include "../util/structs_aux.hpp"
#include <cstddef>
#include <numbers>

struct SoundSystem_t;
struct GraphicEngine;
struct PartSys;

struct LevelMan {
    using voidCMP = MP::Typelist<PhysicsCmp2>;
    using EneTAGs = MP::Typelist<TEnemy>;
    using voidCMP2 = MP::Typelist<PhysicsCmp2, SalaCmp, SpawnCmp>;
    using EneTAGs2 = MP::Typelist<TSpawn>;
    using voidCMP3 = MP::Typelist<WeaponCmp>;
    using EneTAGs3 = MP::Typelist<TWeapon>;

    static constexpr auto PI { std::numbers::pi };

    void update(SoundSystem_t& SouSys, double const dt, Enty& player);

    /*NUEVO*/ size_t createMap2(GraphicEngine& GE, SoundSystem_t& SouSys);

    /*NUEVO*/ size_t createPlayer2(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys);

    /*NUEVO*/ Enty&  createEnemy(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, Type_Enemy type, ExtraStats plus = {1,1,1});

    /*NUEVO*/ Enty&  createNormalEnemy  (GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus = {1,1,1});
    /*NUEVO*/ Enty&  createDistanceEnemy(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus = {1,1,1});
    /*NUEVO*/ Enty&  createTankEnemy    (GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus = {1,1,1});

    /*NUEVO*/ Enty&  createNormalEnemyAnim  (GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus = {1,1,1});
    /*NUEVO*/ Enty&  createDistanceEnemyAnim(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus = {1,1,1});
    /*NUEVO*/ Enty&  createTankEnemyAnim    (GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus = {1,1,1});

    /*NUEVO*/ void   createBullet2(GraphicEngine& GE, PhysicsCmp2& pos, EstadisticaCmp&& stats, 
        Vec3 dir, SoundSystem_t& SouSys, double const slfD = 2., double const pbx = 0, double const pby = 0);
    /*NUEVO*/ void   createShotgunBullets2(GraphicEngine& GE, PhysicsCmp2& pos, EstadisticaCmp&& stats, 
        Vec3 dir, SoundSystem_t& SouSys, double const slfD = 2., uint8_t dispersion = 10);
    /*NUEVO*/ void   createEneBullet(GraphicEngine& GE, PhysicsCmp2&& phy, int dmg);

    /*NUEVO*/ Enty&  createWeapon2(GraphicEngine& GE, Vec3 pos, W_Type tipo, SoundSystem_t& SouSys);

    /*NUEVO*/ void   createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth);
    /*NUEVO*/ TNodo* createModelHitbox(GraphicEngine& GE, Vec3 pos, Vec3 scale, TNodo* padre);

    /*NUEVO*/ void   viewBB(GraphicEngine& GE, Enty& ent);

    /*NUEVO*/ Enty&  createEneSpawn(Vec3 pos, GraphicEngine& GE, int room, double timer = 1);
    /*NUEVO*/ Enty&  createWpnSpawn(Vec3 pos, GraphicEngine& GE, int room, double timer = 1);
    /*NUEVO*/ Enty&  createSpawn2  (Vec3 pos, GraphicEngine& GE, int room, double timer = 1);

    Enty& createPowerUp(GraphicEngine& GE, PhysicsCmp2& phy);

    void resetLevel(std::size_t player_ID, GraphicEngine& GE, SoundSystem_t& SouSys);
    void resetBlackboard(size_t player_ID);
    EntyMan& getEM() { return EM; }

private:
    TwoAngles disperShotgun(uint8_t disp);
    TwoAngles normalize(TwoAngles angs);
    void      componentsPlayer(Enty& player, SoundSystem_t& SouSys);
    void      defineAI(Enty& enemy, SB patron, double cd);
    double    randAng(uint8_t ang);

    EntyMan EM;

    //void createSoundEffect(SoundSystem_t& SouSys);
    //Enty& createEnemy(SoundSystem_t& SouSys);
    //void createRoom(TheEngine& dev, irr::io::path const model, irr::io::path const texture);
    
    //Waves
    //double extraHeal            = 5; //extra EnemyHeal per wave
    //float  extraSpeed           = 0; //extra speed per round
    //int    waveNumber           = 1; //actual wave
    //int    numberOfEnemysBasics = 2; //number of enemys per wave
    //int    aliveEnemys          = 0;
    //double extraEnemys          = 3; //extra number of enemys per wave
    //int    maxEnemysWave        = 11; //max number of enemy created
    //double timeBtwWaves         = 4;
    //double clockToNextWave      = 0; //clock unter next wave
    //bool   inRound              = false;
    //int    points               = 0;

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