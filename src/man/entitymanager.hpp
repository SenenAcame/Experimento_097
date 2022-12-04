#pragma once
#include <vector>
#include "../cmp/entity.hpp"

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