#include "inputsystem.hpp"
#include "soundsystem.hpp"

void InputSystem::checkPressed(const irr::SEvent& event, KeySym k){
    if(event.KeyInput.PressedDown){
        keyboard.keyPressed(k);
    }
    else{
        keyboard.keyReleased(k);
    }
}

bool InputSystem::OnEvent(const irr::SEvent& event){
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
        switch (event.KeyInput.Key) {
            case irr::KEY_KEY_W:
                checkPressed(event, XK_W);
                break;
            case irr::KEY_KEY_A:
                checkPressed(event, XK_A);
                break;
            case irr::KEY_KEY_S:
                checkPressed(event, XK_S);
                break;
            case irr::KEY_KEY_D:
                checkPressed(event, XK_D);
                break;
            case irr::KEY_KEY_B:
                checkPressed(event, XK_B);
                break; 
            case irr::KEY_KEY_N:
                checkPressed(event, XK_N);
                break; 
            case irr::KEY_KEY_M:
                checkPressed(event, XK_M);
                break; 
            case irr::KEY_KEY_P:
                checkPressed(event, XK_P);
                break; 
            default:
                break;
        }
    }
    return false;
}

void InputSystem::onkeypressed(KeySym k){
    keyboard.keyPressed(k);
}

void InputSystem::onkeyreleased(KeySym k){
    keyboard.keyReleased(k);
}

void InputSystem::update(EntityManager<Entity>& EM, TheEngine& eng, SoundSystem_t& sounsys){
    EM.forall(eng, keyboard, sounsys);
}