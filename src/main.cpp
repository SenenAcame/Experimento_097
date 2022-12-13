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
    e.physics->z = 50.0f;
	e.physics->vx = 0.1f;

    auto& e2 = EM.createEntity();
    e2.render->node = dev.createSphere();
	e2.physics->x = -30.0f;
    e2.physics->z = 50.0f;
    e2.physics->vx = 0.3f;
    e2.physics->vy = 0.3f;

    auto& e3 = EM.createEntity();
    e3.render->node = dev.createSphere();
	e3.physics->x = 30.0f;
    e3.physics->z = 50.0f;
//    e3.physics->vx = 0.3f;

    auto& e4 = EM.createEntity();
    e4.render->node = dev.createSphere();
	e4.physics->x = 50.0f;
    e4.physics->z = 50.0f;

    auto& e5 = EM.createEntity();
    e5.render->node = dev.createSphere();
	e5.physics->x = -50.0f;
    e5.physics->z = 50.0f;

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