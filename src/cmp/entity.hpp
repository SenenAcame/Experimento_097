#pragma once
#include "physicscomponent.hpp"
#include "rendercomponent.hpp"
#include "inputcomponent.hpp"
#include <cstddef>
#include <irrlicht/irrlicht.h>

struct Entity {
    explicit Entity() = default;

    PhysicsComponent* physics {nullptr};
    RenderComponent*  render  {nullptr};
    InputComponent*   input   {nullptr};
    
    constexpr std::size_t getEntityID() const noexcept {return entityID;};

    irr::core::vector3df getLookAtVector() { return lookatVector; };
    void setLookAtVector(irr::core::vector3df vector) { 
        lookatVector.X = vector.X;
        lookatVector.Y = vector.Y;    
        lookatVector.Z = vector.Z;
    };

    irr::core::vector3df getLastMousePos() { return lastMousePos; };
    void setLastMousePos(irr::core::vector3df vector) { 
        lastMousePos.X = vector.X;
        lastMousePos.Y = vector.Y;    
        lastMousePos.Z = vector.Z;
    };
    
    unsigned char tipo;

    

    private:
    std::size_t entityID {++nextID};
    inline static std::size_t nextID {0};
    irr::core::vector3df lookatVector;
    irr::core::vector3df lastMousePos;
};