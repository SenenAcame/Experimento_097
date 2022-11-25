extern "C"{
    #include "inc/tinyPTC/tinyptc.h"
}
#include "man/entitymanager.hpp"

int main(){
    ECS::EntityManager_t EntityMan;
    EntityMan.createEntity(16, 16, 0x0000FF00);
    return 0;
}