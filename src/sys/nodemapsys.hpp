#pragma once
#include "../util/types.hpp"
#include <vector>
#include <algorithm>

struct NodeMapSys {
    using EneCMPs       = MP::Typelist<PhysicsCmp2, AICmp>;
    using PlayCMPs      = MP::Typelist<PhysicsCmp2>;
    using PlayTAGs      = MP::Typelist<TPlayer>;
    using NodoCMPs      = MP::Typelist<NodoCmp>;
    using MapTAGs       = MP::Typelist<TMap>;
    using MapTAGsSpawns = MP::Typelist<TSpawn>;
    using EneTAGs       = MP::Typelist<TEnemy>;

    int getSala(NodoCmp& map, float x, float z);
    void update(EntyMan& EM);
    std::vector<sala> static creaSalas();
};