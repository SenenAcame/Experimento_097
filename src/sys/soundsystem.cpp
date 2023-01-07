#include "soundsystem.hpp"

SoundSystem_t::SoundSystem_t(){
    facherita.init();
}

void SoundSystem_t::update(){
    facherita.update();
}

void SoundSystem_t::createinstance(Entity& e){
    facherita.createinstance(e);
}

void SoundSystem_t::changesound(Entity& e ,unsigned int indice){
    facherita.changesound(e, indice);
}

void SoundSystem_t::startsound(Entity& e){
    facherita.startsound(e);
}

void SoundSystem_t::close(){
    facherita.close();
}
