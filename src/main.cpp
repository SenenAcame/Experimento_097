#include "main.hpp"
#include "cmp/entity2.hpp"
#include "cmp/rendercmp2.hpp"
#include "cmp/physicscmp2.hpp"
#include "cmp/inputcmp2.hpp"
#include "man/cmpstorage2.hpp"
#include "man/entityman2.hpp"
#include "util/gameengine.hpp"
//#include "util/metaprogramming.hpp"
#include <iostream>
//#include <memory>

void seetype(auto) { std::cout<<__PRETTY_FUNCTION__<<"\n"; }

struct TPlayer { static constexpr uint8_t id {0}; };
struct TEnemy  { static constexpr uint8_t id {1}; };
struct TBullet { static constexpr uint8_t id {2}; };

using ComponentList = MP::Typelist<PhysicsCmp2, RenderCmp2, InputCmp2>;
using TagList       = MP::Typelist<TPlayer, TEnemy, TBullet>;

void printEntity(EntityMan2<ComponentList, TagList>::Entity const& e){
    std::cout<<"Mascara de componentes: "<<e.hasCMP<PhysicsCmp2>();
    std::cout<<e.hasCMP<RenderCmp2>();
    std::cout<<e.hasCMP<InputCmp2>();
    std::cout<<"\n";
}

void printTagEntity(EntityMan2<ComponentList, TagList>::Entity const& e){
    std::cout<<"Mascara de tags: "<<e.hasTAG<TPlayer>();
    std::cout<<e.hasTAG<TEnemy>();
    std::cout<<e.hasTAG<TBullet>();
    std::cout<<"\n";
}

void game(){
    EntityMan2<ComponentList, TagList> EM;
    //EntityMan2<ComponentList, TagList>::Entity e;
    auto& e = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(e,1,2,3);

    printTagEntity(e);



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
}

int main(){
    game();
}