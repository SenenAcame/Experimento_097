#pragma once
#include "../man/entitymanager.hpp"
#include "../eng/engine.hpp"

struct RenderSystem {
    explicit RenderSystem() = default;
    void update(EntityManager<Entity>& EM, TheEngine& GFX);
};