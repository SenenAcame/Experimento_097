#pragma once
#include <cstddef>
#include <irrlicht/vector3d.h>
#include "../util/gamecontext.hpp"
#include "componentstorage.hpp"
#include "../eng/engine.hpp"
#include "../util/keyboard.hpp"
#include "../sys/soundsystem.hpp"
#include <iostream>
#include "math.h"

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
        auto& so   = storage.createSoundComponent(e.getEntityID());

        e.physics = &ph;
        e.render = &re;
        e.input = &in;
        e.sound= &so;

        return e; 
    }

    Entity& createBullet(Entity& weapon){
        Entity& bullet = createEntity();
        bullet.tipo = 'b';
        //bullet.physics->x = weapon.render->node->getParent()->getPosition().X+7;
        //bullet.physics->y = weapon.render->node->getParent()->getPosition().Y-2;
        //bullet.physics->z = weapon.render->node->getParent()->getPosition().Z-1;
        
        //irr::core::vector3df cameraPos = targetCamera->getPosition();
        //irr::core::vector3df cameraRot = targetCamera->getRotation();
//
        //irr::core::vector3df PosBullet = cameraPos + cameraRot;
        //bullet.physics->x = weapon.render->node->getParent()->getPosition().X+7;
        //bullet.physics->y = weapon.render->node->getParent()->getPosition().Y-2;
        //bullet.physics->z = weapon.render->node->getParent()->getPosition().Z-1;
//
        //irr::core::vector3df DirBullet = cameraRot;
        //irr::core::vector3df VelBullet = DirBullet * 0.2; 
        //if(VelBullet.X !=0){
            bullet.physics->vx = 0.2;
        //}
        //if(VelBullet.Y !=0 ){
            bullet.physics->vy = 0.2;
        //}
        //if(VelBullet.Z !=0 ){
        //    bullet.physics->vz = 0.2;
        //}
        
        //std::cout << "VelBullet: " <<VelBullet.X <<" " << VelBullet.Y <<" "<< VelBullet.Z;
        //bullet.physics->vx = 0.2;
        //std::cout << "Target de camera: " <<targetCamera.X <<" " << targetCamera.Y <<" "<< targetCamera.Z;
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

    void forall(TheEngine& eng, Keyboard& keyb, SoundSystem_t& sounsys){
        for(Entity& e: entities_){
            if(e.tipo == 'p'){
                auto& phy = *(e.physics);
                auto& inp   = *(e.input);
                //auto cam = e.render->node->getParent()->getPosition();
                phy.vx = 0;
                phy.vz = 0;
               // if(keyb.isKeyPressed(inp.key_left)){
               //     phy.vz = 0.2;
               // }
               // if(keyb.isKeyPressed(inp.key_right)){
               //     phy.vz = -0.2;
               // }
               // if(keyb.isKeyPressed(inp.key_up)){
               //     phy.vx = 0.2;
               // }
               // if(keyb.isKeyPressed(inp.key_down)){
               //     phy.vx = -0.2;
               // }
                if(keyb.isKeyPressed(inp.key_shot)){
                    auto& bullet = createBullet(e);
                    bullet.render->node = eng.addBullet();
                    bullet.physics->x = eng.getCamera()->getPosition().X+7;
                    bullet.physics->y = eng.getCamera()->getPosition().Y-2;
                    bullet.physics->z = eng.getCamera()->getPosition().Z-1;

                    bullet.physics->vx = cos(
                        (eng.getCamera()->getRotation().X * M_PI/180) 
                        ) * 0.2;
                    bullet.physics->vy = sin(
                        ((eng.getCamera()->getRotation().Y-90) * M_PI/180)
                        ) * 0.2;
                    bullet.physics->vz = 0;
                    
                    //bullet.render->node->setPosition(e.render->node->getParent()->getPosition().X+7,
                    //e.render->node->getParent()->getPosition().Y-2,
                    //e.render->node->getParent()->getPosition().Z-1);
    
                    irr::core::vector3df targetCamera = eng.getCamera()->getTarget();
                    irr::core::vector3df cameraRot = eng.getCamera()->getRotation();
                   // bullet.physics->vx = cameraRot.X * 0.2; 
                   // bullet.physics->vy = cameraRot.Y * 0.2; 
                   // bullet.physics->vz = cameraRot.Z * 0.2; 
                   // 

                   std::cout << "Valores Operacion: " <<eng.getCamera()->getRotation().Y <<" " << M_PI <<" Y tiene da "
                   << eng.getCamera()->getRotation().Y * M_PI/180 << " con cos da  " << sin(
                        (eng.getCamera()->getRotation().Y * M_PI/180) 
                        ) << " y por 0.2 es "<< cos(
                        (eng.getCamera()->getRotation().Y * M_PI/180) 
                        ) * 0.2;
                    //std::cout << "Rot de camera: " <<cameraRot.X <<" " << cameraRot.Y <<" "<< cameraRot.Z;
                    //std::cout << "Rot weapon: " <<e.render->node->getRotation().X <<" " << e.render->node->getRotation().Y <<" "<< e.render->node->getRotation().Z;
                    //bullet.render->node->setPosition(eng.getCamera()->getPosition());
                    //bullet.render->node->setRotation(eng.getCamera()->getRotation());
                    //bullet.physics->x = bullet.render->node->getPosition().X+7;
                    //bullet.physics->y = bullet.render->node->getPosition().Y-2;
                    //bullet.physics->z = bullet.render->node->getPosition().Z-1;
                    keyb.keyReleased(inp.key_shot);
                }
                if(keyb.isKeyPressed(inp.key_sound1)){
                    sounsys.changesound(e,1);
                }
                if(keyb.isKeyPressed(inp.key_sound2)){
                    sounsys.startsound(e); 
                }
                //if(keyb.isKeyPressed(inp.key_sound3)){
//
                //}
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

    const std::vector<SoundComponent>&     getSoundComponents()     const {return storage.getSoundComponents();};
          std::vector<SoundComponent>&     getSoundComponents()           {return storage.getSoundComponents();};

    private:
    std::vector<Type> entities_{};
    ComponentStorage storage {kNUMINIT};
};