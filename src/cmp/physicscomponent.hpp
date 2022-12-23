#pragma once
#include "component.hpp"

struct PhysicsComponent : public Component{
    explicit PhysicsComponent(std::size_t eid) : Component(eid){};

    float  x{},  y{},  z{};
    float vx{}, vy{}, vz{};
};