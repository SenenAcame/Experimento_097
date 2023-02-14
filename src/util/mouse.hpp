#pragma once
#include <cstdint>

struct Mouse {
//    uint16_t X { 0 }, Y { 0 };
    explicit Mouse() = default;
//
//    Mouse(const Mouse&) = delete;
//    Mouse(Mouse&&)      = delete;
//    Mouse& operator=(const Mouse&) = delete;
//    Mouse& operator=(Mouse&&)      = delete;
//
    void moved()   { move = 1; }
    void quiet()   { move = 0; }
    bool getMove() { return move; }
private: 
    uint8_t move { 0 };
};