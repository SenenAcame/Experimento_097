#pragma once
#include "../cmp/physicscomponent.hpp"
#include "../cmp/rendercomponent.hpp"
#include <cstddef>
#include <vector>

struct ComponentStorage{
    explicit ComponentStorage(std::size_t initialize);

    ComponentStorage(const ComponentStorage&) = delete;
    ComponentStorage(ComponentStorage&&)      = delete;
    ComponentStorage& operator=(const ComponentStorage&) = delete;
    ComponentStorage& operator=(ComponentStorage&&)      = delete;

    PhysicsComponent& createPhysicsComponent();
    RenderComponent&  createRenderComponent();

    const std::vector<PhysicsComponent>& getPhysicsComponents() const {return phyStora;};
          std::vector<PhysicsComponent>& getPhysicsComponents()       {return phyStora;};

    const std::vector<RenderComponent>& getRenderComponents() const {return renStora;};
          std::vector<RenderComponent>& getRenderComponents()       {return renStora;};

    private:
    std::vector<PhysicsComponent> phyStora {};
    std::vector<RenderComponent>  renStora {};
};