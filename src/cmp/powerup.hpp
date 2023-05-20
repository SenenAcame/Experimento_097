#pragma once
#include <cstdint>

enum class PU_Type {
    Damage,
    Speed,
    Health
};

struct PowerUp {
    PU_Type type { PU_Type::Damage };

    static constexpr uint8_t id { 14 };
};