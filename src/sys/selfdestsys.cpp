#include "selfdestsys.hpp"

void SelfDestSys::update(EntyMan& EM, double dt) {
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& ent, SelfDestCmp& self_dest) {
            self_dest.time += dt;
            if(self_dest.time <= self_dest.cooldown) return;
            ent.setDestroy();
        }
    );
}