#include "fachada.hpp"
#include <iostream>

TheFachada::TheFachada() {}

void TheFachada::init() {

    FMOD_Studio_System_Create(&system, 131589);
    FMOD_Studio_System_GetCoreSystem(system, &coreSystem);
    FMOD_System_SetSoftwareFormat(coreSystem, 0, FMOD_SPEAKERMODE_5POINT1, 0);
    FMOD_System_SetOutput(coreSystem, FMOD_OUTPUTTYPE_AUTODETECT);
    FMOD_Studio_System_Initialize(system, 1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_3D_RIGHTHANDED, 0);

    chargebanks();
}

void TheFachada::update() { 
    FMOD_Studio_System_Update(system) ; 
}

void TheFachada::chargebanks() {
    masterBank = nullptr;
    stringsBank = nullptr;

    FMOD_Studio_System_LoadBankFile(system, "assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) ;
    FMOD_Studio_System_LoadBankFile(system, "assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) ;

    createdescriptions();
    chargeparameters();
}

void TheFachada::createdescriptions() {
    ambienteDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Ambientes/Ambientes", &ambienteDescription) ;

    armaDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Arma", &armaDescription) ;

    mejoraDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Comprar", &mejoraDescription) ;

    danyoDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Daño", &danyoDescription) ;

    moverseDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Moverse", &moverseDescription) ;

    menuDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Menus/Menu", &menuDescription) ;

    musicaDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Musica/Musica menu", &musicaDescription) ;

    enemigoDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Voces/Enemigos", &enemigoDescription) ;

    rondaDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Efectos/Ronda", &rondaDescription) ;

    personajeDescription = nullptr;
    FMOD_Studio_System_GetEvent(system, "event:/Voces/Personaje", &personajeDescription) ;
}

ProgrammerSoundContext TheFachada::createinstance(int tipo) {
    ProgrammerSoundContext sound;
    FMOD_STUDIO_EVENTINSTANCE* eventInstance = nullptr;

    switch(tipo){
        case 0:
            FMOD_Studio_EventDescription_CreateInstance(ambienteDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramAmbiente.id), 0.0f, false);
            break;
        case 1:
            FMOD_Studio_EventDescription_CreateInstance(armaDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramArma.id), 0.0f, false);
            break;
            
        case 2:
            FMOD_Studio_EventDescription_CreateInstance(mejoraDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMejora.id), 0.0f, false);
            break;
        case 3:
            FMOD_Studio_EventDescription_CreateInstance(danyoDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramDanyo.id), 0.0f, false);
            break;
        case 4:
            FMOD_Studio_EventDescription_CreateInstance(moverseDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMoverse.id), 0.0f, false);
            break;
        case 5:
            FMOD_Studio_EventDescription_CreateInstance(menuDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMenu.id), 0.0f, false);
            break;
        case 6:
            FMOD_Studio_EventDescription_CreateInstance(musicaDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramMusica.id), 0.0f, false);
            break;
        case 7:
            FMOD_Studio_EventDescription_CreateInstance(enemigoDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramEnemigo.id), 0.0f, false);
            break;
        case 8:
            FMOD_Studio_EventDescription_CreateInstance(rondaDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramRonda.id), 0.0f, false);
            break;
        default:
            FMOD_Studio_EventDescription_CreateInstance(personajeDescription, &eventInstance);
            FMOD_Studio_EventInstance_SetParameterByID(eventInstance, (sound.id=paramPersonaje.id), 0.0f, false);
    }

    sound.system = system;
    sound.coreSystem = coreSystem;
    sound.sound = eventInstance;

    return sound;
}

void TheFachada::changesound(SoundCmp& s) {
    FMOD_Studio_EventInstance_SetParameterByID(s.programmerSoundContext.sound, s.programmerSoundContext.id, static_cast<float>(s.parametro), false);
}

void TheFachada::startsound(SoundCmp& s) {
    if(isPlaying(s)) stopsound(s);
     FMOD_Studio_EventInstance_Start(s.programmerSoundContext.sound) ;
}

void TheFachada::set3DAttributes(SoundCmp& s, PhysicsCmp2& enty) {
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

     FMOD_Studio_EventInstance_Stop(s.programmerSoundContext.sound, FMOD_STUDIO_STOP_IMMEDIATE) ;
}

void TheFachada::close() {

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

void TheFachada::changeVCAVolume(int tipo, float volumen){
    FMOD_STUDIO_VCA *vca;
    switch(tipo){
        case 0:
            FMOD_Studio_System_GetVCA(system, "vca:/Ambientes", &vca);
            break;
        case 1:
            FMOD_Studio_System_GetVCA(system, "vca:/Musica", &vca);
            break;
        case 2:
            FMOD_Studio_System_GetVCA(system, "vca:/SFX", &vca);
            break;
        case 3:
            FMOD_Studio_System_GetVCA(system, "vca:/Voces", &vca);
            break;
    }
    if(volumen>0 && FMOD_Studio_VCA_GetVolume(vca,0,0)>0)
        FMOD_Studio_VCA_SetVolume(vca, FMOD_Studio_VCA_GetVolume(vca,0,0)+volumen);
    else if(volumen<0 && FMOD_Studio_VCA_GetVolume(vca,0,0)<1){
        FMOD_Studio_VCA_SetVolume(vca, FMOD_Studio_VCA_GetVolume(vca,0,0)+volumen);
    }
}

void TheFachada::changeVCAMaster(float volumen){
    for(int i=0; i<4;i++){
        changeVCAVolume(i, volumen);
    }
}