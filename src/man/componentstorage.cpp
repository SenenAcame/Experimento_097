#include "componentstorage.hpp"
#include <cstddef>

ComponentStorage::ComponentStorage(std::size_t initialize){
    phyStora.reserve(initialize);
    renStora.reserve(initialize);
}

PhysicsComponent& ComponentStorage::createPhysicsComponent(){
    auto& phy = phyStora.emplace_back();
    return phy;
}

RenderComponent& ComponentStorage::createRenderComponent(){
    auto& ren = renStora.emplace_back();
    return ren;
}