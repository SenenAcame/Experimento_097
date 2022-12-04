#include <irrlicht/irrlicht.h>
#include "eng/engine.hpp"
#include "man/entitymanager.hpp"
#include "sys/physicsystem.hpp"
#include "sys/rendersystem.hpp"
#include "sys/inputsystem.hpp"

void game(){
    TheEngine dev {640, 480};
    EntityManager<Entity> EM;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    InputSystem     InpSys;

    auto& e = EM.createEntity();
    e.render.node = dev.createSphere();
    e.physics.z = 10.0f;
    e.physics.vz = 0.2f;

    while(dev.run()){
        InpSys.update(EM);
        PhySys.update(EM);
        RenSys.update(EM, dev);
    }
}

int main(){
    game();
}