//extern "C"{
//    #include "tinyPTC/tinyptc.h"
//}
#include <irrlicht/irrlicht.h>
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