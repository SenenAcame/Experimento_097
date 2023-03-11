#pragma once
#include "../man/entitymanager.hpp"

struct PhysicsSystem {
    explicit PhysicsSystem() = default;
    void update(EntityManager<Entity>& EM);
};