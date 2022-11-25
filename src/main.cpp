extern "C"{
    #include "inc/tinyPTC/tinyptc.h"
}
#include "man/entitymanager.hpp"

int main(){
//    ptc_open("windows", 1080, 720);
//
//    for(;;);
//
//    ptc_close();
    ECS::EntityManager_t EntityMan;
    EntityMan.createEntity(16, 16, 0x0000FF00);
    return 0;
    
}