#pragma once
#include "physicscomponent.hpp"
#include "rendercomponent.hpp"
#include "inputcomponent.hpp"
//#include "collisioncomponent.hpp"
#include <cstddef>

struct Entity {
    explicit Entity() = default;

    PhysicsComponent* physics {nullptr};
    RenderComponent*  render  {nullptr};
    InputComponent*   input   {nullptr};
    
    constexpr std::size_t getEntityID() const noexcept {return entityID;};
    
    unsigned char tipo;

    private:
    std::size_t entityID {++nextID};
    inline static std::size_t nextID {0};
};