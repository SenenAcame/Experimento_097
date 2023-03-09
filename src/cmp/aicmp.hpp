#pragma once
#include <cstddef>
#include <cstdint>

enum class SB{
    Arrive,
    Seek,
    Shoot,
    Patrol,
    Persue
};

struct AICmp {
    double ox{ 0 }, oz{ 0 };
    bool   enable        { true };
    double arrivalRadius { 1.0 };
    double timeArrive    { 0.5 };
    SB     behaviour     { SB::Arrive };
    bool   shoot         { false };

    double cooldown      { 0.1 };
    double time          { 0.0 };

    std::size_t entyID { 0 };

    static constexpr uint8_t id {4}; //0000010000
};