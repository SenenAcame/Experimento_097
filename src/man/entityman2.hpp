#pragma once
#include <vector>
#include "../cmp/entity2.hpp"
#include "../cmp/rendercmp2.hpp"
#include "../cmp/physicscmp2.hpp"
#include "../cmp/inputcmp2.hpp"
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
        auto cmp = CMP0{};
        e.c1 = cmpStorage_.template getStorage<CMP0>().push_back(cmp);
        auto cmp2 = CMP1{};
        e.c2 = cmpStorage_.template getStorage<CMP1>().push_back(cmp2);
        auto cmp3 = CMP2{};
        e.c3 = cmpStorage_.template getStorage<CMP2>().push_back(cmp3);
        return e;
    }

    void forall(TypeProccessFunc process) {
        for(auto& e : entities_){
            process(e);
        }
    }

    template<typename Comp>
    auto& getComponente(Key<Comp> k){
        return cmpStorage_.getComp(k);
    }
private:
    std::vector<EntityType> entities_{};
    CmpStorage2<CMP0, CMP1, CMP2> cmpStorage_{};
};