#pragma once
#include <irrlicht/irrlicht.h>
#include <stdexcept>
#include <memory>

struct TheEngine {
    explicit TheEngine(uint32_t const w, uint32_t const h);
    bool run() const;
    void addStaticText();
    void beginScene();
    void drawAll();
    void endScene();
    auto* createSphere(){
        auto* node = smgr_->addSphereSceneNode();
        if (!node) throw std::runtime_error("Couldn't create sphere");

        //auto* texture = driver_->getTexture("/usr/share/irrlicht/media/wall.bmp");
        //if (!texture) throw std::runtime_error("Couldn't create texture");

        node->setPosition(irr::core::vector3df(0,0,30));
        //node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        return node;
    };
    
    private:
    using DestructorFunc = void (*)(irr::IrrlichtDevice*);
    using irrDeviceManaged = std::unique_ptr<irr::IrrlichtDevice, DestructorFunc>;

    static void destroy(irr::IrrlichtDevice* p){ p->drop(); };
    irr::u32 const width_{}, height_{};
    irrDeviceManaged device_ {
        irr::createDevice(irr::video::EDT_SOFTWARE, 
                            irr::core::dimension2d<irr::u32>(width_, height_), 
                            16,false,false,false,0), 
        destroy
    };
    irr::video::IVideoDriver  * const driver_ {device_ ? device_->getVideoDriver()    : nullptr};
    irr::scene::ISceneManager * const smgr_   {device_ ? device_->getSceneManager()   : nullptr};
    irr::gui::IGUIEnvironment * const guienv_ {device_ ? device_->getGUIEnvironment() : nullptr};
};