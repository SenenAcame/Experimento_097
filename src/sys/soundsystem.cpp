#include "soundsystem.hpp"
#include "../man/entitymanager.hpp"

SoundSystem_t::SoundSystem_t(){
    facherita.init();
}

void SoundSystem_t::update(){
    facherita.update();
}

void SoundSystem_t::createinstance(Entity& e,int tipo){
    facherita.createinstance(e, tipo);
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
