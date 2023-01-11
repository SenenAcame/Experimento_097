#include "inputsystem.hpp"


//struct SMouseState
//    {
//        irr::core::position2di LastPosition;
//        irr::core::position2di Position;
//        bool LeftButtonDown;
//        SMouseState() : LeftButtonDown(false) { }
//    } MouseState;
//
//
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
            case irr::KEY_KEY_P:
                checkPressed(event, XK_P);
                break; 
            default:
                break;
        }
    }
   // if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
   //    {
   //        switch(event.MouseInput.Event)
   //        {
   //        case irr::EMIE_LMOUSE_PRESSED_DOWN:
   //            MouseState.LeftButtonDown = true;
   //            break;
//
   //        case irr::EMIE_LMOUSE_LEFT_UP:
   //            MouseState.LeftButtonDown = false;
   //            break;
//
   //        case irr::EMIE_MOUSE_MOVED:
   //            MouseState.Position.X = event.MouseInput.X;
   //            MouseState.Position.Y = event.MouseInput.Y;
   //            
   //            break;
//
   //        default:
   //            // We won't use the wheel
   //            break;
   //        }
   //    }
    return false;
}

//auto getMouseState(){
//
//    return MouseState;
//}

void InputSystem::onkeypressed(KeySym k){
    keyboard.keyPressed(k);
}

void InputSystem::onkeyreleased(KeySym k){
    keyboard.keyReleased(k);
}

void InputSystem::update(EntityManager<Entity>& EM, TheEngine& eng){
    EM.forall(eng, keyboard);
}