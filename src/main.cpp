#include "main.hpp"

void game(){
    InputSystem     InpSys;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    CollisionSystem ColSys;
    SoundSystem_t   SouSys;
    EntityManager<Entity> EM;
    TheEngine dev {1080, 720, &InpSys};

    auto cam = dev.getCamera();

    cam->setFOV(1);
    cam->setPosition({-6,2,20});
    cam->setTarget({200,0,20});
    cam->setNearValue(2);
    
    //cam->setFarValue(4000);
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
    
    auto& e = EM.createEntity();
    e.render->node = dev.createPlayer();
    e.physics->z = 20.0f;
    e.physics->x = -1.0f;
    e.tipo = 'p';

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
}