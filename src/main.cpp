#include "main.hpp"
#include "cmp/inputcmp2.hpp"
#include "cmp/physicscmp2.hpp"
#include "cmp/rendercmp2.hpp"
#include "sys/rensys2.hpp"
#include "sys/physys2.hpp"
#include "sys/colsys2.hpp"
#include "sys/inpsys2.hpp"
#include "util/types.hpp"

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

void game2() {
    EntyMan     EM;
    PhySys2     PhySys;
    RenSys2     RenSys;
    ColSys2     ColSys;
    InpSys2     InpSys;
    TheEngine   dev {1080, 720, &InpSys};

    Enty& e1 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(e1, 5.f, 0.f, 20.f, 0.f, 0.f, 0.f);
    EM.addComponent<RenderCmp2> (e1, dev.createSphere());
    EM.addComponent<InputCmp2>  (e1);

    Enty& e2 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(e2, -5.f, 0.f, 20.f, 0.f, 0.f, 0.f);
    EM.addComponent<RenderCmp2> (e2, dev.createSphere());

    //if(e2.hasCMP<PhysicsCmp2>())
    //    std::cout<<"Componente existe\n";
    //else
    //    std::cout<<"Componente no existe\n";
    //
    //if(e2.hasCMP<RenderCmp2>())
    //    std::cout<<"Componente existe\n";
    //else
    //    std::cout<<"Componente no existe\n";
    //
    //if(e2.hasCMP<InputCmp2>())
    //    std::cout<<"Componente existe\n";
    //else
    //    std::cout<<"Componente no existe\n";


    while(dev.run()){
        RenSys.update(EM, dev);
        PhySys.update(EM);
        InpSys.update(EM, dev);
        ColSys.update(EM);
    }
}

void game(){
    InputSystem     InpSys;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    CollisionSystem ColSys;
    SoundSystem_t   SouSys;
    EntityManager<Entity> EM;
    TheEngine dev {1080, 720, &InpSys};

    auto cam = dev.getCamera();
    dev.getDevice()->getCursorControl()->setVisible(false);
    cam->setFOV(1);
    cam->setPosition({-6,2,20});
    cam->setTarget({200,0,20});

    //cam->setNearValue(2);
    //cam->setFarValue(5000);
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

    auto& map = EM.createEntity();
    map.render->node = dev.createMap();
    map.tipo = 'm';
    map.physics->y = -3.0f;
    
    Entity& e = EM.createEntity();
    e.render->node = dev.createPlayer();
    e.physics->x = 0.5f;
    e.physics->y = -2.0f;
    e.physics->z = 5.0f;
    
    e.tipo = 'p';

    e.render->node->setParent(cam);
    //cam->setParent(e.render->node);
    //auto& v = cam->getTarget();

    auto& e2 = EM.createEntity();
    e2.tipo = 'e';
    e2.render->node = dev.createEnemy("assets/fire.bmp");
    e2.physics->z = 20.0f;
    e2.physics->x = 9.0f;

    auto& e3 = EM.createEntity();
    e3.tipo = 'w';
    e3.render->node = dev.createWeapon1();
    e3.physics->z = 30.0f;
    e3.physics->x = 5.0f;

    auto& e4 = EM.createEntity();
    e4.tipo = 'e';
    e4.render->node = dev.createEnemy("assets/portal1.bmp");
    e4.physics->z = 25.0f;
    e4.physics->x = 9.0f;

    auto& e5 = EM.createEntity();
    e5.tipo = 'e';
    e5.render->node = dev.createEnemy("assets/faerie2.bmp");
    e5.physics->z = 15.0f;
    e5.physics->x = 9.0f;

//    Cosas para probar sonidos
    SouSys.createinstance(e,8);                 //crear y asignarle instancia de sonido
    //SouSys.changesound(e,1);                  //cambiar a sonido 2(0=Agree, 1=Disagree, 2=Smoke)
    //SouSys.startsound(e);  
//
    SouSys.createinstance(e2,0);
    SouSys.startsound(e2); 

    ///irr::scene::ICameraSceneNode *cam= dev.getCamera();
    ///cam->setPosition(irr::core::vector3df(0,0,-10));
    ///cam->setParent(e.render->node);
    //cam->bindTargetAndRotation(true); 
    //falta poner lookat al vector posicionActual + vectorForWard	
    
    while(dev.run()){
        RenSys.update(EM, dev);
        InpSys.update(EM, dev, SouSys);
        PhySys.update(EM);
        ColSys.update(EM);
        SouSys.update();
    }
}

int main(){
    game();
    //game2();
}