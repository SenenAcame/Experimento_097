#pragma once
#include "../util/types.hpp"
#include "../util/waves_aux.hpp"

struct SoundSystem_t;
struct LevelMan;
struct GraphicEngine;

struct SpawnSystem {
    using VOICMPs = MP::Typelist<>;
    using ENETAGs = MP::Typelist<TEnemy>;

    using SYSCMPs = MP::Typelist<SpawnCmp, PhysicsCmp2, SalaCmp>;
    using SYSTAGs = MP::Typelist<TSpawn>;

    using WPNTAGs = MP::Typelist<TWeapon>;

    void update(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, size_t player_ID, double const dt);
    
private:
    void updateAliveEnem(EntyMan& EM);
    void updateSpawnEnem(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, size_t player_ID, double const dt);
    void updateWave(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt);
    
    CuantityEnemies refill(CuantityEnemies type);
    void aumentDifficult();
    void spawnProcess(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, SpawnCmp& spawn, PhysicsCmp2& phy);
    void nextWave();
    void spawnWeapons(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys);
    
    ExtraStats   difficult {};
    WaveInfo     wave      {};
    WavesProgres progres   {};
};