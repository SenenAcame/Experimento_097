#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include "cmp/physics.hpp"

namespace ECS{





    PhysicsComponent_T* phy {nullptr};
    uint32_t w {0}, h {0};
    std::vector<uint32_t> sprite {};
}