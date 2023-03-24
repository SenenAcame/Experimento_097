#include "engine.hpp"
#include <cstddef>
#include <irrlicht/IEventReceiver.h>
#include <irrlicht/SMaterialLayer.h>
#include <irrlicht/position2d.h>




TheEngine::TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r) :width_{w}, height_{h}, receive{r}{
    if(!device_) throw std::runtime_error("Couldn't initialize device!!");
    auto* cam = smgr_->addCameraSceneNode();
    cam->bindTargetAndRotation(true);
}

auto TheEngine::loadNode(AnimatedMesh* model, Path text){
    AnimatedMeshNode* node = smgr_->addAnimatedMeshSceneNode(model);
    auto* texture = driver_->getTexture(text);
    if (!texture) throw std::runtime_error("Couldn't create texture");
    node->setMaterialTexture(0, texture);
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    return node;
}

TheEngine::AnimatedMeshNode* TheEngine::createModel(Path obj, Path asset) {
    AnimatedMesh* mesh = smgr_->getMesh(obj);
    if (!mesh){
        device_->drop();
        return nullptr;
    }
    auto node = loadNode(mesh, asset);
    return node;
}

TheEngine::AnimatedMeshNode* TheEngine::createPlayer(Path obj, Path asset) {
    auto node = createModel(obj, asset);
    auto* cam = getCamera();

    cam->setParent(node);
    cam->setPosition({ 0, 2, -3 });

    return node;
}

bool TheEngine::run() const { return device_->run(); }

void TheEngine::addStaticText(){
    guienv_->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                        irr::core::rect<irr::s32>(10,10,260,22), true);
}

TheEngine::IGUIImage* TheEngine::addImageToPositionInScreen(Path image, int x, int y){
    
    irr::video::ITexture* images = driver_->getTexture(image);
    return guienv_->addImage(images, irr::core::position2d<int>(x,y));
   
}

void TheEngine::changeImageFromPointer(IGUIImage* pointer, Path image){

    irr::video::ITexture* images = driver_->getTexture(image);
    pointer->setImage(images);

}

void TheEngine::beginScene(){
    
    driver_->beginScene(true, true, irr::video::SColor(255, 200, 100, 140));
    
}

void TheEngine::drawAll(){
    smgr_->drawAll();
    guienv_->drawAll();
}

void TheEngine::endScene(){ driver_->endScene(); }