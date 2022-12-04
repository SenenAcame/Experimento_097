#pragma once

struct PhysicsComponent {
    explicit PhysicsComponent() = default;

    float  x{},  y{},  z{};
    float vx{}, vy{}, vz{};
};