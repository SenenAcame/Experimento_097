//#include <irrlicht/EDebugSceneTypes.h>
//#include <irrlicht/EDriverTypes.h>
//#include <irrlicht/IrrlichtDevice.h>
//#include <irrlicht/dimension2d.h>
//#include <irrlicht/irrTypes.h>
//#include <irrlicht/irrTypes.h>
#include <irrlicht/SColor.h>
#include <irrlicht/irrlicht.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <cstdint>


struct TheEngine {
    TheEngine(uint32_t const w, uint32_t const h) :width_{w}, height_{h}{
        if(!device_) throw std::runtime_error("Couldn't initialize device!!");
    }
    bool run() const {return device_->run();}
    void addStaticText(){
        guienv_->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                            irr::core::rect<irr::s32>(10,10,260,22), true);
    }
    void beginScene(){
        driver_->beginScene(true, true, irr::video::SColor(255, 200, 101, 140));
    }
    void drawAll(){
        smgr_->drawAll();
        guienv_->drawAll();
    }
    void endScene(){
        driver_->endScene();
    }
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

void game(){
    TheEngine dev {640, 480};
    dev.addStaticText();
    while(dev.run()){
        dev.beginScene();
        dev.drawAll();
        dev.endScene();
    }
}


int main(){
    game();
    return 0;    
}