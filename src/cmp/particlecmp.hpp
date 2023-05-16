#pragma once

#include <cstdint>
#include <vector>
struct EGenParticle;

struct ParticleCMP {

    EGenParticle* generator_;
    std::string textureName_ {"assets/textures/material_pasillo_1.png"};
    uint8_t maxParticles_ {20};
    uint8_t particlesForSpawn_ {1};

    float ellapsedTime_{0.f};
    float spawnTime_ {.2f};

    float life_ {1.0f};

    std::vector<float> velocityDirection_ {1.f, 1.f, 1.f};
    float dotVelocity_ {1.0f};

    float rotation_ {0.f};
    float scale_ {1.f};
    float gravity_ {0.f};
};
