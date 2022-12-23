#pragma once

#include <string>
#include <iostream>
extern "C"{
    #include <FMOD/src/fmod_errors.h>
}
#include <FMOD/src/fmod.hpp>
#include <FMOD/src/fmod_studio.hpp>
#include <FMOD/src/common.hpp>

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
    FMOD::Studio::EventInstance* eventInstance;

    FMOD::Studio::Bank * masterBank;
    FMOD::Studio::Bank* stringsBank;
    FMOD::Studio::Bank* voicesBank;

        void init();
        void chargebanks();
        void chargedialogue();
        void changebank();
        void changebankunload();
        void changesound();
        void startsound();

    public:
        explicit SoundSystem_t();
        void controller(unsigned int);
        void update();
        void close();
        unsigned int getBankIndex();
        unsigned int getDialogueIndex();
    };
    
