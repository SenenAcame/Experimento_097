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
    void updateAliveEnem(EntyMan& EM);
    void aumentDifficult();
    //void activeRespawn(Enty& player, Enty& spawn, Enty& map, EntyMan& EM);
    //void createEnemy(size_t type, EntyMan& EM, TheEngine& eng, SoundSystem_t& ss, SpawnCmp& spwCMP, Enty& spwEnty);

private:
    ExtraStats difficult {};
    WaveInfo   waves {};
};