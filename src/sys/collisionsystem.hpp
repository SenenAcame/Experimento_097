#pragma once
#include "../man/entitymanager.hpp"

struct CollisionSystem {
    explicit CollisionSystem() = default;
    void update(EntityManager<Entity>& EM);
};