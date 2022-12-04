#pragma once
#include "../man/entitymanager.hpp"

struct PhysicsSystem {
    void update(EntityManager<Entity>& EM);
};