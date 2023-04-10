#pragma once
#include "../util/types.hpp"


struct SelfDestSys {
    using SYSCMPs = MP::Typelist<SelfDestCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, double dt);
};