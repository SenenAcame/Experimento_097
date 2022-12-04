#pragma once
#include <irrlicht/irrlicht.h>

struct RenderComponent {
    explicit RenderComponent() = default;

    irr::scene::ISceneNode* node{};
};