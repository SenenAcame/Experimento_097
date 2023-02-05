#include "soundsystem.hpp"

SoundSystem_t::SoundSystem_t(){
    facherita.init();
}

ProgrammerSoundContext SoundSystem_t::createinstance(int tipo){
    return facherita.createinstance(tipo);
}

void SoundSystem_t::changesound(SoundCmp& s){
    facherita.changesound(s);
}

void SoundSystem_t::startsound(SoundCmp& s){
    facherita.startsound(s);
}

void SoundSystem_t::stopsound(SoundCmp& s){
    facherita.stopsound(s);
}

bool SoundSystem_t::isPlaying(SoundCmp& s){
    return facherita.isPlaying(s);
}

void SoundSystem_t::close(){
    facherita.close();
}
