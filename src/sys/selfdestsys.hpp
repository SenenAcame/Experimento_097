#pragma once
#include "../util/types.hpp"


struct SelfDestSys {
    using SYSCMPs = MP::Typelist<SelfDestCmp>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, double dt) {
        
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, SelfDestCmp& s) {
                s.time += dt;
                if(s.time <= s.cooldown) return;
                e.setDestroy();
                
            }
        );
    }
};