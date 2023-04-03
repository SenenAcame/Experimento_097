#pragma once

#include "../particles/particle.hpp"
#include "../resources/RShader.hpp"
#include "../resources/RTexture.hpp"
#include <vector>

struct EGenParticle {

    EGenParticle(RShader *shader, RTexture *texture, unsigned int amount);

    void update(float dt);

    //gen new particles
    void genParticles(Vec3 objPos, Vec3 offset = Vec3(0.0f), Vec3 velocityDirection = Vec3(1.0f), float offsetVelocity = 1.0f, float rotation = 0.0f, float scale = 1.0f, float life = 1.0f, float gravity = 0.0f);

    //draw all particles
    void draw(Mat4 &view);

    void addParticle(unsigned int );

    // Variables___________________
    //_____________________________

    std::vector<Particle> particles;
    unsigned int amount{50};
    unsigned int newParticles{0};

    RShader  *shader{nullptr};
    RTexture *texture{nullptr};
    unsigned int VAO;

    void init();
    unsigned int firstUnusedParticle();

    void respawnParticle(Particle &particle, Vec3 objPos, Vec3 offset = Vec3(0.0f), Vec3 velocityDirection = Vec3(1.0f), float offsetVelocity = 1.0f, float rotation = 0.0f, float scale = 1.0f, float life = 1.0f, float gravity = 0.0f);
};