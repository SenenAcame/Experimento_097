#pragma once
#include <cstdint>
#include "aicmp.hpp"

struct BlackBoardCmp {
    double tx{ 0.0 }, tz{ 0.0 };
    SB  behaviour { SB::Seek };
    bool tactive { false };
};