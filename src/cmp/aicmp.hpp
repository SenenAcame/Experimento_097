#pragma once
#include <cstdint>

enum class SB{
    Arrive,
    Seek
};

struct AICmp {
    double ox{0}, oz{0};
    bool   enable        {false};
    double arrivalRadius {1.0};
    double timeArrive    {0.5};
    SB     behaviour     {SB::Arrive};

    static constexpr uint8_t id {4};
};