#pragma once

#include <vector>
#include "../utils/typeUsing.hpp"

struct Particle {

    Vec3 Position, Velocity;
    Vec4 Color;
    float Life;

    float Scale;
    float Rotation;

    float Gravity;

    Particle() : Position(0.0f), Velocity(0.0f), Color(0.0f), Life(0.0f), Scale(0.0f), Rotation(0.0f), Gravity(0.0f) {};
};