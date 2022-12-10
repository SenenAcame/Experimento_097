#include "main.hpp"
#include <iostream>

void game(){
    TheEngine dev {1080, 720};
    EntityManager<Entity> EM;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    InputSystem     InpSys;
    CollisionSystem ColSys;

    auto& e = EM.createEntity();
    e.render->node = dev.createSphere();
    e.physics->z = 20.0f;
    e.physics->x = 5.0f;
    e.physics->vz = 0.1f;
//    std::cout<<e.entityID<<"\n";
//    std::cout<<e.physics->componentID<<"\n";
//    std::cout<<e.physics->entityID<<"\n";
//    std::cout<<e.render->componentID<<"\n";
//    std::cout<<e.render->entityID<<"\n";
//    std::cout<<e.input->componentID<<"\n";
//    std::cout<<e.input->entityID<<"\n";
//    std::cout<<e.collision->componentID<<"\n";
//    std::cout<<e.collision->entityID<<"\n";

    auto& e2 = EM.createEntity();
    e2.render->node = dev.createSphere();
    e2.physics->z = 40.0f;
    e2.physics->x = -5.0f;
    e2.physics->vz = 0.05f;
//    std::cout<<e2.entityID<<"\n";
//    std::cout<<e2.physics->componentID<<"\n";
//    std::cout<<e2.physics->entityID<<"\n";
//    std::cout<<e2.render->componentID<<"\n";
//    std::cout<<e2.render->entityID<<"\n";
//    std::cout<<e2.input->componentID<<"\n";
//    std::cout<<e2.input->entityID<<"\n";
//    std::cout<<e2.collision->componentID<<"\n";
//    std::cout<<e2.collision->entityID<<"\n";

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