#pragma once
#include <cstddef>
#include <vector>
#include "../cmp/entity.hpp"
#include "componentstorage.hpp"

template<typename Type>
struct EntityManager {
    using TypeProcessFunc = void (*)(Type&);
    static constexpr std::size_t kNUMINIT {100};

    explicit EntityManager(std::size_t kNUMENT = 100){
        entities_.reserve(kNUMENT);
    }

    auto& createEntity(){ 
        auto& e = entities_.emplace_back();
        auto& ph = storage.createPhysicsComponent();
        e.physics = &ph;
        e.physics->z = 10.0f;
        e.physics->vz = 0.2f;
        return e; 
    }

    void forall(TypeProcessFunc process){
        for(auto& e : entities_){
            process(e);
        }
    }

    private:
    std::vector<Entity> entities_{};
    ComponentStorage storage {kNUMINIT};
};