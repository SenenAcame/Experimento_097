#pragma once
#include <cstddef>
#include "../util/gamecontext.hpp"
#include "componentstorage.hpp"
#include "../eng/engine.hpp"
#include "../util/keyboard.hpp"
#include <iostream>
#include <vector>
static int i=0;
template<typename Type>
struct EntityManager : public GameContext {
    using TypeProcessFunc = void (*)(Type&);
    static constexpr std::size_t kNUMINIT {1000};
    

    explicit EntityManager(std::size_t kNUMENT = kNUMINIT){
        entities_.reserve(kNUMENT);
    }

    Entity& createEntity(){ 
        Entity& e = entities_.emplace_back();

        auto& ph = storage.createPhysicsComponent(e.getEntityID());
        auto& re  = storage.createRenderComponent(e.getEntityID());
        auto& in   = storage.createInputComponent(e.getEntityID());

        e.physics = &ph;
        e.render = &re;
        e.input = &in;

        return e; 
    }

    Entity& createBullet(Entity& weapon){
        Entity& bullet = createEntity();
        bullet.tipo = 'b';
        bullet.physics->x = weapon.physics->x+5;
        bullet.physics->z = weapon.physics->z;
        bullet.physics->vx = 0.2;
        return bullet;
    }

    int findEntity(Entity& e){
        int cont = 0;
        for(auto& ent : entities_){
            if(e.getEntityID()==ent.getEntityID()){
                break;
            }
            ++cont;
        }
        std::cout<<"Posicion de ents: "<<cont<<"\n";
        return cont;
    }

    int findPhysics(Entity& e){
        int cont = 0;
        for(auto& phy : getPhysicsComponents()){
            if(e.physics->componentID==phy.componentID){
                break;
            }
            cont++;
        }
        std::cout<<"Posicion de phy: "<<cont<<"\n";
        return cont;
        
    }

    int findRender(Entity& e){
        int cont = 0;
        for(auto& ren : getRenderComponents()){
            if(e.render->componentID==ren.componentID){
                break;
            }
            cont++;
        }
        std::cout<<"Posicion de rend: "<<cont<<"\n";
        return cont;
        
    }

    int findInput(Entity& e){
        int cont = 0;
        for(auto& inp : getInputComponents()){
            if(e.input->componentID==inp.componentID){
                break;
            }
            cont++;
        }
        std::cout<<"Posicion de inp: "<<cont<<"\n";
        return cont;
        
    }

    void destroyEntity(Entity& e){
        i++;

        //std::cout<<"Voy a destruir la ID: "<<e.render->componentID<<"\n";
        //
        //std::vector<PhysicsComponent>& phycomp  = getPhysicsComponents();
        std::vector<RenderComponent>& rendcomp = getRenderComponents();
        //auto& inpcomp  = getInputComponents();

        e.render->node->remove();
        //e.render->node = nullptr;

        //phycomp.erase(phycomp.begin()+findPhysics(e));
        //rendcomp.erase(rendcomp.begin()+findRender(e));
        //inpcomp.erase(inpcomp.begin()+findInput(e));
        //
        entities_.erase(entities_.begin()+findEntity(e));

        std::cout<<i<<" "<<rendcomp.size()<<" "<<rendcomp.capacity()<<"\n";
    }

    void forall(TypeProcessFunc process){
        for(auto& e : entities_){
            process(e);
        }
    }

    void forall(std::vector<PhysicsComponent>& phyCMP){
        for(auto& e : entities_){
            //if(e.physics != nullptr && e.render != nullptr && e.input != nullptr){
                auto& phy = e.physics;
                for(auto& e2 : entities_){
                    //if(e2.physics != nullptr && e2.render != nullptr && e2.input != nullptr){
                        if(e.getEntityID()!=e2.getEntityID()){
                            auto& phy2 = e2.physics;
                            float dx = phy->x - phy2->x;
                            float dy = phy->y - phy2->y;
                            float dz = phy->z - phy2->z;
                            float distance = std::sqrt(dx*dx+dy*dy+dz*dz);
                            if(distance <= 1.0){
                                if(e.tipo=='b'){
                                    //for(auto& e : getRenderComponents()){
                                    //    std::cout<<e.componentID<<" ";
                                    //}
                                    //std::cout<<"Antes de destroy";
                                    //std::cout<<"\n";
                                    //std::cout<<"Voy a destruir la ID: "<<e.componentID<<"\n";
                                    destroyEntity(e);
                                    //for(auto& e : getRenderComponents()){
                                    //    std::cout<<e.componentID<<" ";
                                    //}
                                    //std::cout<<"Despues de destroy";
                                    //std::cout<<"\n";
                                    //std::cout<<"\n";
                                }
                                else{
                                    phy->x -= phy->vx;
                                    phy->vx = -phy->vx;
                                    phy->y -= phy->vy;
                                    phy->vy = -phy->vy;
                                    phy->z -= phy->vz;
                                    phy->vz = -phy->vz;
                                }
                            }
                        }
                    //}
                }
            //}
        }
    }

    void forall(TheEngine& eng, Keyboard& keyb){
        for(Entity& e: entities_){
            if(e.tipo == 'p'){
                auto& phy = *(e.physics);
                auto& inp = *(e.input);
                phy.vx = 0;
                phy.vz = 0;
                if(keyb.isKeyPressed(inp.key_left)){
                    phy.vx = -0.1;
                }
                if(keyb.isKeyPressed(inp.key_right)){
                    phy.vx = 0.1;
                }
                if(keyb.isKeyPressed(inp.key_up)){
                    phy.vz = 0.1;
                }
                if(keyb.isKeyPressed(inp.key_down)){
                    phy.vz = -0.1;
                }
                if(keyb.isKeyPressed(inp.key_shot)){
                    auto& bullet = createBullet(e);
                    bullet.render->node = eng.createSphere();
                    keyb.keyReleased(inp.key_shot);
                }
            }
        }
    }
    
    const std::vector<Type>& getEntities() const override {return entities_;};
          std::vector<Type>& getEntities()       override {return entities_;};

    const std::vector<PhysicsComponent>&   getPhysicsComponents()   const {return storage.getPhysicsComponents();};
          std::vector<PhysicsComponent>&   getPhysicsComponents()         {return storage.getPhysicsComponents();};

    const std::vector<RenderComponent>&    getRenderComponents()    const {return storage.getRenderComponents();};
          std::vector<RenderComponent>&    getRenderComponents()          {return storage.getRenderComponents();};

    const std::vector<InputComponent>&     getInputComponents()     const {return storage.getInputComponents();};
          std::vector<InputComponent>&     getInputComponents()           {return storage.getInputComponents();};

    private:
    std::vector<Type> entities_{};
    ComponentStorage storage {kNUMINIT};
};