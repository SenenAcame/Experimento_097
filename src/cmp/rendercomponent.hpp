#pragma once
#include <irrlicht/irrlicht.h>
#include "component.hpp"

struct RenderComponent : public Component{
    explicit RenderComponent(std::size_t eid) : Component(eid){};

    irr::scene::ISceneNode* node{};
};