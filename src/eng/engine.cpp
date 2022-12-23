#include "engine.hpp"
#include <stdexcept>

TheEngine::TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r) :width_{w}, height_{h}, receive{r}{
    if(!device_) throw std::runtime_error("Couldn't initialize device!!");
    smgr_->addCameraSceneNodeFPS(
        /*irr::scene::ISceneNode *parent = */0,
        /*irr::f32 rotateSpeed = */2.0f, 
        /*irr::f32 moveSpeed = */0.1f,
        /*irr::s32 id = */-1, 
        /*irr::SKeyMap *keyMapArray = */0,
        /*irr::s32 keyMapSize = */4, 
        /*bool noVerticalMovement = */false,
        /*irr::f32 jumpSpeed = */0.f, 
        /*bool invertMouse = */false,
        /*bool makeActive = */true);
    //smgr_->addCameraSceneNode();
}

bool TheEngine::run() const {return device_->run();}

void TheEngine::addStaticText(){
    guienv_->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                        irr::core::rect<irr::s32>(10,10,260,22), true);
}

void TheEngine::beginScene(){
    driver_->beginScene(true, true, irr::video::SColor(255, 200, 100, 140));
}

void TheEngine::drawAll(){
    smgr_->drawAll();
    guienv_->drawAll();
}

void TheEngine::endScene(){
    driver_->endScene();
}