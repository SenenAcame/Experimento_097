#include "soundsystem.hpp"

void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line) {
	if(result != FMOD_OK)
	{
        std::cerr << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

#define ERRCHECK(_result) ERRCHECK_FMOD(_result, __FILE__, __LINE__)

FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void* parameters);

struct ProgrammerSoundContext {
    FMOD::System* coreSystem;
    FMOD::Studio::System* system;
    const char* dialogueString;
};

#define CHECK_RESULT(op) \
{ \
    FMOD_RESULT res = (op); \
    if (res != FMOD_OK) \
    { \
        return res; \
    } \
}

FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void *parameters) {
    FMOD::Studio::EventInstance* eventInstance = (FMOD::Studio::EventInstance*)event;

    if (type == FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND) {
        FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;

        // Get our context from the event instance user data
        ProgrammerSoundContext* context = nullptr;
        CHECK_RESULT( eventInstance->getUserData((void**)&context) );

        // Find the audio file in the audio table with the key
        FMOD_STUDIO_SOUND_INFO info;
        CHECK_RESULT( context->system->getSoundInfo(context->dialogueString, &info) );

        FMOD::Sound* sound = nullptr;
        CHECK_RESULT( context->coreSystem->createSound(info.name_or_data, FMOD_LOOP_NORMAL | FMOD_CREATECOMPRESSEDSAMPLE | FMOD_NONBLOCKING | info.mode, &info.exinfo, &sound) );

        // Pass the sound to FMOD
        props->sound = (FMOD_SOUND*)sound;
        props->subsoundIndex = info.subsoundindex;
    }
    else if (type == FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) {
        FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;

        // Obtain the sound
        FMOD::Sound* sound = (FMOD::Sound*)props->sound;

        // Release the sound
        CHECK_RESULT( sound->release() );
    }

    return FMOD_OK;
}

ProgrammerSoundContext programmerSoundContext;

SoundSystem_t::SoundSystem_t(){
    init();
}

void SoundSystem_t::init(){
    
    bankIndex=0;
    dialogueIndex=0;

    ERRCHECK(FMOD::Studio::System::create(&soundSystem));
    ERRCHECK(soundSystem->getCoreSystem(&coreSystem));
    ERRCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERRCHECK(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

    chargebanks();

    chargedialogue();

    programmerSoundContext.system = soundSystem;
    programmerSoundContext.coreSystem = coreSystem;
    programmerSoundContext.dialogueString = dialogue[dialogueIndex];

    ERRCHECK( eventInstance->setUserData(&programmerSoundContext) );
    ERRCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );

}

void SoundSystem_t::update(){
    ERRCHECK(soundSystem->update() );
}

void SoundSystem_t::chargebanks(){
    masterBank = nullptr;
    stringsBank = nullptr;
    voicesBank = nullptr;
    
    ERRCHECK(soundSystem->loadBankFile("src/assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    ERRCHECK(soundSystem->loadBankFile("src/assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
    ERRCHECK(soundSystem->loadBankFile("src/assets/FMOD_BANKS/Voices.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &voicesBank) );

    banks[0] = "src/assets/FMOD_BANKS/Dialogue_CT.bank";
    banks[1] = "src/assets/FMOD_BANKS/Dialogue_T.bank";
}

void SoundSystem_t::chargedialogue(){
    localizedBank = nullptr;
    ERRCHECK(soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );

    eventDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Dialogue", &eventDescription) );

    eventInstance = nullptr;
    ERRCHECK(eventDescription->createInstance(&eventInstance));

    dialogue[0] = "agree";
    dialogue[1] = "disagree";
    dialogue[2] = "smoke";
}

void SoundSystem_t::changebank(){
    bankIndex = (bankIndex < 1) ? bankIndex + 1 : 0;
    ERRCHECK( soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );
}

void SoundSystem_t::changebankunload(){
    ERRCHECK( localizedBank->unload() );
    changebank();
}

void SoundSystem_t::changesound(){
    dialogueIndex = (dialogueIndex < 2) ? dialogueIndex + 1 : 0;
    programmerSoundContext.dialogueString = dialogue[dialogueIndex];
}

void SoundSystem_t::startsound(){
    ERRCHECK( eventInstance->start() );
}

void SoundSystem_t::close(){
    ERRCHECK(eventDescription->releaseAllInstances());
    ERRCHECK(masterBank->unload());
    ERRCHECK(stringsBank->unload());
    ERRCHECK(localizedBank->unload());
    ERRCHECK(voicesBank->unload());
    ERRCHECK(soundSystem->unloadAll());
}

void SoundSystem_t::controller(unsigned int n){
    switch(n){
        case 1:
            changebankunload();
            break;

        case 2:
            changesound();
            break;

        case 3:
            startsound();
    }
}

unsigned int SoundSystem_t::getBankIndex(){
    return bankIndex;
}

unsigned int SoundSystem_t::getDialogueIndex(){
    return dialogueIndex;
}