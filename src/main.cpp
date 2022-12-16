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

    //tengo que poner lo de entity.hpp en el manager de alguna forma
    //using Player_t = Entity<Tags<TPlayer>, CPhysisc, CRender, CInput> ;
    /*Player_t player{
        
        std::make_unique<CPhysics>(20.0f, 5.0f),
        std::make_unique<CRender>(dev.createSphere),
        std::make_unique<CInput>()

    };*/

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
        RenSys.update(EM, dev);
    }
}

int main(){
    game();
}