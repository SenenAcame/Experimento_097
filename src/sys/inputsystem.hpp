#pragma once
#include "../man/entitymanager.hpp"

struct InputSystem {
    explicit InputSystem() = default;
    void update(EntityManager<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>>& EM);
};