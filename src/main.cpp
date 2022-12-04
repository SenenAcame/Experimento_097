#include <irrlicht/irrlicht.h>
#include "eng/engine.hpp"
#include "cmp/entity.hpp"
#include "man/entitymanager.hpp"
#include "sys/physicsystem.hpp"
#include "sys/rendersystem.hpp"

void game(){
    TheEngine dev {640, 480};
    EntityManager<Entity> EM;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;

    auto& e = EM.createEntity();
    e.render.node = dev.createSphere();
    e.physics.z = 10.0f;
    e.physics.vz = 0.2f;

    while(dev.run()){
        PhySys.update(EM);
        RenSys.update(EM, dev);
    }
}

int main(){
    game();
}