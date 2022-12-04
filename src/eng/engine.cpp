//#pragma once
#include "engine.hpp"
#include <stdexcept>

TheEngine::TheEngine(uint32_t const w, uint32_t const h) :width_{w}, height_{h}{
    if(!device_) throw std::runtime_error("Couldn't initialize device!!");
    smgr_->addCameraSceneNodeFPS();
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
//
//auto* TheEngine::createSphere(){
//    auto* node = smgr_->addSphereSceneNode();
//    if (!node) throw std::runtime_error("Couldn't create sphere");
//
//    //auto* texture = driver_->getTexture("/usr/share/irrlicht/media/wall.bmp");
//    //if (!texture) throw std::runtime_error("Couldn't create texture");
//
//    node->setPosition(irr::core::vector3df(0,0,30));
//    //node->setMaterialTexture(0, texture);
//    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//
//    return node;
//}