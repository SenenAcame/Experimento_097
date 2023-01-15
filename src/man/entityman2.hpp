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

    template<typename Comp0, typename Comp1, typename Comp2>
    auto& createEntity() {
        auto& e = entities_.emplace_back();
        e.c1 = cmpStorage_.template getStorage<Comp0>().push_back(Comp0{});
        e.c2 = cmpStorage_.template getStorage<Comp1>().push_back(Comp1{});
        e.c3 = cmpStorage_.template getStorage<Comp2>().push_back(Comp2{});
        return e;
    }

    void forall(TypeProccessFunc process) {
        for(auto& e : entities_){
            process(e);
        }
    }

    template<typename Comp>
    auto& getComponent(Key<Comp> k){
        return cmpStorage_.getComp(k);
    }
private:
    std::vector<EntityType> entities_{};
    CmpStorage2<MP::Typelist<CMP0, CMP1, CMP2>, MP::Typelist<>> cmpStorage_{};
};