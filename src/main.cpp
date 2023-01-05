#include "main.hpp"
#include "cmp/entity2.hpp"
#include "cmp/rendercmp2.hpp"
#include "cmp/physicscmp2.hpp"
#include "cmp/inputcmp2.hpp"
#include <iostream>
//#include <memory>

void game(){
    /*
    InputSystem     InpSys;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    CollisionSystem ColSys;
    EntityManager<Entity> EM;
    TheEngine dev {1080, 720, &InpSys};
    */

    //auto camera = dev.getCamera();
    //irr::core::vector3df tar = camera->getTarget();
    //tar.X=50; tar.Y=0; tar.Z=50;
    //camera->setTarget(tar);

    //irr::scene::ICameraSceneNode* cam = dev.getCamera();
    //cam->setPosition(irr::core::vector3df(0,5,-10));
    //cam->setParent(e.render->node);
    
    //irr::core::vector3df posi(e.physics->x,e.physics->y+10,e.physics->z-20);
    //camera->setPosition(posi);
    //camera->setParent(e.render->node);
    //irr::core::vector3df pos(0);
    //camera->setRotation(pos);

    /*
    auto& map = EM.createEntity();
    map.render->node = dev.createMap();
    map.tipo = 'm';
    map.physics->y = -3.0f;
    
    auto& e = EM.createEntity();
    e.render->node = dev.createPlayer();
    e.physics->z = 20.0f;
    e.tipo = 'p';

    auto& e2 = EM.createEntity();
    e2.tipo = 'e';
    e2.render->node = dev.createEnemy();
    e2.physics->z = 20.0f;
    e2.physics->x = 9.0f;

    auto& e3 = EM.createEntity();
    e3.tipo = 'w';
    e3.render->node = dev.createWeapon1();
    e3.physics->z = 30.0f;
    e3.physics->x = 5.0f;
    */

    ///irr::scene::ICameraSceneNode *cam= dev.getCamera();
    ///cam->setPosition(irr::core::vector3df(0,0,-10));
    ///cam->setParent(e.render->node);
    //cam->bindTargetAndRotation(true); 
    //falta poner lookat al vector posicionActual + vectorForWard	
    /*
    while(dev.run()){
        RenSys.update(EM, dev);
        InpSys.update(EM, dev);
        PhySys.update(EM);
        ColSys.update(EM);
    }
    */
    /*
    Entity2<PhysicsCmp2, RenderCmp2> ent{
        std::make_unique<PhysicsCmp2>(1,2,3,4,5,6),
        std::make_unique<RenderCmp2> ('@')
    };
    */
    Entity2<PhysicsCmp2, RenderCmp2, InputCmp2> player{
        std::make_unique<PhysicsCmp2>(1,2,3,4,5,6),
        std::make_unique<RenderCmp2> ('@'),
        std::make_unique<InputCmp2>  ()
    };

    Entity2<PhysicsCmp2, RenderCmp2> enemy{
        std::make_unique<PhysicsCmp2>(1,2,3,4,5,6),
        std::make_unique<RenderCmp2> ('%')
    };

}

int main(){
    game();
}