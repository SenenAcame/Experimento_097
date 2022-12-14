#pragma once
#include <cstddef>
#include "../util/gamecontext.hpp"
#include "componentstorage.hpp"

template<typename Type>
struct EntityManager : public GameContext {
    using TypeProcessFunc = void (*)(Type&);
    static constexpr std::size_t kNUMINIT {100};

    explicit EntityManager(std::size_t kNUMENT = kNUMINIT){
        entities_.reserve(kNUMENT);
    }

    auto& createEntity(){ 
        auto& e = entities_.emplace_back();

        auto& ph = storage.createPhysicsComponent(e.entityID);
        auto& re  = storage.createRenderComponent(e.entityID);
        auto& in   = storage.createInputComponent(e.entityID);

        e.physics = &ph;
        e.render = &re;
        e.input = &in;

        return e; 
    }

    void forall(TypeProcessFunc process){
        for(auto& e : entities_){
            process(e);
        }
    }

    void forall(std::vector<PhysicsComponent>& phyCMP){
        for(auto& phy : phyCMP){
            for(auto& phy2 : phyCMP){
                //Obtener id de entidad a partir del componente para que
                //dependiendo del tipo de entidad haga una cosa u otra
                //phy.entityID;
                //phy2.entityID;
                if(phy.componentID!=phy2.componentID){
                    float dx = phy.x - phy2.x;
                    float dy = phy.y - phy2.y;
                    float dz = phy.z - phy2.z;
                    float distance = std::sqrt(dx*dx+dy*dy+dz*dz);
                    if(distance <= 8.0){
                        phy.x -= phy.vx;
                        phy.vx = -phy.vx;
                        phy.y -= phy.vy;
                        phy.vy = -phy.vy;
                        phy.z -= phy.vz;
                        phy.vz = -phy.vz;
                    }
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