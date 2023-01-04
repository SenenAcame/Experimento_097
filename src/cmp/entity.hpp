#pragma once
#include "physicscomponent.hpp"
#include "rendercomponent.hpp"
#include "inputcomponent.hpp"
#include "soundcomponent.hpp"
#include <cstddef>

struct Entity {
    explicit Entity() = default;

    PhysicsComponent* physics {nullptr};
    RenderComponent*  render  {nullptr};
    InputComponent*   input   {nullptr};
    SoundComponent*   sound   {nullptr};
    
    constexpr std::size_t getEntityID() const noexcept {return entityID;};
    
    unsigned char tipo;

    private:
    std::size_t entityID {++nextID};
    inline static std::size_t nextID {0};
};