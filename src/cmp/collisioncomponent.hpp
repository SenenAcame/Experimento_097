#pragma once
#include "component.hpp"

struct CollisionComponent : public Component{
    explicit CollisionComponent(std::size_t eid) : Component(eid){};
};