#pragma once
#include <stdint.h>

struct HealthComponent {
    explicit HealthComponent() = default;

    uint16_t value{100};
};