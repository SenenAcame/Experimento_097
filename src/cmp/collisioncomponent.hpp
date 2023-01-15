#pragma once
#include "component.hpp"
#include <cstdint>

struct Entity;

struct ColliderComponent : public Component{
    explicit ColliderComponent(std::size_t eid) : Component(eid){};
    
    float width_x{2};
    float width_y{2};
    float height{2};

};
