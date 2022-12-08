#pragma once
#include "../cmp/entity.hpp"
#include <vector>

struct GameContext{

    virtual const std::vector<Entity>& getEntities() const = 0;
};