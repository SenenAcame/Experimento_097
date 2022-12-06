#pragma once
#include "physicscomponent.hpp"
#include "rendercomponent.hpp"
#include "inputcomponent.hpp"
#include "collisioncomponent.hpp"
#include <cstddef>

struct Entity {
    explicit Entity() = default;

    PhysicsComponent*   physics   {nullptr};
    RenderComponent*    render    {nullptr};
    InputComponent*     input     {nullptr};
    CollisionComponent* collision {nullptr};
};