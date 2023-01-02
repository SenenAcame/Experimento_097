#include "main.hpp"
#include "util/slotmap.hpp"

void game(){
    InputSystem     InpSys;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;
    CollisionSystem ColSys;
    EntityManager<Entity> EM;
    TheEngine dev {1080, 720, &InpSys};

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

//struct  NameComponent{
//    char name[8] {"noname"};
//};

int main(){
    game();
//    Slotmap<NameComponent, 4> names;
//    using key_type = Slotmap<NameComponent, 4>::key_type;
//    std::array<key_type, 8> key;
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<"\n";
//
//    key[0] = names.push_back(NameComponent{"Myname"});
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<" << Key id: "<<key[0].id<<" | Key gen: "<<key[0].gen<<"\n";
//
//    key[1] = names.push_back(NameComponent{"Twoname"});
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<" << Key id: "<<key[1].id<<" | Key gen: "<<key[1].gen<<"\n";
//
//    key[2] = names.push_back(NameComponent{"3name"});
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<" << Key id: "<<key[2].id<<" | Key gen: "<<key[2].gen<<"\n";
//
//    names.erase(key[0]);
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<" >> Key id: "<<key[0].id<<" | Key gen: "<<key[0].gen<<"\n";
//   
//    names.erase(key[1]);
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<" >> Key id: "<<key[1].id<<" | Key gen: "<<key[1].gen<<"\n";
//
//    key[3] = names.push_back(NameComponent{"Youname"});
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<" << Key id: "<<key[3].id<<" | Key gen: "<<key[3].gen<<"\n";
//
//    key[4] = names.push_back(NameComponent{"Nexname"});
//    std::cout<<"Capacity: "<<names.capacity()<<" | Size: "<<names.size()<<" | Freelist: "<<names.freelist()<<" | Generation: "<<names.generation()<<" << Key id: "<<key[4].id<<" | Key gen: "<<key[4].gen<<"\n";
//
//    for(auto& item : names){
//        std::cout<<"Item | Nombre: "<<item.name<<"\n";
//    }
}