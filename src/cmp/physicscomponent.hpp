#pragma once
#include "component.hpp"
//#include <cstddef>

struct PhysicsComponent : public Component{
    explicit PhysicsComponent(std::size_t eid) : Component(eid){};

    float  x{},  y{},  z{};
    float vx{}, vy{}, vz{};
};