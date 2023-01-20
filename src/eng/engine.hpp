#pragma once
#include <irrlicht/EDriverTypes.h>
#include <irrlicht/irrlicht.h>
#include <stdexcept>
#include <memory>

struct TheEngine {
    explicit TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r);
    bool run() const;
    void addStaticText();
    void beginScene();
    void drawAll();
    void endScene();
    auto* createCube(float x, float y, float z, float tamx, float tamy, float tamz){
        auto* node = smgr_->addCubeSceneNode();
        if (!node) throw std::runtime_error("Couldn't create cube");
        node->setPosition(irr::core::vector3df(x,y,z));
        node->setScale(irr::core::vector3df(tamx/10,tamy/10,tamz/10));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        //node->setVisible(false);

        return node;
    }
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
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setRotation({45,-90,0});
        return node;
    };

    irr::scene::IAnimatedMeshSceneNode* createMap(){
        irr::scene::IAnimatedMesh* mesh = smgr_->getMesh("assets/salas_visibles.obj");
        if (!mesh){
            device_->drop();
            return nullptr;
        }
        irr::scene::IAnimatedMeshSceneNode* node = smgr_->addAnimatedMeshSceneNode( mesh );

        auto* texture = driver_->getTexture("assets/wall.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");
        node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        return node;
    };

    irr::scene::IAnimatedMeshSceneNode* createEnemy(const irr::io::path asset){
        irr::scene::IAnimatedMesh* mesh = smgr_->getMesh("assets/enemy.obj");
        if (!mesh){
            device_->drop();
            return nullptr;
        }
        irr::scene::IAnimatedMeshSceneNode* node = smgr_->addAnimatedMeshSceneNode( mesh );
        auto* texture = driver_->getTexture(asset);
        if (!texture) throw std::runtime_error("Couldn't create texture");
        node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        return node;
    };

    irr::scene::IAnimatedMeshSceneNode* createWeapon1(){
        irr::scene::IAnimatedMesh* mesh = smgr_->getMesh("assets/pistola.obj");
        if (!mesh){
            device_->drop();
            return nullptr;
        }
        irr::scene::IAnimatedMeshSceneNode* node = smgr_->addAnimatedMeshSceneNode( mesh );
        auto* texture = driver_->getTexture("assets/portal7.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");
        node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        return node;
    };

    auto& getDevice(){return device_;}
    auto getSceneManager(){return device_->getSceneManager();}
    auto getCamera(){return device_->getSceneManager()->getActiveCamera();}
    auto getCameraTarget(){return device_->getSceneManager()->getActiveCamera()->getTarget();}

    private:
    using DestructorFunc = void (*)(irr::IrrlichtDevice*);
    using irrDeviceManaged = std::unique_ptr<irr::IrrlichtDevice, DestructorFunc>;

    static void destroy(irr::IrrlichtDevice* p){ p->drop(); };

    irr::u32 const width_{}, height_{};
    irr::IEventReceiver* receive {};

    irrDeviceManaged device_ {
        irr::createDevice(irr::video::EDT_BURNINGSVIDEO, 
                            irr::core::dimension2d<irr::u32>(width_, height_), 
                            16,false,false,false,receive), 
        destroy
    };
    irr::video::IVideoDriver  * const driver_ {device_ ? device_->getVideoDriver()    : nullptr};
    irr::scene::ISceneManager * const smgr_   {device_ ? device_->getSceneManager()   : nullptr};
    irr::gui::IGUIEnvironment * const guienv_ {device_ ? device_->getGUIEnvironment() : nullptr};
};