#include "soundsystem.hpp"

SoundSystem_t::SoundSystem_t() {
    facherita.init();
}

void SoundSystem_t::update(EntyMan& EM) {
    EM.foreach<SYSCMPs,SYSTAGs>(
        [&](Enty& e, SoundCmp& s) {
            if(s.cambia) {
                changesound(s);
                s.cambia = false;
            }
            if(s.play) {
                if(isPlaying(s)) {
                    s.isplaying = true;
                    s.play = false;
                    startsound(s);
                }
                else s.isplaying = false;
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

void SoundSystem_t::stopsound(SoundCmp& s) {
    facherita.stopsound(s);
}

bool SoundSystem_t::isPlaying(SoundCmp& s) {
    return facherita.isPlaying(s);
}

void SoundSystem_t::close() {
    facherita.close();
}
