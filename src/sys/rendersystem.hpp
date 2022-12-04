#pragma once
#include "../man/entitymanager.hpp"
#include "../eng/engine.hpp"

struct RenderSystem {
    void update(EntityManager<Entity>& EM, TheEngine& GFX);
};