#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"

struct SoundSystem_t;

struct LevelMan {
    using voidCMP  = MP::Typelist<PhysicsCmp2>;
    using EneTAGs  = MP::Typelist<TEnemy>;
    using voidCMP2 = MP::Typelist<PhysicsCmp2, SalaCmp, SpawnCmp>;
    using EneTAGs2 = MP::Typelist<TSpawn>;
    using voidCMP3 = MP::Typelist<WeaponCmp>;
    using EneTAGs3 = MP::Typelist<TWeapon>;

    using Text   = TheEngine::IGUIText*;
    using Image  = TheEngine::IGUIImage*;
    using Gui    = TheEngine::IGUIEnvironment*;
    using Button = TheEngine::IGUIButton*;

    void  update(TheEngine& dev, SoundSystem_t& SouSys, double const dt, std::size_t player_ID) ;
    Enty& init_level(TheEngine& dev, SoundSystem_t& SouSys);
    void  initMenu(TheEngine& dev);
    void  initInterface (TheEngine& dev, Enty& player);
    //void createInterface (TheEngine& dev, Enty& player);
    void  createEmptyInterface (TheEngine& dev);

    void updateInterfaceMag(TheEngine& dev, int maga);
    void updateInterfacePoints(TheEngine& dev);
    void updateInterfaceWave(TheEngine& dev);
    void updateInterfaceWhenReload(TheEngine& dev, int maga, int amm);
    void updateInterfaceHP(TheEngine& dev, Enty&player);
    void updateInterfaceHit(TheEngine& dev, Enty& player);
    void cleanHitsInterface(TheEngine& dev ,double dt);

    void  createMap(TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createPlayer(TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, int extraHeal, int waveNumber);
    //Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    //Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    //Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    Enty&  createWeapon(float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, size_t tipo);
    //Enty& createDoor(float x_pos, float z_pos, TheEngine& dev);
    //Enty& createKey(float x_pos, float z_pos, TheEngine& dev);
    void  createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth, TheEngine& dev);
    Enty& createSpawn(float x_pos, float z_pos, int sala2);
    void  createShotgunBullets(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
        int const dmg, float const spd, float const rad, double const slfD, uint8_t dispersion);
    void  createBullet(PhysicsCmp2& phy_player, TheEngine& eng, SoundSystem_t& SS, 
        int const dmg, float const spd, float const rad, double const slfD,
        double const pbx = 0, double const pby = 0);
    void resetLevel(TheEngine& dev);

    void setVisibleMenu(TheEngine& dev);
    void setInvisibleMenu(TheEngine& dev);
    void setVisibleControls();
    void setInvisibleControls();

    bool isStartPressed() { return start->isPressed(); }
    bool isExitPressed()  { return exit->isPressed();  }

    EntyMan& getEM() { return EM; }

private:
    void   createSoundEffect(SoundSystem_t& SouSys);
    Enty&  createEnemy(SoundSystem_t& SouSys);
    void   createRoom(TheEngine& dev, irr::io::path const model, irr::io::path const texture);
    void   defineAI(Enty& enemy);
    double randAng(uint8_t ang);

    EntyMan EM;

    //Waves
    int    waveNumber           = 1; //actual wave
    int    numberOfEnemysBasics = 2; //number of enemys per wave
    int    aliveEnemys          = 0;
    int    maxEnemysWave        = 11; //max number of enemy created
    int    points               = 0;
    int    extraHeal            = 5; //extra EnemyHeal per wave
    int    extraEnemys          = 3; //extra number of enemys per wave
    float  extraSpeed           = 0; //extra speed per round
    double timeBtwWaves         = 4;
    double clockToNextWave      = 0; //clock unter next wave
    bool   inRound              = false;

    //INTERFACE
    Text mag  {}, h1 {}, hp {};
    Text amm1 {}, separacion {};
    Text wave {}, waveText   {};
    Text pointsUI {}, pointsText {};

    Image mir  {}, hit1 {};
    Image hit2 {}, hit3 {};
    Image menu_init {};
    Image controls {};

    Button start {};
    Button exit {};

    //Hits
    int activateHit {0};
    double cd1 {0}, cd2 {0}, cd3 {0};
    double clockHit1 {}, clockHit2 {}, clockHit3 {};
};