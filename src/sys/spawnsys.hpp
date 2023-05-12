#pragma once
#include "../util/types.hpp"
#include "../util/waves_aux.hpp"

struct SoundSystem_t;
struct LevelMan;
struct GraphicEngine;

struct SpawnSystem {
    using ENECMPs = MP::Typelist<>;
    using ENETAGs = MP::Typelist<TEnemy>;

    using SYSCMPs = MP::Typelist<SpawnCmp, PhysicsCmp2>;
    using SYSTAGs = MP::Typelist<TSpawn>;

    void update(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, std::size_t player_ID, std::size_t map_ID, double const dt);
    
private:
    void updateAliveEnem(EntyMan& EM);
    void updateSpawnEnem(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, double const dt);
    void updateWave(double const dt);
    
    CuantityEnemies refill(CuantityEnemies type);
    void aumentDifficult();
    void spawnProcess(LevelMan& LM, GraphicEngine& GE, SoundSystem_t& SouSys, SpawnCmp& spawn, PhysicsCmp2& phy);
    void nextWave();
    
    ExtraStats   difficult {};
    WaveInfo     wave      {};
    WavesProgres progres   {};
};