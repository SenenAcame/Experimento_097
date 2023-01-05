#pragma once
#include <vector>
#include "cmpstorage2.hpp"
#include "componentstorage.hpp"

template<typename EntityType, typename CMP0, typename CMP1, typename CMP2>
struct EntityMan2 {
    using TypeProccessFunc = void (*)(EntityType);
    using cmp_type = std::uint16_t;

    EntityMan2(std::size_t defaultsize = 100) {
        entities_.reserve(defaultsize);
    }

    auto& createEntity() {
        auto& e = entities_.emplace_back();
        
        return e;
    }

    void forall(TypeProccessFunc process) {
        for(auto& e : entities_){
            process(e);
        }
    }
private:
    std::vector<EntityType> entities_{};
    CmpStorage2<CMP0, CMP1, CMP2> cmpStorage_{};
};