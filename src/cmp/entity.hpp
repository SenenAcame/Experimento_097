#pragma once
#include "physicscomponent.hpp"
#include "rendercomponent.hpp"

struct Entity {
    PhysicsComponent physics;
    RenderComponent render;
};