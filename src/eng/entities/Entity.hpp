#pragma once

#include <glm/glm.hpp>
#include "../utils/typeUsing.hpp"

#include "../resources/RShader.hpp"

#include <iostream>

struct Entity {
    Entity(){};

    ~Entity(){};

    virtual void draw(Mat4 mat, bool border) = 0;

    bool unused_ {true};
};