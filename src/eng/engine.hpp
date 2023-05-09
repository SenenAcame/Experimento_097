//#pragma once
//#include <irrlicht/irrlicht.h>
//#include <memory>
//
//struct TheEngine {
//    using IMeshSceneNode   = irr::scene::IMeshSceneNode;
//    using AnimatedMeshNode = irr::scene::IAnimatedMeshSceneNode;
//    using AnimatedMesh     = irr::scene::IAnimatedMesh;
//    using Path             = const irr::io::path;
//    using IGUIImage        = irr::gui::IGUIImage;
//    using IGUIText         = irr::gui::IGUIStaticText;
//    using IGUIFont         = irr::gui::IGUIFont;
//
//    explicit TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r);
//    bool run() const { return device_->run(); }
//    void addStaticText();
//    void beginScene();
//    void drawAll();
//    void endScene() { driver_->endScene(); }
//
//    IGUIImage* addImageToPositionInScreen(Path image, int x, int y);
//    void       changeImageFromPointer    (IGUIImage* pointer, Path image);
//    void       setInvisibleImage         (IGUIImage* pointer) { pointer->setVisible(false); }
//    void       setVisibleImage           (IGUIImage* pointer) { pointer->setVisible(true); }
//    auto       addFont                   (Path p);
//    void       SetFont                   (Path p);
//    IGUIText*  addTextToPositionInScreen (const wchar_t * text, int x, int y, int x2, int y2);
//    void       changeTextFromPointer     (IGUIText* pointer,const wchar_t * text) { pointer->setText(text); }
//
//    AnimatedMeshNode* loadNode(AnimatedMesh* model, Path text);
//    AnimatedMeshNode* createModel (Path obj, Path asset);
//    AnimatedMeshNode* createPlayer(Path obj, Path asset);
//    IMeshSceneNode*   createSphere(float r = 5.0f);
//
//    auto& getDevice()           { return device_; }
//    auto  getSceneManager() { return device_->getSceneManager(); }
//    auto  getCamera()           { return getSceneManager()->getActiveCamera(); }
//    auto& getCameraTarget(){ return getCamera()->getTarget(); }
//    unsigned int getWidth()  { return driver_->getScreenSize().Width;  }
//    unsigned int getHeight() { return driver_->getScreenSize().Height; }
//    
//private:
//    using DestructorFunc   = void (*)(irr::IrrlichtDevice*);
//    using irrDeviceManaged = std::unique_ptr<irr::IrrlichtDevice, DestructorFunc>;
//
//    static void destroy(irr::IrrlichtDevice* p) { p->drop(); };
//
//    irr::u32 const width_ {}, height_ {};
//    irr::IEventReceiver* receive {};
//
//    irrDeviceManaged device_ {
//        irr::createDevice(
//            irr::video::EDT_BURNINGSVIDEO,
//            irr::core::dimension2d<irr::u32>(width_, height_),
//            16,
//            false,
//            false,
//            false,
//            receive
//        ), 
//        destroy
//    };
//
//    irr::video::IVideoDriver * const driver_ { device_ ? device_->getVideoDriver()    : nullptr };
//    irr::scene::ISceneManager* const smgr_   { device_ ? device_->getSceneManager()   : nullptr };
//    irr::gui::IGUIEnvironment* const guienv_ { device_ ? device_->getGUIEnvironment() : nullptr };
//};