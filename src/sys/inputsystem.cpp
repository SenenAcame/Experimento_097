#include "inputsystem.hpp"
extern "C"{
    #include "../inc/tinyPTC/tinyptc.h"
}

InputSystem::InputSystem(){
    ptc_set_on_keypress(onkeypressed);
    ptc_set_on_keyrelease(onkeyreleased);
}

void InputSystem::onkeypressed(KeySym k){
    keyboard.keyPressed(k);
}

void InputSystem::onkeyreleased(KeySym k){
    keyboard.keyReleased(k);
}

void InputSystem::update(EntityManager<Entity>& EM){
    std::cout<<"Antes"<<"\n";
    ptc_process_events();
    std::cout<<"Despues"<<"\n";
    
    auto lambda = [](Entity& e){
        auto& phy = *(e.physics);
        auto& inp = *(e.input);

        if(keyboard.isKeyPressed(inp.key_left))
            phy.vx = -1;
        if(keyboard.isKeyPressed(inp.key_right))
            phy.vx = 1;
        if(keyboard.isKeyPressed(inp.key_up))
            phy.vy = 1;
        if(keyboard.isKeyPressed(inp.key_down))
            phy.vy = -1;
    };


    EM.forall(lambda);
    
//    //if(keyboard.isKeyPressed(XK_W))
}