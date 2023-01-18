#include "main.hpp"
#include "util/types.hpp"
#include "sys/physys2.hpp"

//void printEntity(Enty const& e){
//    std::cout<<"Mascara de componentes: "<<e.hasCMP<PhysicsCmp2>();
//    std::cout<<e.hasCMP<RenderCmp2>();
//    std::cout<<e.hasCMP<InputCmp2>();
//    std::cout<<"\n";
//}
//
//void printTagEntity(Enty const& e){
//    std::cout<<"Mascara de tags: "<<e.hasTAG<TPlayer>();
//    std::cout<<e.hasTAG<TEnemy>();
//    std::cout<<e.hasTAG<TBullet>();
//    std::cout<<"\n";
//}

void game(){
    EntyMan EM;
    InputSystem InpSys;
    PhySys2     PhySys;
    TheEngine   dev {1080, 720, &InpSys};

    Enty& e1 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(e1);
    EM.addComponent<RenderCmp2>(e1, dev.createSphere());

    while(true){
        PhySys.update(EM);
    }

    /*
    InputSystem           InpSys;
    PhysicsSystem         PhySys;
    RenderSystem          RenSys;
    CollisionSystem       ColSys;
    EntityManager<Entity> EM;
    TheEngine             dev {1080, 720, &InpSys};
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
}

int main(){
    game();
}