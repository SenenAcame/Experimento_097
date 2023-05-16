#pragma once
#include "aicmp.hpp"

struct BlackBoardCmp {
    double tx { 0.0 }, tz { 0.0 };
    bool tactive  { false };
    bool shoot    { false };
    std::size_t entyID { 0 };
    SB  behaviour { SB::Two_Steps };
};