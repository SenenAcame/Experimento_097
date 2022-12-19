#include "inputsystem.hpp"
#include <iostream>

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
            default:    
                std::cout<<"Se ha pulsado otra tecla\n";
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

void InputSystem::update(EntityManager<Entity>& EM){
    auto lambda = [](Entity& e){
        if(e.tipo == 'p'){
            auto& phy = *(e.physics);
            auto& inp = *(e.input);
            phy.vx = 0;
            phy.vy = 0;
            if(keyboard.isKeyPressed(inp.key_left)){
                phy.vx = -0.1;
            }
            if(keyboard.isKeyPressed(inp.key_right)){
                phy.vx = 0.1;
            }
            if(keyboard.isKeyPressed(inp.key_up)){
                phy.vy = 0.1;
            }
            if(keyboard.isKeyPressed(inp.key_down)){
                phy.vy = -0.1;
            }
        }
    };
    EM.forall(lambda);
}