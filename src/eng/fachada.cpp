#include "fachada.hpp"
#include <iostream>
//
////void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line) {
//void ERRCHECK_FMOD (FMOD_RESULT result) {
//	if(result != FMOD_OK) {
//        std::cerr << FMOD_ErrorString(result) << std::endl;
//		exit(-1);
//	}
//}
//
//#define _result) ERRCHECK_FMOD(_result)
//
//FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void* parameters);
//
//#define CHECK_RESULT(op) { \
//    FMOD_RESULT res = (op); \
//    if (res != FMOD_OK) return res; \
//}
//
//FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void *parameters) {
//    FMOD::Studio::EventInstance* eventInstance = (FMOD::Studio::EventInstance*) event;
//
//    if (type == FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND) {
//        //FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;
//        //
//        // Get our context from the event instance user data
//        ProgrammerSoundContext* context = nullptr;
//        eventInstance->getUserData((void**)&context) ;
//
//        // Find the audio file in the audio table with the key
//        //FMOD_STUDIO_SOUND_INFO info;
//        //CHECK_RESULT( context->system->getSoundInfo(context->dialogueString, &info) );
//        //
//        //FMOD::Sound* sound = nullptr;
//        //CHECK_RESULT( context->coreSystem->createSound(info.name_or_data, FMOD_LOOP_NORMAL | FMOD_CREATECOMPRESSEDSAMPLE | FMOD_NONBLOCKING | info.mode, &info.exinfo, &sound) );
//        //
//        //// Pass the sound to FMOD
//        //props->sound = (FMOD_SOUND*)sound;
//        //props->subsoundIndex = info.subsoundindex;
//    }
//    else if (type == FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) {
//        FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;
//
//        // Obtain the sound
//        FMOD::Sound* sound = (FMOD::Sound*)props->sound;
//
//        // Release the sound
//        sound->release() ;
//    }
//
//    return FMOD_OK;
//}

TheFachada::TheFachada() {}

void TheFachada::init() {
    /*FMOD::Studio::System::create(&soundSystem));
    soundSystem->getCoreSystem(&coreSystem));
    coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));*/

    FMOD_Studio_System_Create(&system, 131589);
    FMOD_Studio_System_GetCoreSystem(system, &coreSystem);
    FMOD_System_SetSoftwareFormat(coreSystem, 0, FMOD_SPEAKERMODE_5POINT1, 0);
    FMOD_System_SetOutput(coreSystem, FMOD_OUTPUTTYPE_AUTODETECT);
    FMOD_Studio_System_Initialize(system, 1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_3D_RIGHTHANDED, 0);

    chargebanks();
}

void TheFachada::update() { /*soundSystem->update() );*/ FMOD_Studio_System_Update(system) ; }

void TheFachada::chargebanks() {
    masterBank = nullptr;
    stringsBank = nullptr;
    
    /*soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
*/
    FMOD_Studio_System_LoadBankFile(system, "assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) ;
    FMOD_Studio_System_LoadBankFile(system, "assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) ;

    createdescriptions();
    chargeparameters();
}

void TheFachada::createdescriptions() {
    ambienteDescription = nullptr;
    //soundSystem->getEvent("event:/Ambientes/Ambientes", &ambienteDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Ambientes/Ambientes", &ambienteDescription) ;

    armaDescription = nullptr;
    //soundSystem->getEvent("event:/Efectos/Arma", &armaDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Arma", &armaDescription) ;

    mejoraDescription = nullptr;
    //soundSystem->getEvent("event:/Efectos/Comprar", &mejoraDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Comprar", &mejoraDescription) ;

    danyoDescription = nullptr;
    //soundSystem->getEvent("event:/Efectos/Daño", &danyoDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Daño", &danyoDescription) ;

    moverseDescription = nullptr;
    //soundSystem->getEvent("event:/Efectos/Moverse", &moverseDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Moverse", &moverseDescription) ;

    menuDescription = nullptr;
    //soundSystem->getEvent("event:/Menus/Menu", &menuDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Menus/Menu", &menuDescription) ;

    musicaDescription = nullptr;
    //soundSystem->getEvent("event:/Musica/Musica menu", &musicaDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Musica/Musica menu", &musicaDescription) ;

    enemigoDescription = nullptr;
    //soundSystem->getEvent("event:/Voces/Enemigos", &enemigoDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Voces/Enemigos", &enemigoDescription) ;

    rondaDescription = nullptr;
    //soundSystem->getEvent("event:/Voces/Ronda", &rondaDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Ronda", &rondaDescription) ;

    personajeDescription = nullptr;
    //soundSystem->getEvent("event:/Voces/Personaje", &personajeDescription) );
    FMOD_Studio_System_GetEvent(system, "event:/Voces/Personaje", &personajeDescription) ;
}

ProgrammerSoundContext TheFachada::createinstance(int tipo) {
    ProgrammerSoundContext sound;
    FMOD_STUDIO_EVENTINSTANCE* eventInstance = nullptr;

    switch(tipo){
        case 0:
            /*ambienteDescription->createInstance(&eventInstance));
             eventInstance->setParameterByID((sound.id=paramAmbiente.id), 0.0f));*/
            FMOD_Studio_EventDescription_CreateInstance(ambienteDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramAmbiente.id), 0.0f, false);
            break;
        case 1:
            //armaDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramArma.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(armaDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramArma.id), 0.0f, false);
            break;
            
        case 2:
            //mejoraDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramMejora.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(mejoraDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMejora.id), 0.0f, false);
            break;
        case 3:
            //danyoDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramDanyo.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(danyoDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramDanyo.id), 0.0f, false);
            break;
        case 4:
            //moverseDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramMoverse.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(moverseDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMoverse.id), 0.0f, false);
            break;
        case 5:
            //menuDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramMenu.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(menuDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMenu.id), 0.0f, false);
            break;
        case 6:
            //musicaDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramMusica.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(musicaDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMusica.id), 0.0f, false);
            break;
        case 7:
            //enemigoDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramEnemigo.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(enemigoDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramEnemigo.id), 0.0f, false);
            break;
        case 8:
        //    //enemigoDescription->createInstance(&eventInstance));
        //    // eventInstance->setParameterByID((sound.id=paramEnemigo.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(rondaDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramRonda.id), 0.0f, false);
            break;
        default:
            //personajeDescription->createInstance(&eventInstance));
            // eventInstance->setParameterByID((sound.id=paramPersonaje.id), 0.0f));
            FMOD_Studio_EventDescription_CreateInstance(personajeDescription, &eventInstance);
             FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramPersonaje.id), 0.0f, false);
    }

    sound.system = system;
    sound.coreSystem = coreSystem;

    /* eventInstance->setUserData(&sound) );
     eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );*/
    
     //FMOD_Studio_EventInstance_SetUserData(eventInstance, &sound) ;
     //FMOD_Studio_EventInstance_SetCallback(eventInstance, programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) ;

    sound.sound = eventInstance;

    return sound;
}

void TheFachada::changesound(SoundCmp& s) {
    //s.programmerSoundContext.sound->setParameterByID(s.programmerSoundContext.id, static_cast<float>(s.parametro)));
    FMOD_Studio_EventInstance_SetParameterByID(s.programmerSoundContext.sound, s.programmerSoundContext.id, static_cast<float>(s.parametro), false);
}

void TheFachada::startsound(SoundCmp& s) {
    if(isPlaying(s)) stopsound(s);
    // s.programmerSoundContext.sound->start() );
     FMOD_Studio_EventInstance_Start(s.programmerSoundContext.sound) ;
}

void TheFachada::set3DAttributes(SoundCmp& s, PhysicsCmp2& enty, PhysicsCmp2& player) {
    FMOD_3D_ATTRIBUTES att;
    att.position = FMOD_VECTOR{static_cast<float>(enty.x/10), 0, static_cast<float>(enty.z/10)};
    att.velocity = FMOD_VECTOR{0, 0, 0};
    att.forward  = FMOD_VECTOR{1, 0, 0};
    att.up       = FMOD_VECTOR{0, 1, 0};
    FMOD_Studio_EventInstance_Set3DAttributes(s.programmerSoundContext.sound, &att);
}

void TheFachada::setListener(PhysicsCmp2& player) {
    FMOD_3D_ATTRIBUTES att;
    att.position = FMOD_VECTOR{static_cast<float>(player.x/10), 0, static_cast<float>(player.z/10)};
    att.velocity = FMOD_VECTOR{0, 0, 0};
    att.forward  = FMOD_VECTOR{static_cast<float>(sin(player.orieny*180/std::numbers::pi)), 0, static_cast<float>(cos(player.orieny*180/std::numbers::pi))};
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
    // s.programmerSoundContext.sound->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT) );
     FMOD_Studio_EventInstance_Stop(s.programmerSoundContext.sound, FMOD_STUDIO_STOP_IMMEDIATE) ;
}

void TheFachada::close() {
    /*ambienteDescription->releaseAllInstances());
    armaDescription->releaseAllInstances());
    mejoraDescription->releaseAllInstances());
    danyoDescription->releaseAllInstances());
    moverseDescription->releaseAllInstances());
    menuDescription->releaseAllInstances());
    musicaDescription->releaseAllInstances());
    enemigoDescription->releaseAllInstances());
    personajeDescription->releaseAllInstances());
    masterBank->unload());
    stringsBank->unload());
    soundSystem->unloadAll());*/

    FMOD_Studio_EventDescription_ReleaseAllInstances(ambienteDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(armaDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(mejoraDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(danyoDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(moverseDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(menuDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(musicaDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(enemigoDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(rondaDescription);
    FMOD_Studio_EventDescription_ReleaseAllInstances(personajeDescription);
    FMOD_Studio_Bank_Unload(masterBank);
    FMOD_Studio_Bank_Unload(stringsBank);
    FMOD_Studio_System_UnloadAll(system);
}

void TheFachada::chargeparameters() {
    /*ambienteDescription->getParameterDescriptionByName("ambiente",&paramAmbiente));

    armaDescription->getParameterDescriptionByName("armatipo",&paramArma));

    mejoraDescription->getParameterDescriptionByName("Mejora",&paramMejora));

    danyoDescription->getParameterDescriptionByName("Danyo",&paramDanyo));

    moverseDescription->getParameterDescriptionByName("moverse",&paramMoverse));

    menuDescription->getParameterDescriptionByName("Menu",&paramMenu));

    musicaDescription->getParameterDescriptionByName("musica",&paramMusica));

    enemigoDescription->getParameterDescriptionByName("vozenemigo",&paramEnemigo));

    personajeDescription->getParameterDescriptionByName("vozpersonaje",&paramPersonaje));*/

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(ambienteDescription, "ambiente",&paramAmbiente);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(armaDescription, "armatipo",&paramArma);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(mejoraDescription, "Mejora",&paramMejora);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(danyoDescription, "Danyo",&paramDanyo);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(moverseDescription, "moverse",&paramMoverse);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(menuDescription, "Menu",&paramMenu);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(musicaDescription, "musica",&paramMusica);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(enemigoDescription, "vozenemigo",&paramEnemigo);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(rondaDescription, "ronda",&paramRonda);

    FMOD_Studio_EventDescription_GetParameterDescriptionByName(personajeDescription, "vozpersonaje",&paramPersonaje);
}