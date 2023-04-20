#include "fachada.hpp"
#include <iostream>

void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line) {
	if(result != FMOD_OK) {
        std::cerr << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

#define ERROCHECK(_result) ERRCHECK_FMOD(_result, __FILE__, __LINE__)

FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void* parameters);

#define CHECK_RESULT(op) { \
    FMOD_RESULT res = (op); \
    if (res != FMOD_OK) return res; \
}

FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void *parameters) {
    FMOD::Studio::EventInstance* eventInstance = (FMOD::Studio::EventInstance*) event;

    if (type == FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND) {
        //FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;
        //
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

TheFachada::TheFachada() {}

void TheFachada::init() {
    ERROCHECK(FMOD::Studio::System::create(&soundSystem));
    ERROCHECK(soundSystem->getCoreSystem(&coreSystem));
    ERROCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERROCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERROCHECK(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

    chargebanks();
}

void TheFachada::update() { ERROCHECK(soundSystem->update() ); }

void TheFachada::chargebanks() {
    masterBank = nullptr;
    stringsBank = nullptr;
    
    ERROCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    ERROCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );

    createdescriptions();
    chargeparameters();
}

void TheFachada::createdescriptions() {
    ambienteDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Ambientes/Ambientes", &ambienteDescription) );

    armaDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Efectos/Arma", &armaDescription) );

    mejoraDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Efectos/Comprar", &mejoraDescription) );

    danyoDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Efectos/Daño", &danyoDescription) );

    moverseDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Efectos/Moverse", &moverseDescription) );

    menuDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Menus/Menu", &menuDescription) );

    musicaDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Musica/Musica menu", &musicaDescription) );

    enemigoDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Voces/Enemigos", &enemigoDescription) );

    personajeDescription = nullptr;
    ERROCHECK(soundSystem->getEvent("event:/Voces/Personaje", &personajeDescription) );
}

ProgrammerSoundContext TheFachada::createinstance(int tipo) {
    ProgrammerSoundContext sound;
    FMOD::Studio::EventInstance* eventInstance = nullptr;

    switch(tipo){
        case 0:
            ERROCHECK(ambienteDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramAmbiente.id), 0.0f));
            break;
        case 1:
            ERROCHECK(armaDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramArma.id), 0.0f));
            break;
            
        case 2:
            ERROCHECK(mejoraDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramMejora.id), 0.0f));
            break;
        case 3:
            ERROCHECK(danyoDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramDanyo.id), 0.0f));
            break;
        case 4:
            ERROCHECK(moverseDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramMoverse.id), 0.0f));
            break;
        case 5:
            ERROCHECK(menuDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramMenu.id), 0.0f));
            break;
        case 6:
            ERROCHECK(musicaDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramMusica.id), 0.0f));
            break;
        case 7:
            ERROCHECK(enemigoDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramEnemigo.id), 0.0f));
            break;
        default:
            ERROCHECK(personajeDescription->createInstance(&eventInstance));
            ERROCHECK( eventInstance->setParameterByID((sound.id=paramPersonaje.id), 0.0f));
    }

    sound.system = soundSystem;
    sound.coreSystem = coreSystem;

    ERROCHECK( eventInstance->setUserData(&sound) );
    ERROCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );
    
    sound.sound = eventInstance;

    return sound;
}

void TheFachada::changesound(SoundCmp& s) {
    ERROCHECK(s.programmerSoundContext.sound->setParameterByID(s.programmerSoundContext.id, s.parametro));
}

void TheFachada::startsound(SoundCmp& s) {
    if(isPlaying(s)) stopsound(s);
    ERROCHECK( s.programmerSoundContext.sound->start() );
}

void TheFachada::stopsound(SoundCmp& s) {
    ERROCHECK( s.programmerSoundContext.sound->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT) );
}

bool TheFachada::isPlaying(SoundCmp& s) {
    FMOD_STUDIO_PLAYBACK_STATE* state = nullptr;
    if(s.programmerSoundContext.sound->getPlaybackState(state) != 2/*FMOD_STUDIO_PLAYBACK_STOPPED*/)
        return true;

    return false;
}

void TheFachada::close() {
    ERROCHECK(ambienteDescription->releaseAllInstances());
    ERROCHECK(armaDescription->releaseAllInstances());
    ERROCHECK(mejoraDescription->releaseAllInstances());
    ERROCHECK(danyoDescription->releaseAllInstances());
    ERROCHECK(moverseDescription->releaseAllInstances());
    ERROCHECK(menuDescription->releaseAllInstances());
    ERROCHECK(musicaDescription->releaseAllInstances());
    ERROCHECK(enemigoDescription->releaseAllInstances());
    ERROCHECK(personajeDescription->releaseAllInstances());
    ERROCHECK(masterBank->unload());
    ERROCHECK(stringsBank->unload());
    ERROCHECK(soundSystem->unloadAll());
}

void TheFachada::chargeparameters() {
    ERROCHECK(ambienteDescription->getParameterDescriptionByName("ambiente",&paramAmbiente));

    ERROCHECK(armaDescription->getParameterDescriptionByName("armatipo",&paramArma));

    ERROCHECK(mejoraDescription->getParameterDescriptionByName("Mejora",&paramMejora));

    ERROCHECK(danyoDescription->getParameterDescriptionByName("Danyo",&paramDanyo));

    ERROCHECK(moverseDescription->getParameterDescriptionByName("moverse",&paramMoverse));

    ERROCHECK(menuDescription->getParameterDescriptionByName("Menu",&paramMenu));

    ERROCHECK(musicaDescription->getParameterDescriptionByName("musica",&paramMusica));

    ERROCHECK(enemigoDescription->getParameterDescriptionByName("vozenemigo",&paramEnemigo));

    ERROCHECK(personajeDescription->getParameterDescriptionByName("vozpersonaje",&paramPersonaje));
}