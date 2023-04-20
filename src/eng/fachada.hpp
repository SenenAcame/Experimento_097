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
    void set3DAttributes(SoundCmp&, PhysicsCmp2&, PhysicsCmp2&);
    void setListener(PhysicsCmp2&);
    void stopsound(SoundCmp&);
    bool isPlaying(SoundCmp&);
    void changesound(SoundCmp&);
    void chargeparameters();
    void createdescriptions();

private:
    FMOD::System* coreSystem;
    FMOD::Studio::System* soundSystem;

    FMOD::Studio::EventDescription* ambienteDescription;
    FMOD::Studio::EventDescription* armaDescription;
    FMOD::Studio::EventDescription* mejoraDescription;
    FMOD::Studio::EventDescription* danyoDescription;
    FMOD::Studio::EventDescription* moverseDescription;
    FMOD::Studio::EventDescription* menuDescription;
    FMOD::Studio::EventDescription* musicaDescription;
    FMOD::Studio::EventDescription* enemigoDescription;
    FMOD::Studio::EventDescription* personajeDescription;

    FMOD_STUDIO_PARAMETER_DESCRIPTION paramAmbiente;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramArma;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMejora;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramDanyo;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMoverse;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMenu;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramMusica;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramEnemigo;
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramPersonaje;

    FMOD::Studio::Bank * masterBank;
    FMOD::Studio::Bank* stringsBank;
};