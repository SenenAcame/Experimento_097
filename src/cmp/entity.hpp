#pragma once
#include "physicscomponent.hpp"
#include "rendercomponent.hpp"
#include "inputcomponent.hpp"

struct Entity {
    PhysicsComponent physics;
    RenderComponent render;
    InputComponent input;
};