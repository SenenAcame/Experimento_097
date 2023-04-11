#pragma once
#include <cstdint>
#include <irrlicht/ISceneNode.h>
#include "../eng/TNodo.hpp"

struct RenderCmp2 {
    irr::scene::ISceneNode* n;

    TNodo* node;

    static constexpr uint8_t id { 1 }; //0000000010
};