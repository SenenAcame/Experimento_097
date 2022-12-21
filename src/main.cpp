#include "main.hpp"
#include <irrlicht/vector3d.h>

void game(){
    InputSystem     InpSys;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    CollisionSystem ColSys;
    EntityManager<Entity> EM;
    TheEngine dev {1080, 720, &InpSys};

    //auto camera = dev.getCamera();
    //irr::core::vector3df tar = camera->getTarget();
    //tar.X=50; tar.Y=0; tar.Z=50;
    //camera->setTarget(tar);

    auto& e = EM.createEntity();
    e.tipo = 'p';
    e.render->node = dev.createSphere();
    e.physics->z = 50.0f;
    
    //irr::core::vector3df posi(e.physics->x,e.physics->y+10,e.physics->z-20);
    //camera->setPosition(posi);
    //camera->setParent(e.render->node);
    //irr::core::vector3df pos(0);
    //camera->setRotation(pos);

    auto& e2 = EM.createEntity();
    e2.tipo = 'e';
    e2.render->node = dev.createSphere();
    e2.physics->x = 30.0f;
    e2.physics->z = 100.0f;

    while(dev.run()){
        InpSys.update(EM);
        PhySys.update(EM);
        ColSys.update(EM);
        RenSys.update(EM, dev);
    }
}

int main(){
    game();
}

//extern "C"{
//    #include "inc/FMOD/inc/fmod_errors.h"
//}
//#include "man/entitymanager.hpp"
//#include "inc/FMOD/inc/fmod.hpp"
//#include "inc/FMOD/inc/fmod_studio.hpp"
//#include "inc/FMOD/inc/common.hpp"
//#include <string>
//#include <iostream>
//
//void ERRCHECK_FMOD (FMOD_RESULT result, const char * file, int line) {
//	if(result != FMOD_OK)
//	{
//        std::cerr << FMOD_ErrorString(result) << std::endl;
//		exit(-1);
//	}
//}
//
//#define ERRCHECK(_result) ERRCHECK_FMOD(_result, __FILE__, __LINE__)
//
//FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void* parameters);
//
//struct ProgrammerSoundContext {
//    FMOD::System* coreSystem;
//    FMOD::Studio::System* system;
//    const char* dialogueString;
//};
//
//#define CHECK_RESULT(op) \
//{ \
//    FMOD_RESULT res = (op); \
//    if (res != FMOD_OK) \
//    { \
//        return res; \
//    } \
//}
//
//FMOD_RESULT F_CALLBACK programmerSoundCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void *parameters) {
//    FMOD::Studio::EventInstance* eventInstance = (FMOD::Studio::EventInstance*)event;
//
//    if (type == FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND) {
//        FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;
//
//        // Get our context from the event instance user data
//        ProgrammerSoundContext* context = nullptr;
//        CHECK_RESULT( eventInstance->getUserData((void**)&context) );
//
//        // Find the audio file in the audio table with the key
//        FMOD_STUDIO_SOUND_INFO info;
//        CHECK_RESULT( context->system->getSoundInfo(context->dialogueString, &info) );
//
//        FMOD::Sound* sound = nullptr;
//        CHECK_RESULT( context->coreSystem->createSound(info.name_or_data, FMOD_LOOP_NORMAL | FMOD_CREATECOMPRESSEDSAMPLE | FMOD_NONBLOCKING | info.mode, &info.exinfo, &sound) );
//
//        // Pass the sound to FMOD
//        props->sound = (FMOD_SOUND*)sound;
//        props->subsoundIndex = info.subsoundindex;
//    }
//    else if (type == FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) {
//        FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;
//
//        // Obtain the sound
//        FMOD::Sound* sound = (FMOD::Sound*)props->sound;
//
//        // Release the sound
//        CHECK_RESULT( sound->release() );
//    }
//
//    return FMOD_OK;
//}
//
//int main(){
//    FMOD::System* coreSystem;
//    FMOD::Studio::System* soundSystem;
//    std::string dialogueString;
//
//    ERRCHECK(FMOD::Studio::System::create(&soundSystem));
//    ERRCHECK(soundSystem->getCoreSystem(&coreSystem));
//    ERRCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
//    ERRCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
//    ERRCHECK(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
//
//    FMOD::Studio::Bank* masterBank = nullptr;
//    FMOD::Studio::Bank* stringsBank = nullptr;
//    FMOD::Studio::Bank* voicesBank = nullptr;
//
//    ERRCHECK(soundSystem->loadBankFile("src/assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
//    ERRCHECK(soundSystem->loadBankFile("src/assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
//    ERRCHECK(soundSystem->loadBankFile("src/assets/FMOD_BANKS/Voices.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &voicesBank) );
//
//    unsigned int bankIndex = 0;
//    static const char* const banks[] = { "src/assets/FMOD_BANKS/Dialogue_CT.bank", "src/assets/FMOD_BANKS/Dialogue_T.bank"};
//
//    FMOD::Studio::Bank* localizedBank = nullptr;
//    ERRCHECK(soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );
//
//    FMOD::Studio::EventDescription* eventDescription = nullptr;
//    ERRCHECK(soundSystem->getEvent("event:/Dialogue", &eventDescription) );
//
//    FMOD::Studio::EventInstance* eventInstance = nullptr;
//    ERRCHECK(eventDescription->createInstance(&eventInstance));
//
//    unsigned int dialogueIndex = 0;
//    static const char* const dialogue[] = {"agree", "disagree", "smoke"};
//
//    ProgrammerSoundContext programmerSoundContext;
//    programmerSoundContext.system = soundSystem;
//    programmerSoundContext.coreSystem = coreSystem;
//    programmerSoundContext.dialogueString = dialogue[dialogueIndex];
//
//    ERRCHECK( eventInstance->setUserData(&programmerSoundContext) );
//    ERRCHECK( eventInstance->setCallback(programmerSoundCallback, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );
//
//    int n = 3;
//    do{
//        if (n==1){
//            ERRCHECK( localizedBank->unload() );
//
//            bankIndex = (bankIndex < 1) ? bankIndex + 1 : 0;
//            ERRCHECK( soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );
//        }
//
//        if (n==2){
//            dialogueIndex = (dialogueIndex < 2) ? dialogueIndex + 1 : 0;
//            programmerSoundContext.dialogueString = dialogue[dialogueIndex];
//        }
//
//        if (n==3){
//            ERRCHECK( eventInstance->start() );
//        }
//        
//        ERRCHECK(soundSystem->update() );
//
//        std::cout<< "Press 1 to change team" << std::endl;
//        std::cout<< "Press 2 to change voice line" << std::endl;
//        std::cout<< "Press 3 to play the event" << std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Team:"<<std::endl;
//        std::string out1 = bankIndex == 0 ? ">" : " ";
//        std::cout<< out1 << " Counter_Terror team" <<std::endl;
//        out1 = bankIndex == 1 ? ">" : " ";
//        std::cout<< out1 << " Terror team" <<std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Line:"<<std::endl;
//        out1 = dialogueIndex == 0 ? ">" : " ";
//        std::cout<< out1 << " Agree!" <<std::endl;
//        out1 = dialogueIndex == 1 ? ">" : " ";
//        std::cout<< out1 << " Disagree!" <<std::endl;
//        out1 = dialogueIndex == 2 ? ">" : " ";
//        std::cout<< out1 << " Smoke!" <<std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Press 8 to quit"<<std::endl;
//
//        std::cin >> n;
//        std::cout << "\x1B[2J\x1B[H";
//    }while (n != 8);
//
//    ERRCHECK(eventDescription->releaseAllInstances());
//    ERRCHECK(masterBank->unload());
//    ERRCHECK(stringsBank->unload());
//    ERRCHECK(localizedBank->unload());
//    ERRCHECK(voicesBank->unload());
//    ERRCHECK(soundSystem->unloadAll());
//    return 0;
//}

//#include "sys/soundsystem.hpp"
//
//
//int main(){
//
//    SoundSystem_t soundsystem;
//    int n=0;
//    do{
//        std::cout<< "Press 1 to change team" << std::endl;
//        std::cout<< "Press 2 to change voice line" << std::endl;
//        std::cout<< "Press 3 to play the event" << std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Team:"<<std::endl;
//        std::string out1 = soundsystem.getBankIndex() == 0 ? ">" : " ";
//        std::cout<< out1 << " Counter_Terror team" <<std::endl;
//        out1 = soundsystem.getBankIndex() == 1 ? ">" : " ";
//        std::cout<< out1 << " Terror team" <<std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Line:"<<std::endl;
//        out1 = soundsystem.getDialogueIndex() == 0 ? ">" : " ";
//        std::cout<< out1 << " Agree!" <<std::endl;
//        out1 = soundsystem.getDialogueIndex() == 1 ? ">" : " ";
//        std::cout<< out1 << " Disagree!" <<std::endl;
//        out1 = soundsystem.getDialogueIndex() == 2 ? ">" : " ";
//        std::cout<< out1 << " Smoke!" <<std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Press 8 to quit"<<std::endl;
//
//        std::cin >> n;
//        std::cout << "\x1B[2J\x1B[H";
//        soundsystem.controller(n);
//        soundsystem.update();
//    }while (n != 8);
//    soundsystem.close();
//    return 0;
//}