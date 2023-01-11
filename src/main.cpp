#include "main.hpp"
#include <iostream>

void game(){
    InputSystem     InpSys;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    CollisionSystem ColSys;
    EntityManager<Entity> EM;
    TheEngine dev {1080, 720, &InpSys};

    

    auto& map = EM.createEntity();
    map.render->node = dev.createMap();
    map.tipo = 'm';
    map.physics->y = -3.0f;
    
    auto& e = EM.createEntity();
    e.render->node = dev.createPlayer();
     irr::core::vector3df posP(5,2,20);
    e.render->node->setPosition(posP);
    //e.physics->z = 20.0f;
    //e.physics->x = 0.0f;
    //e.physics->y = 0.0f;
    e.tipo = 'p';
    //irr::core::vector3df rot(-90,0,0);
    //e.render->node->setRotation(rot);
    irr::core::vector3df eye = dev.normalizeVector3(e.getLookAtVector());
    
    //camera
    auto camera = dev.getCamera();
    irr::core::vector3df tar = camera->getTarget();
    //tar.X=50; tar.Y=0; tar.Z=50;
    //camera->setTarget(tar);

    irr::core::vector3df lookAT(1,0,0);
    e.setLookAtVector(lookAT);
    
    
    irr::core::vector3df posi(e.physics->x,e.physics->y,e.physics->z-10);
    irr::core::vector3df posi2( 
         camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z+10);
    camera->setPosition(posi);
    camera->setParent(e.render->node);
    camera->bindTargetAndRotation(true); 
    irr::core::vector3df pos(0);
    camera->setRotation(pos);
    camera->setTarget(dev.normalizeVector3(lookAT));
    std::cout<<"Este es el vector de lookAt: " << camera->getTarget().X<< ", "
    << camera->getTarget().Y<< ", " << camera->getTarget().Z<< ", ";
    std::cout<<"Esta es la posicion de e: " << e.render->node->getAbsolutePosition().X<< ", "
    << e.render->node->getAbsolutePosition().Y<< ", " << e.render->node->getAbsolutePosition().Z<< ", ";
    
    

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

    ///irr::scene::ICameraSceneNode *cam= dev.getCamera();
    ///cam->setPosition(irr::core::vector3df(0,0,-10));
    ///cam->setParent(e.render->node);
    //cam->bindTargetAndRotation(true); 
    //falta poner lookat al vector posicionActual + vectorForWard	

    while(dev.run()){
        RenSys.update(EM, dev);
        InpSys.update(EM, dev);
        PhySys.update(EM);
        ColSys.update(EM);
    }
}

int main(){
    game();
}