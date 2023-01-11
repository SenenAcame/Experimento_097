#pragma once
#include <cstddef>
#include "../util/gamecontext.hpp"
#include "componentstorage.hpp"
#include "../eng/engine.hpp"
#include "../eng/matrix3.hpp"
#include "../util/keyboard.hpp"

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
        irr::core::vector3df vector(0,0,0);
        e.setLookAtVector(vector);

        return e; 
    }

    Entity& createBullet(Entity& weapon){
        Entity& bullet = createEntity();
        bullet.tipo = 'b';
        bullet.physics->x = weapon.physics->x+1.1;
        bullet.physics->y = weapon.physics->y;
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
        return cont;
        
    }

    void destroyEntity(Entity& e){
        //std::vector<PhysicsComponent>& phycomp  = getPhysicsComponents();
        //std::vector<RenderComponent>& rendcomp = getRenderComponents();
        //auto& inpcomp  = getInputComponents();

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
                    if(distance <= 1.0){
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
                phy.vy = 0;
                irr::core::vector3df PlayerPos = e.render->node->getAbsolutePosition();
                e.setLookAtVector(TheEngine::normalizeVector3(e.getLookAtVector()));
                irr::core::vector3df aux(0.0,1.0,0.0);
                if(keyb.isKeyPressed(inp.key_left)){
                    phy.vx = -0.1; 
                    irr::core::vector3df PosP(phy.x,phy.y,phy.z);
                    PosP = TheEngine::SubVector3(
                        PosP,
                        TheEngine::MultyVector3(
                           TheEngine:: ProductCross(e.getLookAtVector(),
                            aux)
                            ,0.07
                        )
                    );
                    e.render->node->setPosition(PosP);
                }
                if(keyb.isKeyPressed(inp.key_right)){
                    phy.vx = 0.1;
                    irr::core::vector3df PosP(phy.x,phy.y,phy.z);
                    PosP = TheEngine::SubVector3(
                        PosP,
                        TheEngine::MultyVector3(
                           TheEngine:: ProductCross(e.getLookAtVector(),
                            aux)
                            ,0.07
                        )
                    );
                    e.render->node->setPosition(PosP);

                }
                if(keyb.isKeyPressed(inp.key_up)){
                    //phy.vy = 0.1;
                    e.render->node->setPosition(TheEngine::addVector3(
                            PlayerPos,
                            TheEngine::MultyVector3(e.getLookAtVector(),0.07)
                    ));
                //std::cout<<"Este es el vector de lookAt: " << e.getLookAtVector().X<< ", "
                //<< e.getLookAtVector().Y<< ", " << e.getLookAtVector().Z<< ", ";
                //std::cout<<"Esta es la posicion de e: " << e.render->node->getAbsolutePosition().X<< ", "
                //<< e.render->node->getAbsolutePosition().Y<< ", " << e.render->node->getAbsolutePosition().Z<< ", ";

                }
                if(keyb.isKeyPressed(inp.key_down)){
                    phy.vy = -0.1;
                    e.render->node->setPosition(TheEngine::SubVector3(PlayerPos,
                    TheEngine::MultyVector3(e.getLookAtVector(),0.07)
                    ));
                }
                if(keyb.isKeyPressed(inp.key_shot)){
                    auto& bullet = createBullet(e);
                    bullet.render->node = eng.addBullet();
                    keyb.keyReleased(inp.key_shot);
                }

                //e.setLookAtVector(TheEngine::tranformVector3(
                //    e.getLookAtVector(), rotationMatrix3(
                //        (3.14/4.0(4.0*75.0))*-(getMouseState().Position.X - getMouseState().LastPosition.X ),
                //        0.0, 1.0, 0.0               
                //    ))
                //);
//
                //MouseState.LastPosition.X = MouseState.Position.X;
                //MouseState.LastPosition.Y = MouseState.Position.Y;

                e.setLookAtVector(TheEngine::addVector3(PlayerPos,e.getLookAtVector()));
                
                
                //PlayerPos.X =e.physics->x;
                //PlayerPos.Y =e.physics->y;
                //PlayerPos.Z =e.physics->z;
                //e.render->node->setPosition(PlayerPos);
                
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