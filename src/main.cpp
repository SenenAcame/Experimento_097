#include "main.hpp"

void game(){
    TheEngine dev {720, 480};
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

    auto& e2 = EM.createEntity();
    e2.render->node = dev.createSphere();
    e2.physics->z = 40.0f;
    e2.physics->x = -5.0f;
    e2.physics->vz = 0.05f;

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