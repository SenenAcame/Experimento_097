#pragma once

#include <string>
#include <iostream>
extern "C"{
    #include <FMOD/src/fmod_errors.h>
}
#include <FMOD/src/fmod.hpp>
#include <FMOD/src/fmod_studio.hpp>
#include <FMOD/src/common.hpp>
#include "../man/entitymanager.hpp"

struct SoundSystem_t{

    private:

    FMOD::System* coreSystem;
    FMOD::Studio::System* soundSystem;
    std::string dialogueString;

    unsigned int bankIndex;
    unsigned int dialogueIndex;
    const char* banks[2];
    const char* dialogue[3];

    FMOD::Studio::Bank* localizedBank;
    FMOD::Studio::EventDescription* eventDescription;

    FMOD::Studio::Bank * masterBank;
    FMOD::Studio::Bank* stringsBank;
    FMOD::Studio::Bank* voicesBank;

        void init();
        void chargebanks();
        void changebank();
        void changebankunload();
        
        

    public:
        explicit SoundSystem_t();
        void controller(unsigned int);
        void update();
        void createinstance(Entity&);
        void close();
        unsigned int getBankIndex();
        unsigned int getDialogueIndex();
        void startsound(Entity&);
        void changesound(Entity&,unsigned int);
    };
    
