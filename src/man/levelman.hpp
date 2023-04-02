#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"

struct SoundSystem_t;

struct LevelMan {
    using voidCMP = MP::Typelist<PhysicsCmp2>;
    using EneTAGs = MP::Typelist<TEnemy>;

    void update(TheEngine& dev, SoundSystem_t& SouSys, double const dt);
    Enty& init_level(TheEngine& dev, SoundSystem_t& SouSys);
    void createInterface (TheEngine& dev, Enty& player);
    void updateInterfaceMag(TheEngine& dev, int maga);
    void updateInterfaceWhenReload(TheEngine& dev, int maga, int amm);
    void updateInterfaceHit(TheEngine& dev, Enty& player);
    void cleanHitsInterface(TheEngine& dev ,double dt);
    void createMap(TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createPlayer(TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createBasicEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createDistEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createTankEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys);
    Enty& createWeapon(float x_pos, float y_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys, size_t tipo);
    Enty& createDoor(float x_pos, float z_pos, TheEngine& dev);
    Enty& createKey(float x_pos, float z_pos, TheEngine& dev);
    void createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth, TheEngine& dev);
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

    //INTERFACE
    TheEngine::IGUIText* mag {};
    TheEngine::IGUIText* h1 {};
    TheEngine::IGUIText* hp {};
    TheEngine::IGUIText* amm1 {};
    TheEngine::IGUIText* separacion {};
    TheEngine::IGUIImage* mir {};
    TheEngine::IGUIImage* hit1 {};
    TheEngine::IGUIImage* hit2 {};
    TheEngine::IGUIImage* hit3 {};

    int activateHit { 0 };
    double cd1 { 0 }, cd2 { 0 }, cd3 { 0 };
    double clockHit1 {}, clockHit2 {}, clockHit3 {};
};