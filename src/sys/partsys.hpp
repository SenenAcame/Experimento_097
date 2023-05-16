#pragma once

#include "../util/types.hpp"
#include <cstdint>
#include <string>
#include <vector>

struct ParticleCMP;
struct GlEngine;

struct PartSys {

    using SYSCMPs = MP::Typelist<PhysicsCmp2, ParticleCMP>;
    using SYSTAGs = MP::Typelist<>;
    
    explicit PartSys() = default;

    bool update(EntyMan &EM, const float dt) const;

    //set particle component
    void setParticle(ParticleCMP& parcmp, std::string textureName = "assets/textures", uint8_t maxParticles = 20, uint8_t particlesForSpawn = 1, float spawnTime = .2f, float life = 1.0f, std::vector<float> velocityDirection = {1.f, 1.f, 1.f}, float dotVelocity = 1.f, float rotation = 0.f, float scale = 1.f, float gravity = 0.f);

    void setEngine(GlEngine *engine) {
        engine_ = engine;
    }

    GlEngine *engine_ = nullptr;
};