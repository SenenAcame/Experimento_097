#include "soundsystem.hpp"

SoundSystem_t::SoundSystem_t(){
    facherita.init();
}

void SoundSystem_t::update(){
    facherita.update();
}

ProgrammerSoundContext SoundSystem_t::createinstance(int tipo){
    return facherita.createinstance(tipo);
}

void SoundSystem_t::changesound(SoundCmp& s ,unsigned int indice){
    facherita.changesound(s, indice);
}

void SoundSystem_t::startsound(SoundCmp& s){
    facherita.startsound(s);
}

void SoundSystem_t::close(){
    facherita.close();
}
