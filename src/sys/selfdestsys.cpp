#include "selfdestsys.hpp"

void SelfDestSys::update(EntyMan& EM, double dt) {
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& e, SelfDestCmp& s) {
            s.time += dt;
            if(s.time <= s.cooldown) return;
            e.setDestroy();
        }
    );
}