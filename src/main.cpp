#include <irrlicht/irrlicht.h>
#include "eng/engine.hpp"
#include "man/entitymanager.hpp"
#include "sys/physicsystem.hpp"
#include "sys/rendersystem.hpp"
#include "sys/inputsystem.hpp"


void game(){

    

    //TheEngine dev {640, 480};
    EntityManager<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>> EM;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    InputSystem     InpSys;

    //tengo que poner lo de entity.hpp en el manager de alguna forma
    using Player_t = Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent> ;
    Player_t player{
        
        std::make_unique<PhysicsComponent>(),
        std::make_unique<RenderComponent>(),
        std::make_unique<InputComponent>()

    };
    player.c2->node = dev.createSphere();
    player.c1->z = 20.0f;
    player.c1->x = 5.0f;

    //auto& e = EM.createEntity();
    //e.render->node = dev.createSphere();
    //e.physics->z = 20.0f;
    //e.physics->x = 5.0f;
    //e.physics->vz = 0.1f;
//
    //auto& e2 = EM.createEntity();
    //e2.render->node = dev.createSphere();
    //e2.physics->z = 40.0f;
    //e2.physics->x = -5.0f;
    //e2.physics->vz = 0.05f;

    while(dev.run()){
        InpSys.update(EM);
        PhySys.update(EM);
        RenSys.update(EM, dev);
    }
}

int main(){
    game();
}