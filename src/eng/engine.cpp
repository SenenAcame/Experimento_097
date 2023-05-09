//#include "engine.hpp"
//#include <stdexcept>
//
//TheEngine::TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r) 
//: width_ { w }, height_ { h }, receive { r } {
//    if(!device_) throw std::runtime_error("Couldn't initialize device!!");
//
//    auto* cam = smgr_->addCameraSceneNode();
//    cam->bindTargetAndRotation(true);
//}
//
//void TheEngine::addStaticText() {
//    guienv_->addStaticText(
//        L"Hello World! This is the Irrlicht Software renderer!",
//        irr::core::rect<irr::s32>(10,10,260,22), 
//        true
//    );
//}
//
//void TheEngine::beginScene() {
//    driver_->beginScene(
//        true, 
//        true, 
//        irr::video::SColor(255, 200, 100, 140)
//    );
//}
//
//void TheEngine::drawAll() {
//    smgr_->drawAll();
//    guienv_->drawAll();
//}
//
//TheEngine::IGUIImage* TheEngine::addImageToPositionInScreen(Path image, int x, int y) {
//    irr::video::ITexture* images = driver_->getTexture(image);
//    auto height = images->getSize().Height;
//    auto width  = images->getSize().Width;
//    return guienv_->addImage(images, irr::core::position2d<int>(x-width/2,y-height/2));
//
//}
//
//void TheEngine::changeImageFromPointer(IGUIImage* pointer, Path image) {
//    irr::video::ITexture* images = driver_->getTexture(image);
//    pointer->setImage(images);
//}
//
//auto TheEngine::addFont(Path p) {
//    IGUIFont *font = guienv_->getFont(p);
//    return guienv_->addFont(p, font);
//}
//
//void TheEngine::SetFont(Path p) {
//    irr::gui::IGUISkin* skin = guienv_->getSkin();
//    IGUIFont* font = guienv_->getFont(p);
//    
//    if (font) skin->setFont(font);
//
//    skin->setFont(guienv_->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
//}
//
//TheEngine::IGUIText* TheEngine::addTextToPositionInScreen (const wchar_t * text, int x, int y, int x2, int y2) {
//    return guienv_->addStaticText(
//        text, 
//        irr::core::rect<irr::s32>(x, y, x2, y2), 
//        false
//    );
//}
//
//TheEngine::AnimatedMeshNode* TheEngine::loadNode(AnimatedMesh* model, Path text) {
//    AnimatedMeshNode* node = smgr_->addAnimatedMeshSceneNode(model);
//    auto* texture = driver_->getTexture(text);
//
//    if (!texture) throw std::runtime_error("Couldn't create texture");
//
//    node->setMaterialTexture(0, texture);
//    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//    return node;
//}
//
//TheEngine::AnimatedMeshNode* TheEngine::createModel(Path obj, Path asset) {
//    AnimatedMesh* mesh = smgr_->getMesh(obj);
//    if (!mesh) {
//        device_->drop();
//        return nullptr;
//    }
//    
//    return loadNode(mesh, asset);
//}
//
//TheEngine::AnimatedMeshNode* TheEngine::createPlayer(Path obj, Path asset) {
//    auto node = createModel(obj, asset);
//    auto* cam = getCamera();
//
//    cam->setParent(node);
//    cam->setPosition({ 0, 2, -3 });
//
//    return node;
//}
//
//TheEngine::IMeshSceneNode* TheEngine::createSphere(float r) {
//    auto* node = smgr_->addSphereSceneNode(
//        r,
//        16,
//        0,
//        -1,
//        irr::core::vector3df(0, 0, 0),
//        irr::core::vector3df(0, 0, 0),
//        irr::core::vector3df(1.f, 1.f, 1.f)
//    );
//
//    if (!node) throw std::runtime_error("Couldn't create sphere");
//
//    auto* texture = driver_->getTexture("assets/textures/wall.bmp");
//    if (!texture) throw std::runtime_error("Couldn't create texture");
//
//    node->setPosition(irr::core::vector3df(0,0,0));
//    node->setRotation(irr::core::vector3df(0,-180,0));
//    node->setMaterialTexture(0, texture);
//    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//    return node;
//}