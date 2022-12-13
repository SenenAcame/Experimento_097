#pragma once
#include <cstddef>
//#include <vector>
//#include "../cmp/entity.hpp"
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
    //    auto& co   = storage.createCollisionComponent(e.entityID);

        e.physics = &ph;
        e.render = &re;
        e.input = &in;
    //    e.collision = &co;

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
                    if(/*phy.x < -50.0 ||*/ abs(phy.x - phy2.x) <= 8 /*|| phy.x > 50.0*/){

                        if((phy.vx>0 && phy2.vx>0) || (phy.vx<0 && phy2.vx<0)){
                            if(abs(phy.vx)>abs(phy2.vx)){
                                phy.x -= phy.vx;
                                phy.vx = -phy.vx;
                                phy.y -= phy.vy;
                                phy.vy = -phy.vy;
                            }
                        }
                        else{
                            phy.x -= phy.vx;
                            phy.vx = -phy.vx;
                            phy.y -= phy.vy;
                            phy.vy = -phy.vy;
                        }

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
          
    //const std::vector<CollisionComponent>& getCollisionComponents() const {return storage.getCollisionComponents();};
    //      std::vector<CollisionComponent>& getCollisionComponents()       {return storage.getCollisionComponents();};

    private:
    std::vector<Type> entities_{};
    ComponentStorage storage {kNUMINIT};
};