#include "engine.hpp"
#include <stdexcept>

TheEngine::TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r) :width_{w}, height_{h}, receive{r}{
    if(!device_) throw std::runtime_error("Couldn't initialize device!!");
    irr::SKeyMap keyMap[8];
		 keyMap[0].Action  = irr::EKA_MOVE_FORWARD;
		 keyMap[0].KeyCode = irr::KEY_UP;
		 keyMap[1].Action  = irr::EKA_MOVE_FORWARD;
		 keyMap[1].KeyCode = irr::KEY_KEY_W;

		 keyMap[2].Action  = irr::EKA_MOVE_BACKWARD;
		 keyMap[2].KeyCode = irr::KEY_DOWN;
		 keyMap[3].Action  = irr::EKA_MOVE_BACKWARD;
		 keyMap[3].KeyCode = irr::KEY_KEY_S;

		 keyMap[4].Action  = irr::EKA_STRAFE_LEFT;
		 keyMap[4].KeyCode = irr::KEY_LEFT;
		 keyMap[5].Action  = irr::EKA_STRAFE_LEFT;
		 keyMap[5].KeyCode = irr::KEY_KEY_A;

		 keyMap[6].Action  = irr::EKA_STRAFE_RIGHT;
		 keyMap[6].KeyCode = irr::KEY_RIGHT;
		 keyMap[7].Action  = irr::EKA_STRAFE_RIGHT;
		 keyMap[7].KeyCode = irr::KEY_KEY_D;

    smgr_->addCameraSceneNodeFPS(
        /*irr::scene::ISceneNode *parent = */0,
        /*irr::f32 rotateSpeed = */30.f, 
        /*irr::f32 moveSpeed = */0.01f,
        /*irr::s32 id = */-1, 
        /*irr::SKeyMap *keyMapArray = */keyMap,
        /*irr::s32 keyMapSize = */8, 
        /*bool noVerticalMovement = */true,
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