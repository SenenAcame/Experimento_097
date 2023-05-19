#pragma once
#include "aicmp.hpp"
#include "../util/waves_aux.hpp"

struct BlackBoardCmp {
    double tx { 0.0 }, tz { 0.0 };
    bool tactive  { false };
    bool shoot    { false };
    std::size_t entyID { 0 };
    SB  behaviour { SB::Two_Steps };

    double spawn_perc { 50.0 };

    ExtraStats   difficult {};
    WaveInfo     wave      {};
    WavesProgres progres   {};
    Clock restart_weapons  { 0, 20 };
};