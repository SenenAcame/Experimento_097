#pragma once
#include "../man/entitymanager.hpp"
#include "physicsystem.hpp"

struct CollisionSystem {
    explicit CollisionSystem() = default;
    void update(EntityManager<Entity>& EM);
};