#pragma once
#include "../cmp/entity.hpp"
#include <vector>

struct GameContext{

    virtual const std::vector<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>>& getEntities() const = 0;
    virtual std::vector<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>>& getEntities() = 0;
};