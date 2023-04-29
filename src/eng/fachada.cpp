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
    /*ERRORCHECK(FMOD::Studio::System::create(&soundSystem));
    ERRORCHECK(soundSystem->getCoreSystem(&coreSystem));
    ERRORCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRORCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERRORCHECK(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));*/

    ERRORCHECK(FMOD_Studio_System_Create(&system, 131589));
    ERRORCHECK(FMOD_Studio_System_GetCoreSystem(system, &coreSystem));
    ERRORCHECK(FMOD_System_SetSoftwareFormat(coreSystem, 0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRORCHECK(FMOD_System_SetOutput(coreSystem, FMOD_OUTPUTTYPE_AUTODETECT));
    ERRORCHECK(FMOD_Studio_System_Initialize(system, 1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_3D_RIGHTHANDED, 0));

    chargebanks();
}

void TheFachada::update() { /*ERRORCHECK(soundSystem->update() );*/ ERRORCHECK(FMOD_Studio_System_Update(system) ); }

void TheFachada::chargebanks() {
    masterBank = nullptr;
    stringsBank = nullptr;
    
    /*ERRORCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    ERRORCHECK(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
*/
    ERRORCHECK(FMOD_Studio_System_LoadBankFile(system, "assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    ERRORCHECK(FMOD_Studio_System_LoadBankFile(system, "assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );

    createdescriptions();
    chargeparameters();
}

void TheFachada::createdescriptions() {
    ambienteDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Ambientes/Ambientes", &ambienteDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Ambientes/Ambientes", &ambienteDescription) );

    armaDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Efectos/Arma", &armaDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Efectos/Arma", &armaDescription) );

    mejoraDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Efectos/Comprar", &mejoraDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Efectos/Comprar", &mejoraDescription) );

    danyoDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Efectos/Daño", &danyoDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Efectos/Daño", &danyoDescription) );

    moverseDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Efectos/Moverse", &moverseDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Efectos/Moverse", &moverseDescription) );

    menuDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Menus/Menu", &menuDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Menus/Menu", &menuDescription) );

    musicaDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Musica/Musica menu", &musicaDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Musica/Musica menu", &musicaDescription) );

    enemigoDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Voces/Enemigos", &enemigoDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Voces/Enemigos", &enemigoDescription) );

    rondaDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Voces/Ronda", &rondaDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Efectos/Ronda", &rondaDescription) );

    personajeDescription = nullptr;
    //ERRORCHECK(soundSystem->getEvent("event:/Voces/Personaje", &personajeDescription) );
    ERRORCHECK(FMOD_Studio_System_GetEvent(system, "event:/Voces/Personaje", &personajeDescription) );
}

ProgrammerSoundContext TheFachada::createinstance(int tipo) {
    ProgrammerSoundContext sound;
    FMOD_STUDIO_EVENTINSTANCE* eventInstance = nullptr;

    switch(tipo){
        case 0:
            /*ERRORCHECK(ambienteDescription->createInstance(&eventInstance));
            ERRORCHECK( eventInstance->setParameterByID((sound.id=paramAmbiente.id), 0.0f));*/
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(ambienteDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramAmbiente.id), 0.0f, false));
            break;
        case 1:
            //ERRORCHECK(armaDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramArma.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(armaDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramArma.id), 0.0f, false));
            break;
            
        case 2:
            //ERRORCHECK(mejoraDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMejora.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(mejoraDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMejora.id), 0.0f, false));
            break;
        case 3:
            //ERRORCHECK(danyoDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramDanyo.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(danyoDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramDanyo.id), 0.0f, false));
            break;
        case 4:
            //ERRORCHECK(moverseDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMoverse.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(moverseDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMoverse.id), 0.0f, false));
            break;
        case 5:
            //ERRORCHECK(menuDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMenu.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(menuDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMenu.id), 0.0f, false));
            break;
        case 6:
            //ERRORCHECK(musicaDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramMusica.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(musicaDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMusica.id), 0.0f, false));
            break;
        case 7:
            //ERRORCHECK(enemigoDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramEnemigo.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(enemigoDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramEnemigo.id), 0.0f, false));
            break;
        case 8:
        //    //ERRORCHECK(enemigoDescription->createInstance(&eventInstance));
        //    //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramEnemigo.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(rondaDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramRonda.id), 0.0f, false));
            break;
        default:
            //ERRORCHECK(personajeDescription->createInstance(&eventInstance));
            //ERRORCHECK( eventInstance->setParameterByID((sound.id=paramPersonaje.id), 0.0f));
            ERRORCHECK(FMOD_Studio_EventDescription_CreateInstance(personajeDescription, &eventInstance));
            ERRORCHECK( FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramPersonaje.id), 0.0f, false));
    }

    sound.system = system;
    sound.coreSystem = coreSystem;

    /*ERRORCHECK( eventInstance->setUserData(&sound) );
    ERRORCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );*/
    
    ERRORCHECK( FMOD_Studio_EventInstance_SetUserData(eventInstance, &sound) );
    ERRORCHECK( FMOD_Studio_EventInstance_SetCallback(eventInstance, programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );

    sound.sound = eventInstance;

    return sound;
}

void TheFachada::changesound(SoundCmp& s) {
    //ERRORCHECK(s.programmerSoundContext.sound->setParameterByID(s.programmerSoundContext.id, static_cast<float>(s.parametro)));
    ERRORCHECK(FMOD_Studio_EventInstance_SetParameterByID(s.programmerSoundContext.sound, s.programmerSoundContext.id, static_cast<float>(s.parametro), false));
}

void TheFachada::startsound(SoundCmp& s) {
    if(isPlaying(s)) stopsound(s);
    //ERRORCHECK( s.programmerSoundContext.sound->start() );
    ERRORCHECK( FMOD_Studio_EventInstance_Start(s.programmerSoundContext.sound) );
}

void TheFachada::set3DAttributes(SoundCmp& s, PhysicsCmp2& enty, PhysicsCmp2& player) {
    FMOD_3D_ATTRIBUTES att;
    att.position = FMOD_VECTOR{static_cast<float>((enty.x-player.x)/10), 0, static_cast<float>((enty.z-player.z)/10)};
    att.velocity = FMOD_VECTOR{0, 0, 0};
    att.forward  = FMOD_VECTOR{1, 0, 1};
    att.up       = FMOD_VECTOR{0, 1, 0};
    FMOD_Studio_EventInstance_Set3DAttributes(s.programmerSoundContext.sound, &att);
}

void TheFachada::setListener(PhysicsCmp2& player) {
    FMOD_3D_ATTRIBUTES att;
    att.position = FMOD_VECTOR{static_cast<float>(player.x), 0, static_cast<float>(player.z)};
    att.velocity = FMOD_VECTOR{0, 0, 0};
    att.forward  = FMOD_VECTOR{1, 0, 1};
    att.up       = FMOD_VECTOR{0, 1, 0};
    FMOD_Studio_System_SetListenerAttributes(system, 0, &att, NULL);
}

bool TheFachada::isPlaying(SoundCmp& s) {
    FMOD_STUDIO_PLAYBACK_STATE state;
    FMOD_Studio_EventInstance_GetPlaybackState(s.programmerSoundContext.sound, &state); // 0 PLAYING, 1 SUSTAINING, 2 STOPPED, 3 STARTING, 4 STOPPING
    if(state == 0 || state == 3)
        return true;

    return false;
}

void TheFachada::stopsound(SoundCmp& s) {
    //ERRORCHECK( s.programmerSoundContext.sound->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT) );
    ERRORCHECK( FMOD_Studio_EventInstance_Stop(s.programmerSoundContext.sound, FMOD_STUDIO_STOP_IMMEDIATE) );
}

void TheFachada::close() {
    /*ERRORCHECK(ambienteDescription->releaseAllInstances());
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
    ERRORCHECK(soundSystem->unloadAll());*/

    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(ambienteDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(armaDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(mejoraDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(danyoDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(moverseDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(menuDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(musicaDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(enemigoDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(rondaDescription));
    ERRORCHECK(FMOD_Studio_EventDescription_ReleaseAllInstances(personajeDescription));
    ERRORCHECK(FMOD_Studio_Bank_Unload(masterBank));
    ERRORCHECK(FMOD_Studio_Bank_Unload(stringsBank));
    ERRORCHECK(FMOD_Studio_System_UnloadAll(system));
}

void TheFachada::chargeparameters() {
    /*ERRORCHECK(ambienteDescription->getParameterDescriptionByName("ambiente",&paramAmbiente));

    ERRORCHECK(armaDescription->getParameterDescriptionByName("armatipo",&paramArma));

    ERRORCHECK(mejoraDescription->getParameterDescriptionByName("Mejora",&paramMejora));

    ERRORCHECK(danyoDescription->getParameterDescriptionByName("Danyo",&paramDanyo));

    ERRORCHECK(moverseDescription->getParameterDescriptionByName("moverse",&paramMoverse));

    ERRORCHECK(menuDescription->getParameterDescriptionByName("Menu",&paramMenu));

    ERRORCHECK(musicaDescription->getParameterDescriptionByName("musica",&paramMusica));

    ERRORCHECK(enemigoDescription->getParameterDescriptionByName("vozenemigo",&paramEnemigo));

    ERRORCHECK(personajeDescription->getParameterDescriptionByName("vozpersonaje",&paramPersonaje));*/

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(ambienteDescription, "ambiente",&paramAmbiente));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(armaDescription, "armatipo",&paramArma));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(mejoraDescription, "Mejora",&paramMejora));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(danyoDescription, "Danyo",&paramDanyo));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(moverseDescription, "moverse",&paramMoverse));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(menuDescription, "Menu",&paramMenu));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(musicaDescription, "musica",&paramMusica));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(enemigoDescription, "vozenemigo",&paramEnemigo));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(rondaDescription, "ronda",&paramRonda));

    ERRORCHECK(FMOD_Studio_EventDescription_GetParameterDescriptionByName(personajeDescription, "vozpersonaje",&paramPersonaje));
}