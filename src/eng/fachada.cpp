#include "fachada.hpp"


void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line) {
	if(result != FMOD_OK)
	{
        std::cerr << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

#define ERRCHECK(_result) ERRCHECK_FMOD(_result, __FILE__, __LINE__)

FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void* parameters);

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



TheFachada::TheFachada(){

}

void TheFachada::init(){
    
    bankIndex=0;
    dialogueIndex=0;

    ERRCHECK(FMOD::Studio::System::create(&soundSystem));
    ERRCHECK(soundSystem->getCoreSystem(&coreSystem));
    ERRCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERRCHECK(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

    chargebanks();
}

void TheFachada::update(){
    ERRCHECK(soundSystem->update() );
}

void TheFachada::chargebanks(){
    masterBank = nullptr;
    stringsBank = nullptr;
    voicesBank = nullptr;
    
    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Voices.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &voicesBank) );

    banks[0] = "assets/FMOD_BANKS/Dialogue_CT.bank";
    banks[1] = "assets/FMOD_BANKS/Dialogue_T.bank";

    localizedBank = nullptr;
    ERRCHECK(soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );

    eventDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Dialogue", &eventDescription) );

}

void TheFachada::createinstance(Entity& e){

    FMOD::Studio::EventInstance* eventInstance = nullptr;
    ERRCHECK(eventDescription->createInstance(&eventInstance));

    dialogue[0] = "agree";
    dialogue[1] = "disagree";
    dialogue[2] = "smoke";

    e.sound->programmerSoundContext.system = soundSystem;
    e.sound->programmerSoundContext.coreSystem = coreSystem;
    e.sound->programmerSoundContext.dialogueString = dialogue[dialogueIndex];

    ERRCHECK( eventInstance->setUserData(&e.sound->programmerSoundContext) );
    ERRCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );

    e.sound->sound = eventInstance;
}

void TheFachada::changebank(){
    bankIndex = (bankIndex < 1) ? bankIndex + 1 : 0;
    ERRCHECK( soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );
}

void TheFachada::changebankunload(){
    ERRCHECK( localizedBank->unload() );
    changebank();
}

void TheFachada::changesound(Entity& e ,unsigned int indice){
    //dialogueIndex = (indice < 3 && indice >= 0) ? dialogueIndex = indice : 0;
    //e.sound->programmerSoundContext.dialogueString = dialogue[dialogueIndex];
    if(indice < 3 && indice >= 0)
    e.sound->programmerSoundContext.dialogueString = dialogue[indice];
}

void TheFachada::startsound(Entity& e){
    ERRCHECK( e.sound->sound->start() );
    
}

void TheFachada::close(){
    ERRCHECK(eventDescription->releaseAllInstances());
    ERRCHECK(masterBank->unload());
    ERRCHECK(stringsBank->unload());
    ERRCHECK(localizedBank->unload());
    ERRCHECK(voicesBank->unload());
    ERRCHECK(soundSystem->unloadAll());
}

void TheFachada::controller(unsigned int n){
    /*switch(n){
        case 1:
            changebankunload();
            break;

        case 2:
            changesound();
            break;

        case 3:
            startsound();
    }*/
}

unsigned int TheFachada::getBankIndex(){
    return bankIndex;
}

unsigned int TheFachada::getDialogueIndex(){
    return dialogueIndex;
}