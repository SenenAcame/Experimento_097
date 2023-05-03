#pragma once
#include "../util/types.hpp"
#include <cstddef>

struct NodeMapSys {
    using EneCMPs       = MP::Typelist<PhysicsCmp2, AICmp>;
    using PlayCMPs      = MP::Typelist<PhysicsCmp2>;
    using PlayTAGs      = MP::Typelist<TPlayer>;
    using NodoCMPs      = MP::Typelist<NodoCmp>;
    using MapTAGs       = MP::Typelist<TMap>;
    using MapTAGsSpawns = MP::Typelist<TSpawn>;
    using EneTAGs       = MP::Typelist<TEnemy>;

    /*VIEJO*/ void update (EntyMan& EM);
    /*NUEVO*/ void update2(EntyMan& EM, std::size_t player_ID, std::size_t map_ID);
    
    int getSala(NodoCmp& map, float x, float z);
    std::vector<sala> static creaSalas();
};