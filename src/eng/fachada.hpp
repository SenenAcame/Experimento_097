#pragma once

#include <string>
#include <iostream>
extern "C"{
    #include <FMOD/src/fmod_errors.h>
}
#include <FMOD/src/fmod.hpp>
#include <FMOD/src/fmod_studio.hpp>
#include <FMOD/src/common.hpp>
//#include "../man/entitymanager.hpp"

struct Entity;
struct TheFachada{

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

    public:
    
        void init();
        void chargebanks();
        explicit TheFachada();
        void update();
        void createinstance(Entity&,int);
        void close();
        void startsound(Entity&);
        void changesound(Entity&,unsigned int);
        void chargeparameters();
        void createdescriptions();
    };