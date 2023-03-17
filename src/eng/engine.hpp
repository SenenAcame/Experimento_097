#pragma once
#include <irrlicht/irrlicht.h>
#include <stdexcept>
#include <memory>
#include <iostream>
//IMGUI
#include <imgui/src/imgui.h>
#include <imgui/src/imgui_impl_glfw.h>
#include <imgui/src/imgui_impl_opengl3.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


struct TheEngine {
    using AnimatedMeshNode = irr::scene::IAnimatedMeshSceneNode;
    using AnimatedMesh     = irr::scene::IAnimatedMesh;
    using Path             = const irr::io::path;

    explicit TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r);
    bool run() const;
    void addStaticText();
    void beginScene();
    void drawAll();
    void endScene();
    void initIMGUI();


    auto loadNode(AnimatedMesh* model, Path text);
    AnimatedMeshNode* createModel(Path obj, Path asset);
    AnimatedMeshNode* createPlayer(Path obj, Path asset);

    auto* createSphere(float r = 5.0f){
        auto* node = smgr_->addSphereSceneNode(
            /*irr::f32 radius = */r,
            /*irr::s32 polyCount =*/ 16,
            /*irr::scene::ISceneNode * parent =*/ 0,
            /*irr::s32 id =*/ -1,
            /*const core::vector3df & position =*/ irr::core::vector3df(0, 0, 0),
            /*const core::vector3df & rotation =*/ irr::core::vector3df(0, 0, 0),
            /*const core::vector3df & scale =*/ irr::core::vector3df(1.F, 1.F, 1.F));
        if (!node) throw std::runtime_error("Couldn't create sphere");

        auto* texture = driver_->getTexture("assets/textures/wall.bmp");
        if (!texture) throw std::runtime_error("Couldn't create texture");

        node->setPosition(irr::core::vector3df(0,0,0));
        node->setRotation(irr::core::vector3df(0,-180,0));
        node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        return node;
    };

    auto& getDevice()           {return device_;}
    auto  getSceneManager() {return device_->getSceneManager();}
    auto  getCamera()           {return device_->getSceneManager()->getActiveCamera();}
    auto& getCameraTarget(){return device_->getSceneManager()->getActiveCamera()->getTarget();}
    auto  getWidth() { return driver_->getScreenSize().Width;  }
    auto  getHeight(){ return driver_->getScreenSize().Height; }
    
private:
    using DestructorFunc = void (*)(irr::IrrlichtDevice*);
    using irrDeviceManaged = std::unique_ptr<irr::IrrlichtDevice, DestructorFunc>;

    static void destroy(irr::IrrlichtDevice* p){ 
        

        p->drop(); 
    };

    GLFWwindow* m_window {nullptr};
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