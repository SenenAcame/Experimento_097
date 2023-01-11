#pragma once
#include <irrlicht/irrlicht.h>
#include <stdexcept>
#include <memory>
#include <math.h>
#include "matrix3.hpp"

struct TheEngine {
    explicit TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r);
    bool run() const;
    void addStaticText();
    void beginScene();
    void drawAll();
    void endScene();
    auto* createSphere(){
        auto* node = smgr_->addSphereSceneNode();
        if (!node) throw std::runtime_error("Couldn't create sphere");

        auto* texture = driver_->getTexture("assets/wall.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");

        node->setPosition(irr::core::vector3df(0,0,0));
        node->setRotation(irr::core::vector3df(0,-180,0));
        node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        return node;
    };

    auto* addBullet(){
        auto* node = smgr_->addSphereSceneNode(
            /*irr::f32 radius = */0.5F,
            /*irr::s32 polyCount =*/ 16,
            /*irr::scene::ISceneNode * parent =*/ 0,
            /*irr::s32 id =*/ -1,
            /*const core::vector3df & position =*/ irr::core::vector3df(0, 0, 0),
            /*const core::vector3df & rotation =*/ irr::core::vector3df(0, 0, 0),
            /*const core::vector3df & scale =*/ irr::core::vector3df(1.F, 1.F, 1.F));
        if (!node) throw std::runtime_error("Couldn't create sphere");

        auto* texture = driver_->getTexture("assets/wall.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");

        node->setPosition(irr::core::vector3df(0,0,0));
        node->setRotation(irr::core::vector3df(0,-180,0));
        node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        return node;
    };
    
    irr::scene::IAnimatedMeshSceneNode* createPlayer(){
        irr::scene::IAnimatedMesh* mesh = smgr_->getMesh("assets/player_arm.obj");
        if (!mesh){
            device_->drop();
            return nullptr;
        }
        irr::scene::IAnimatedMeshSceneNode* node = smgr_->addAnimatedMeshSceneNode( mesh );
        auto* texture = driver_->getTexture("assets/fire.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");
        node->setMaterialTexture(0, texture);
        return node;
    };

    irr::scene::IAnimatedMeshSceneNode* createMap(){
        irr::scene::IAnimatedMesh* mesh = smgr_->getMesh("assets/laboratorio.obj");
        if (!mesh){
            device_->drop();
            return nullptr;
        }
        irr::scene::IAnimatedMeshSceneNode* node = smgr_->addAnimatedMeshSceneNode( mesh );

        auto* texture = driver_->getTexture("assets/wall.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");
        node->setMaterialTexture(0, texture);
        return node;
    };

    irr::scene::IAnimatedMeshSceneNode* createEnemy(){
        irr::scene::IAnimatedMesh* mesh = smgr_->getMesh("assets/enemy.obj");
        if (!mesh){
            device_->drop();
            return nullptr;
        }
        irr::scene::IAnimatedMeshSceneNode* node = smgr_->addAnimatedMeshSceneNode( mesh );
        auto* texture = driver_->getTexture("assets/fire.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");
        node->setMaterialTexture(0, texture);
        return node;
    };

    irr::scene::IAnimatedMeshSceneNode* createWeapon1(){
        irr::scene::IAnimatedMesh* mesh = smgr_->getMesh("assets/pistola.obj");
        if (!mesh){
            device_->drop();
            return nullptr;
        }
        irr::scene::IAnimatedMeshSceneNode* node = smgr_->addAnimatedMeshSceneNode( mesh );
        auto* texture = driver_->getTexture("assets/fire.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");
        node->setMaterialTexture(0, texture);
        return node;
    };

    static irr::core::vector3df normalizeVector3( irr::core::vector3df vector){

        double lenght = sqrt(vector.X * vector.X + vector.Y*vector.Y + + vector.Z*vector.Z);
        irr::core::vector3df unitVector(
            unitVector.X = vector.X/lenght ,
            unitVector.Y = vector.Y/lenght ,
            unitVector.Z = vector.Z/lenght 
        );

        return unitVector;
    };

    static irr::core::vector3df addVector3( irr::core::vector3df vector, irr::core::vector3df vector2 ){

        irr::core::vector3df result(0,0,0);
        result.X = vector.X + vector2.X;
        result.Y = vector.Y + vector2.Y;
        result.Z = vector.Z + vector2.Z;

        return result;
    };

    static irr::core::vector3df SubVector3( irr::core::vector3df vector, irr::core::vector3df vector2 ){

        irr::core::vector3df result(0,0,0);
        result.X = vector.X - vector2.X;
        result.Y = vector.Y - vector2.Y;
        result.Z = vector.Z - vector2.Z;

        return result;
    };

    static irr::core::vector3df MultyVector3( irr::core::vector3df vector, float a ){

        irr::core::vector3df result(0,0,0);
        result.X = vector.X * a;
        result.Y = vector.Y * a;
        result.Z = vector.Z * a;

        return result;
    };

    
    static irr::core::vector3df ProductCross(irr::core::vector3df vector, irr::core::vector3df vector2){

        irr::core::vector3df result(0,0,0);
        result.X = vector.Y * vector2.Z - vector.Z * vector2.Y;
        result.Y = vector.Z * vector2.X - vector.X * vector2.Z;
        result.Z = vector.X * vector2.Y - vector.Y * vector2.X;

        return result;

    }

    static float ProductVector3df (irr::core::vector3df vector, irr::core::vector3df vector2){

        return vector.X*vector2.X+ vector.Y*vector2.Y+ vector.Z*vector2.Z;
    }

    static irr::core::vector3df tranformVector3(irr::core::vector3df vector, matrix3 matrix){

        irr::core::vector3df result;
        irr::core::vector3df resultx;
        irr::core::vector3df resulty;
        irr::core::vector3df resultz;
        resultx.X = matrix.m00;
        resultx.Y = matrix.m10;
        resultx.Z = matrix.m20;

        resulty.X = matrix.m01;
        resulty.Y = matrix.m11;
        resulty.Z = matrix.m21;

        resultz.X = matrix.m02;
        resultz.Y = matrix.m12;
        resultz.Z = matrix.m22;


        result.X = ProductVector3df(vector,resultx);
        result.Y = ProductVector3df(vector,resulty);
        result.Z = ProductVector3df(vector,resultz);
        
        return result;
    }






    auto& getDevice(){return device_;}
    auto getSceneManager(){return device_->getSceneManager();}
    auto getCamera(){return device_->getSceneManager()->getActiveCamera();}

    private:
    using DestructorFunc = void (*)(irr::IrrlichtDevice*);
    using irrDeviceManaged = std::unique_ptr<irr::IrrlichtDevice, DestructorFunc>;

    static void destroy(irr::IrrlichtDevice* p){ p->drop(); };

    irr::u32 const width_{}, height_{};
    irr::IEventReceiver* receive {};

    irrDeviceManaged device_ {
        irr::createDevice(irr::video::EDT_SOFTWARE, 
                            irr::core::dimension2d<irr::u32>(width_, height_), 
                            16,false,false,false,receive), 
        destroy
    };
    irr::video::IVideoDriver  * const driver_ {device_ ? device_->getVideoDriver()    : nullptr};
    irr::scene::ISceneManager * const smgr_   {device_ ? device_->getSceneManager()   : nullptr};
    irr::gui::IGUIEnvironment * const guienv_ {device_ ? device_->getGUIEnvironment() : nullptr};
};