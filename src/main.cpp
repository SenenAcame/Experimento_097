#include "main.hpp"
#include "cmp/aicmp.hpp"
#include "cmp/inputcmp2.hpp"
#include "cmp/physicscmp2.hpp"
#include "eng/engine.hpp"
#include "sys/aisys.hpp"
#include "sys/rensys2.hpp"
#include "sys/physys2.hpp"
#include "sys/colsys2.hpp"
#include "sys/inpsys2.hpp"
#include "sys/nodemapsys.hpp"
#include "util/types.hpp"

void game2() {
    EntyMan   EM;
    PhySys2   PhySys;
    RenSys2   RenSys;
    ColSys2   ColSys;
    InpSys2   InpSys;
    AISys     AISys;
    NodeMapSys  MapSys;
    TheEngine dev {1080, 720, &InpSys};
    dev.getDevice()->getCursorControl()->setVisible(false);
    auto cam = dev.getCamera();

    Enty& map = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(map, PhysicsCmp2{.y=-3.f});
    EM.addComponent<RenderCmp2> (map, dev.createModel("assets/salas_visibles.obj","assets/wall.bmp"));
    EM.addComponent<NodoCmp>    (map, NodoCmp{.nodos=MapSys.createNodes()});
    EM.addTag<TMap>(map);

    Enty& player = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(player, PhysicsCmp2{.x=0.5f, .y=-2.0f, .z=5.0f});
    EM.addComponent<RenderCmp2> (player, dev.createPlayer("assets/player_arm.obj","assets/fire.bmp", cam));
    EM.addComponent<InputCmp2>  (player);
    EM.addTag      <TPlayer>    (player);
    
    Enty& enemy1 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(enemy1, PhysicsCmp2{ .x= -50.0, .z=40.0});
    EM.addComponent<RenderCmp2> (enemy1, dev.createModel("assets/enemy.obj","assets/fire.bmp"));
    EM.addComponent<AICmp>      (enemy1, -10.0, -20.0, true, 1.0, 0.001, SB::Seek);
    EM.addTag      <TEnemy>     (enemy1);

    Enty& enemy2 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(enemy2, PhysicsCmp2{.x=0.0f, .z=40.0f});
    EM.addComponent<RenderCmp2> (enemy2, dev.createModel("assets/enemy.obj","assets/portal1.bmp"));
    EM.addComponent<AICmp>      (enemy2, -10.0, -20.0, true, 5.0, 2.0, SB::Seek);
    EM.addTag      <TEnemy>     (enemy2);

    //Enty& enemy3 = EM.createEntity();
    //EM.addComponent<PhysicsCmp2>(enemy3, PhysicsCmp2{.x=9.f, .z=30.f});
    //EM.addComponent<RenderCmp2> (enemy3, dev.createModel("assets/enemy.obj","assets/faerie2.bmp"));

    while(dev.run()){
        RenSys.update(EM, dev);
        MapSys.update(EM);
        AISys. update(EM);
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
    map.render->node = dev.createModel("assets/salas_visibles.obj","assets/wall.bmp");
    map.tipo = 'm';
    map.physics->y = -3.0f;
    
    Entity& player = EM.createEntity();
    player.render->node = dev.createPlayer("assets/player_arm.obj","assets/fire.bmp", cam);
    player.physics->x = 0.5f;
    player.physics->y = -2.0f;
    player.physics->z = 5.0f;
    player.tipo = 'p';
    //cam->setParent(e.render->node);
    //auto& v = cam->getTarget();

    auto& enemy1 = EM.createEntity();
    enemy1.tipo = 'e';
    enemy1.render->node = dev.createModel("assets/enemy.obj","assets/fire.bmp");
    enemy1.physics->z = 20.0f;
    enemy1.physics->x = 9.0f;

    auto& weapon = EM.createEntity();
    weapon.tipo = 'w';
    weapon.render->node = dev.createModel("assets/pistola.obj","assets/portal7.bmp");
    weapon.physics->z = 30.0f;
    weapon.physics->x = 5.0f;

    auto& enemy2 = EM.createEntity();
    enemy2.tipo = 'e';
    enemy2.render->node = dev.createModel("assets/enemy.obj","assets/portal1.bmp");
    enemy2.physics->z = 25.0f;
    enemy2.physics->x = 9.0f;

    auto& enemy3 = EM.createEntity();
    enemy3.tipo = 'e';
    enemy3.render->node = dev.createModel("assets/enemy.obj","assets/faerie2.bmp");
    enemy3.physics->z = 15.0f;
    enemy3.physics->x = 9.0f;

    //    Cosas para probar sonidos
    SouSys.createinstance(player,8);            //crear y asignarle instancia de sonido
    //SouSys.changesound(e,1);                  //cambiar a sonido 2(0=Agree, 1=Disagree, 2=Smoke)
    //SouSys.startsound(e);  
    //
    SouSys.createinstance(enemy1,0);
    SouSys.startsound(enemy1); 

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
    //game();
    game2();
}