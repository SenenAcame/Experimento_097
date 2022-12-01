//#include <irrlicht/EDebugSceneTypes.h>
//#include <irrlicht/EDriverTypes.h>
//#include <irrlicht/IrrlichtDevice.h>
//#include <irrlicht/dimension2d.h>
//#include <irrlicht/irrTypes.h>
//#include <irrlicht/irrTypes.h>
//#include <irrlicht/SColor.h>
//#include <cstddef>
//#include <irrlicht/ISceneNode.h>
//#include <irrlicht/vector3d.h>
#include <irrlicht/irrlicht.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <cstdint>
#include <vector>


struct TheEngine {
    TheEngine(uint32_t const w, uint32_t const h) :width_{w}, height_{h}{
        if(!device_) throw std::runtime_error("Couldn't initialize device!!");
        smgr_->addCameraSceneNodeFPS();
    }
    bool run() const {return device_->run();}
    void addStaticText(){
        guienv_->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                            irr::core::rect<irr::s32>(10,10,260,22), true);
    }
    void beginScene(){
        driver_->beginScene(true, true, irr::video::SColor(255, 200, 100, 140));
    }
    void drawAll(){
        smgr_->drawAll();
        guienv_->drawAll();
    }
    void endScene(){
        driver_->endScene();
    }
    auto* createSphere(){
        auto* node = smgr_->addSphereSceneNode();
        if (!node) throw std::runtime_error("Couldn't create sphere");

        //auto* texture = driver_->getTexture("/usr/share/irrlicht/media/wall.bmp");
        //if (!texture) throw std::runtime_error("Couldn't create texture");

        node->setPosition(irr::core::vector3df(0,0,30));
        //node->setMaterialTexture(0, texture);
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        return node;
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

struct PhysicsComponent {
    float  x{},  y{},  z{};
    float vx{}, vy{}, vz{};
};

struct RenderComponent {
    irr::scene::ISceneNode* node{};
};

struct Entity {
    PhysicsComponent physics;
    RenderComponent render;
};

template<typename Type>
struct EntityManager {
    using TypeProcessFunc = void (*)(Type&);

    EntityManager(std::size_t defaultsize = 100){
        entities_.reserve(defaultsize);
    }
    auto& createEntity(){ return entities_.emplace_back(); }

    void forall(TypeProcessFunc process){
        for(auto& e : entities_){
            process(e);
        }
    }
    private:
    std::vector<Entity> entities_{};
};

struct PhysicsSystem {
    void update(EntityManager<Entity>& EM){
        EM.forall([](Entity& e) {
            e.physics.x += e.physics.vx;
            e.physics.y += e.physics.vy;
            e.physics.z += e.physics.vz;
        });
    }
};

struct RenderSystem {
    void update(EntityManager<Entity>& EM, TheEngine& GFX){
        EM.forall([](Entity& e) {
            auto& phy {e.physics};
            e.render.node->setPosition({phy.x, phy.y, phy.z});
        });
        GFX.beginScene();
        GFX.drawAll();
        GFX.endScene();
    }
};

void game(){
    TheEngine dev {640, 480};
    EntityManager<Entity> EM;
    PhysicsSystem   PhySys;
    RenderSystem    RenSys;

    auto& e = EM.createEntity();
    e.render.node = dev.createSphere();
    e.physics.z = 10.0f;
    e.physics.vz = 0.2f;

    while(dev.run()){
        PhySys.update(EM);
        RenSys.update(EM, dev);
    }
}

int main(){
    game();
}