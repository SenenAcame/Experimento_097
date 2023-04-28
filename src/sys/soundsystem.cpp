#include "soundsystem.hpp"

SoundSystem_t::SoundSystem_t() {
    facherita.init();
}

void SoundSystem_t::update(EntyMan& EM, Enty& player) {
    EM.foreach<PHYCMPs,ENETAGs>(
        [&](Enty& e, PhysicsCmp2& p, SoundCmp& s) {
            facherita.set3DAttributes(s, p, EM.getComponent<PhysicsCmp2>(player));
        }
    );
    facherita.setListener(EM.getComponent<PhysicsCmp2>(player));
    EM.foreach<SYSCMPs,SYSTAGs>(
        [&](Enty& e, SoundCmp& s) {
            if(s.cambia) {
                changesound(s);
                s.cambia = false;
            }
            if(isPlaying(s) && !s.loop)
                s.play = false;
            if(s.play) {
                if(!isPlaying(s)) {
                    if(!s.loop)
                        s.play = false;
                    startsound(s);
                }
            }
            
            //if(s.release) {
            //    s.programmerSoundContext.sound->release();
            //}
        }
    );
    facherita.update();
};

ProgrammerSoundContext SoundSystem_t::createinstance(int tipo) {
    return facherita.createinstance(tipo);
}

void SoundSystem_t::changesound(SoundCmp& s) {
    facherita.changesound(s);
}

void SoundSystem_t::startsound(SoundCmp& s) {
    facherita.startsound(s);
}

void SoundSystem_t::setloop(SoundCmp& s) {
    s.loop = !s.loop;
}

void SoundSystem_t::stopsound(SoundCmp& s) {
    if(s.loop)
        setloop(s);
    s.play=false;
    facherita.stopsound(s);
}

bool SoundSystem_t::isPlaying(SoundCmp& s) {
    return facherita.isPlaying(s);
}

void SoundSystem_t::close() {
    facherita.close();
}
