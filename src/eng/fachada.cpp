#include "fachada.hpp"
#include <iostream>

//void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line) {
void ERRCHECK_FMOD (FMOD_RESULT result) {
	if(result != FMOD_OK) {
        std::cerr << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

#define ERRORCHECK(_result) ERRCHECK_FMOD(_result)

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
    ERRORCHECK(FMOD::Studio::System::create(&soundSystem));
    ERRORCHECK(soundSystem->getCoreSystem(&coreSystem));
    ERRORCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRORCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERRORCHECK(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

    chargebanks();
}

void TheFachada::update() { ERRORCHECK(soundSystem->update() ); }

void TheFachada::chargebanks() {
    masterBank = nullptr;
    stringsBank = nullptr;
    
    ERRORCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    ERRORCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );

    createdescriptions();
    chargeparameters();
}

void TheFachada::createdescriptions() {
    ambienteDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Ambientes/Ambientes", &ambienteDescription) );

    armaDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Efectos/Arma", &armaDescription) );

    mejoraDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Efectos/Comprar", &mejoraDescription) );

    danyoDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Efectos/Daño", &danyoDescription) );

    moverseDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Efectos/Moverse", &moverseDescription) );

    menuDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Menus/Menu", &menuDescription) );

    musicaDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Musica/Musica menu", &musicaDescription) );

    enemigoDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Voces/Enemigos", &enemigoDescription) );

    personajeDescription = nullptr;
    ERRORCHECK(soundSystem->getEvent("event:/Voces/Personaje", &personajeDescription) );
}

ProgrammerSoundContext TheFachada::createinstance(int tipo) {
    ProgrammerSoundContext sound;
    FMOD::Studio::EventInstance* eventInstance = nullptr;

    switch(tipo){
        case 0:
            ERRORCHECK(ambienteDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramAmbiente.id), 0.0f));
            break;
        case 1:
            ERRORCHECK(armaDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramArma.id), 0.0f));
            break;
            
        case 2:
            ERRORCHECK(mejoraDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMejora.id), 0.0f));
            break;
        case 3:
            ERRORCHECK(danyoDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramDanyo.id), 0.0f));
            break;
        case 4:
            ERRORCHECK(moverseDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMoverse.id), 0.0f));
            break;
        case 5:
            ERRORCHECK(menuDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMenu.id), 0.0f));
            break;
        case 6:
            ERRORCHECK(musicaDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMusica.id), 0.0f));
            break;
        case 7:
            ERRORCHECK(enemigoDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramEnemigo.id), 0.0f));
            break;
        default:
            ERRORCHECK(personajeDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramPersonaje.id), 0.0f));
    }

    sound.system = soundSystem;
    sound.coreSystem = coreSystem;

    ERRORCHECK( eventInstance->setUserData(&sound) );
    ERRORCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );
    
    sound.sound = eventInstance;

    return sound;
}

void TheFachada::changesound(SoundCmp& s) {
    ERRORCHECK(s.programmerSoundContext.sound->setParameterByID(s.programmerSoundContext.id, static_cast<float>(s.parametro)));
}

void TheFachada::startsound(SoundCmp& s) {
    if(isPlaying(s)) stopsound(s);
    ERRORCHECK( s.programmerSoundContext.sound->start() );
}

void TheFachada::stopsound(SoundCmp& s) {
    ERRORCHECK( s.programmerSoundContext.sound->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT) );
}

bool TheFachada::isPlaying(SoundCmp& s) {
    FMOD_STUDIO_PLAYBACK_STATE* state = nullptr;
    if(s.programmerSoundContext.sound->getPlaybackState(state) != 2/*FMOD_STUDIO_PLAYBACK_STOPPED*/)
        return true;

    return false;
}

void TheFachada::close() {
    ERRORCHECK(ambienteDescription->releaseAllInstances());
    ERRORCHECK(armaDescription->releaseAllInstances());
    ERRORCHECK(mejoraDescription->releaseAllInstances());
    ERRORCHECK(danyoDescription->releaseAllInstances());
    ERRORCHECK(moverseDescription->releaseAllInstances());
    ERRORCHECK(menuDescription->releaseAllInstances());
    ERRORCHECK(musicaDescription->releaseAllInstances());
    ERRORCHECK(enemigoDescription->releaseAllInstances());
    ERRORCHECK(personajeDescription->releaseAllInstances());
    ERRORCHECK(masterBank->unload());
    ERRORCHECK(stringsBank->unload());
    ERRORCHECK(soundSystem->unloadAll());
}

void TheFachada::chargeparameters() {
    ERRORCHECK(ambienteDescription->getParameterDescriptionByName("ambiente",&paramAmbiente));

    ERRORCHECK(armaDescription->getParameterDescriptionByName("armatipo",&paramArma));

    ERRORCHECK(mejoraDescription->getParameterDescriptionByName("Mejora",&paramMejora));

    ERRORCHECK(danyoDescription->getParameterDescriptionByName("Danyo",&paramDanyo));

    ERRORCHECK(moverseDescription->getParameterDescriptionByName("moverse",&paramMoverse));

    ERRORCHECK(menuDescription->getParameterDescriptionByName("Menu",&paramMenu));

    ERRORCHECK(musicaDescription->getParameterDescriptionByName("musica",&paramMusica));

    ERRORCHECK(enemigoDescription->getParameterDescriptionByName("vozenemigo",&paramEnemigo));

    ERRORCHECK(personajeDescription->getParameterDescriptionByName("vozpersonaje",&paramPersonaje));
}