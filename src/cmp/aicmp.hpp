#pragma once
#include <cstdint>

struct AICmp {
    double  ox{0},  oz{0};
    bool enable {false};

    static constexpr uint8_t id {4};
};