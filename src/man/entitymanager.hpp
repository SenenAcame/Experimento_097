#pragma once
#include <cstddef>
#include "../util/gamecontext.hpp"
#include "componentstorage.hpp"
#include "../eng/engine.hpp"
#include "../util/keyboard.hpp"

template<typename Type>
struct EntityManager : public GameContext {
    using TypeProcessFunc = void (*)(Type&);
    static constexpr std::size_t kNUMINIT {100};

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
        bullet.physics->vx = 1.0;
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
        return cont;
    }

    void destroyEntity(Entity& e){
        e.render->node->remove();
        entities_.erase(entities_.begin()+findEntity(e));
    }

    void forall(TypeProcessFunc process){
        for(auto& e : entities_){
            process(e);
        }
    }

    void forall(std::vector<PhysicsComponent>& phyCMP){
        for(auto& e : entities_){
            auto& phy = e.physics;
            for(auto& e2 : entities_){
                if(e.getEntityID()!=e2.getEntityID()){
                    auto& phy2 = e2.physics;
                    float dx = phy->x - phy2->x;
                    float dy = phy->y - phy2->y;
                    float dz = phy->z - phy2->z;
                    float distance = std::sqrt(dx*dx+dy*dy+dz*dz);
                    if(distance <= 2.0){
                        if(e.tipo=='b'){
                            destroyEntity(e);
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
            }
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