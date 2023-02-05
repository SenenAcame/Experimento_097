#pragma once
#include <cstdint>
#include "aicmp.hpp"

struct BlackBoardCmp {
    double tx { 0.0 }, tz { 0.0 };
    bool tactive  { false };
    bool shoot    { false };
    SB  behaviour { SB::Seek };
};