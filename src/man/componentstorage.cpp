#include "componentstorage.hpp"

ComponentStorage::ComponentStorage(std::size_t initialize){
    phyStora.reserve(initialize);
    renStora.reserve(initialize);
    inpStora.reserve(initialize);
}

PhysicsComponent& ComponentStorage::createPhysicsComponent(std::size_t eid){
    auto& phy = phyStora.emplace_back(eid);
    return phy;
}

RenderComponent& ComponentStorage::createRenderComponent(std::size_t eid){
    auto& ren = renStora.emplace_back(eid);
    return ren;
}

InputComponent& ComponentStorage::createInputComponent(std::size_t eid){
    auto& inp = inpStora.emplace_back(eid);
    return inp;
}

SoundComponent& ComponentStorage::createSoundComponent(std::size_t eid){
    auto& sou = souStora.emplace_back(eid);
    return sou;
}