#pragma once
#include "../cmp/physicscomponent.hpp"
#include "../cmp/rendercomponent.hpp"
#include "../cmp/inputcomponent.hpp"
#include "../cmp/soundcomponent.hpp"
#include "../cmp/collisioncomponent.hpp"
#include <vector>

struct ComponentStorage{
    explicit ComponentStorage(std::size_t initialize);

    ComponentStorage(const ComponentStorage&) = delete;
    ComponentStorage(ComponentStorage&&)      = delete;
    ComponentStorage& operator=(const ComponentStorage&) = delete;
    ComponentStorage& operator=(ComponentStorage&&)      = delete;

    PhysicsComponent&   createPhysicsComponent(std::size_t eid);
    RenderComponent&    createRenderComponent(std::size_t eid);
    InputComponent&     createInputComponent(std::size_t eid);
    SoundComponent&     createSoundComponent(std::size_t eid);
    ColliderComponent& createColliderComponent(std::size_t eid);

    const std::vector<PhysicsComponent>&   getPhysicsComponents()   const {return phyStora;};
          std::vector<PhysicsComponent>&   getPhysicsComponents()         {return phyStora;};

    const std::vector<RenderComponent>&    getRenderComponents()    const {return renStora;};
          std::vector<RenderComponent>&    getRenderComponents()          {return renStora;};

    const std::vector<InputComponent>&     getInputComponents()     const {return inpStora;};
          std::vector<InputComponent>&     getInputComponents()           {return inpStora;};

    const std::vector<SoundComponent>&     getSoundComponents()     const {return souStora;};
          std::vector<SoundComponent>&     getSoundComponents()           {return souStora;};

    const std::vector<ColliderComponent>&     getColliderComponents()     const {return colStora;};
          std::vector<ColliderComponent>&     getColliderComponents()           {return colStora;};

    private:
    std::vector<PhysicsComponent>   phyStora {};
    std::vector<RenderComponent>    renStora {};
    std::vector<InputComponent>     inpStora {};
    std::vector<SoundComponent>     souStora {};
    std::vector<ColliderComponent> colStora {};
};