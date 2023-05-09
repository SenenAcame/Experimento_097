#pragma once
#include "../util/types.hpp"

struct SoundSystem_t;
//struct TheEngine;

struct SpawnSystem {
    using SYSCMPs = MP::Typelist<SpawnCmp>;
    using SYSTAGs = MP::Typelist<TSpawn>;

    //void update(EntyMan& EM, TheEngine& eng, SoundSystem_t& ss, Enty& player, Enty& map);
    //void activeRespawn(Enty& player, Enty& spawn, Enty& map, EntyMan& EM);
    //void createEnemy(size_t type, EntyMan& EM, TheEngine& eng, SoundSystem_t& ss, SpawnCmp& spwCMP, Enty& spwEnty);
};