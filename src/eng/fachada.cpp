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
        //FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;

        // Get our context from the event instance user data
        ProgrammerSoundContext* context = nullptr;
        CHECK_RESULT( eventInstance->getUserData((void**)&context) );

        // Find the audio file in the audio table with the key
        //FMOD_STUDIO_SOUND_INFO info;
        //CHECK_RESULT( context->system->getSoundInfo(context->dialogueString, &info) );
//
        //FMOD::Sound* sound = nullptr;
        //CHECK_RESULT( context->coreSystem->createSound(info.name_or_data, FMOD_LOOP_NORMAL | FMOD_CREATECOMPRESSEDSAMPLE | FMOD_NONBLOCKING | info.mode, &info.exinfo, &sound) );
//
        //// Pass the sound to FMOD
        //props->sound = (FMOD_SOUND*)sound;
        //props->subsoundIndex = info.subsoundindex;
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
    
    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    ERRCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );

    createdescriptions();
    chargeparameters();
}

void TheFachada::createdescriptions(){
    ambienteDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Ambientes/Ambientes", &ambienteDescription) );

    armaDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Efectos/Arma", &armaDescription) );

    mejoraDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Efectos/Comprar", &mejoraDescription) );

    danyoDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Efectos/Daño", &danyoDescription) );

    moverseDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Efectos/Moverse", &moverseDescription) );

    menuDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Menus/Menu", &menuDescription) );

    musicaDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Musica/Musica menu", &musicaDescription) );

    enemigoDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Voces/Enemigos", &enemigoDescription) );

    personajeDescription = nullptr;
    ERRCHECK(soundSystem->getEvent("event:/Voces/Personaje", &personajeDescription) );
}

void TheFachada::createinstance(Entity& e, int tipo){

    FMOD::Studio::EventInstance* eventInstance = nullptr;

    switch(tipo){
        case 0:
            ERRCHECK(ambienteDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramAmbiente.id), 0.0f));
            break;
        case 1:
            ERRCHECK(armaDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramArma.id), 0.0f));
            break;
            
        case 2:
            ERRCHECK(mejoraDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramMejora.id), 0.0f));
            break;
        case 3:
            ERRCHECK(danyoDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramDanyo.id), 0.0f));
            break;
        case 4:
            ERRCHECK(moverseDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramMoverse.id), 0.0f));
            break;
        case 5:
            ERRCHECK(menuDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramMenu.id), 0.0f));
            break;
        case 6:
            ERRCHECK(musicaDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramMusica.id), 0.0f));
            break;
        case 7:
            ERRCHECK(enemigoDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramEnemigo.id), 0.0f));
            break;
        default:
            ERRCHECK(personajeDescription->createInstance(&eventInstance));
            ERRCHECK( eventInstance->setParameterByID((e.sound->id=paramPersonaje.id), 0.0f));
    }

    e.sound->programmerSoundContext.system = soundSystem;
    e.sound->programmerSoundContext.coreSystem = coreSystem;

    ERRCHECK( eventInstance->setUserData(&e.sound->programmerSoundContext) );
    ERRCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );

    
    e.sound->sound = eventInstance;
}

void TheFachada::changesound(Entity& e ,unsigned int indice){
    ERRCHECK(e.sound->sound->setParameterByID(e.sound->id, indice));
}

void TheFachada::startsound(Entity& e){
    ERRCHECK( e.sound->sound->start() );
    
}

void TheFachada::close(){
    ERRCHECK(ambienteDescription->releaseAllInstances());
    ERRCHECK(armaDescription->releaseAllInstances());
    ERRCHECK(mejoraDescription->releaseAllInstances());
    ERRCHECK(danyoDescription->releaseAllInstances());
    ERRCHECK(moverseDescription->releaseAllInstances());
    ERRCHECK(menuDescription->releaseAllInstances());
    ERRCHECK(musicaDescription->releaseAllInstances());
    ERRCHECK(enemigoDescription->releaseAllInstances());
    ERRCHECK(personajeDescription->releaseAllInstances());
    ERRCHECK(masterBank->unload());
    ERRCHECK(stringsBank->unload());
    ERRCHECK(voicesBank->unload());
    ERRCHECK(soundSystem->unloadAll());
}

void TheFachada::chargeparameters(){
    ERRCHECK(ambienteDescription->getParameterDescriptionByName("ambiente",&paramAmbiente));

    ERRCHECK(armaDescription->getParameterDescriptionByName("armatipo",&paramArma));

    ERRCHECK(mejoraDescription->getParameterDescriptionByName("Mejora",&paramMejora));

    ERRCHECK(danyoDescription->getParameterDescriptionByName("Danyo",&paramDanyo));

    ERRCHECK(moverseDescription->getParameterDescriptionByName("moverse",&paramMoverse));

    ERRCHECK(menuDescription->getParameterDescriptionByName("Menu",&paramMenu));

    ERRCHECK(musicaDescription->getParameterDescriptionByName("musica",&paramMusica));

    ERRCHECK(enemigoDescription->getParameterDescriptionByName("vozenemigo",&paramEnemigo));

    ERRCHECK(personajeDescription->getParameterDescriptionByName("vozpersonaje",&paramPersonaje));
}