#include "main.hpp"

void game(){
    TheEngine dev {1080, 720};
    EntityManager<Entity> EM;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    InputSystem     InpSys;
    CollisionSystem ColSys;

    auto& e = EM.createEntity();
    e.render->node = dev.createSphere();
//    e.physics->x = 9.0f;
//    e.physics->y = 9.0f;
    e.physics->z = 50.0f;
    e.physics->vx = 0.1f;
    e.physics->vy = 0.1f;
    e.physics->vz = 0.1f;

    auto& e2 = EM.createEntity();
    e2.render->node = dev.createSphere();
    e2.physics->x = 30.0f;
	e2.physics->y = 30.0f;
    e2.physics->z = 80.0f;

    auto& e3 = EM.createEntity();
    e3.render->node = dev.createSphere();
//    e3.physics->x = 30.0f;
	e3.physics->x = -5.0f;
    e3.physics->y = -10.0f;
    e3.physics->z = 50.0f;

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