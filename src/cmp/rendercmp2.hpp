#pragma once
#include <cstdint>
#include <irrlicht/ISceneNode.h>

struct RenderCmp2 {
    irr::scene::ISceneNode* n;

    static constexpr uint8_t id {1}; //0000000010
};