#pragma once
#include "../util/types.hpp"
//#include <string>
#include <FMOD/src/fmod.hpp>
#include <FMOD/src/fmod_studio.hpp>
extern "C" { 
    #include <FMOD/src/fmod_errors.h> 
}

struct TheFachada {
    void init();
    void chargebanks();
    explicit TheFachada();
    void update();
    ProgrammerSoundContext createinstance(int);
    void close();
    void startsound(SoundCmp&);
    void set3DAttributes(SoundCmp&, PhysicsCmp2&);
    void setListener(PhysicsCmp2&);
    void stopsound(SoundCmp&);
    bool isPlaying(SoundCmp&);
    void changesound(SoundCmp&);
    void chargeparameters();
    void createdescriptions();
    void changeVCAVolume(int, float);
    void changeVCAMaster(float);

private:
    FMOD_SYSTEM *coreSystem;
    FMOD_STUDIO_SYSTEM *system;

    FMOD_STUDIO_EVENTDESCRIPTION *ambienteDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *armaDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *mejoraDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *danyoDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *moverseDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *menuDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *musicaDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *enemigoDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *personajeDescription;
    FMOD_STUDIO_EVENTDESCRIPTION *rondaDescription;

    FMOD_STUDIO_PARAMETER_DESCRIPTION paramAmbiente;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramArma;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMejora;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramDanyo;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMoverse;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMenu;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMusica;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramEnemigo;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramPersonaje;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramRonda;

    FMOD_STUDIO_BANK *masterBank;
    FMOD_STUDIO_BANK *stringsBank;
};