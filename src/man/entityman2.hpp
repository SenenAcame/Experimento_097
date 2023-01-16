#pragma once
#include <cstddef>
#include <tuple>
#include <vector>
#include "../cmp/entity2.hpp"
#include "../cmp/rendercmp2.hpp"
#include "../cmp/physicscmp2.hpp"
#include "../cmp/inputcmp2.hpp"
#include "cmpstorage2.hpp"
#include "componentstorage.hpp"

#include <iostream>

template<typename CMPLIST, typename TAGLIST>
struct EntityMan2 {
    struct Entity;
    using TypeProccessFunc = void (*)(Entity&);
    using cmp_type = std::uint16_t;
    using cmp_storage = CmpStorage2<CMPLIST, TAGLIST>;

    struct Entity {
        using key_list = MP::insert_t<Key, CMPLIST>;
        using key_storage = MP::replace_t<std::tuple, key_list>;

        //static_assert(MP::is_same_v<smallest_mask_type<TAGLIST>, void>);

        template<typename CMP>
        void addCMP(Key<CMP> k){
            cmpmask |= cmp_storage::cmp_info::template mask<CMP>();
            std::get<Key<CMP>>(st_key) = k;
        }

        template<typename CMP>
        bool hasCMP() const noexcept{
            auto m = cmp_storage::cmp_info::template mask<CMP>();
            return cmpmask & m;
        }

        template<typename CMP>
        Key<CMP> getKey() const{
            assert(hasCMP<CMP>());
            return std::get<Key<CMP>>(st_key);
        }

        private:
        std::size_t id { nextID++ };
        smallest_mask_type<CMPLIST> cmpmask;
        smallest_mask_type<TAGLIST> tagmask;
        key_storage st_key{};
        static inline std::size_t nextID { 1 };
    };

    template<typename CMP>
    int addComponent(Entity& e) {
        auto& st = cmpStorage_.template getStorage<CMP>();
        Key<CMP> k;
        if(e.template hasCMP<CMP>()){
            k = e.template getKey<CMP>();
            return 1;
        }
        else{
            k = st.push_back(CMP{});
            e.template addCMP<CMP>(k);
            return 2;
        }
        //return st[k];
    }

    //int addComponent(Entity& e) {
    //    auto& st = cmpStorage_.template getStorage<PhysicsCmp2>();
    //    Key<PhysicsCmp2> k;
    //    if(e.template hasCMP<PhysicsCmp2>()){
    //        k = e.template getKey<PhysicsCmp2>();
    //        return 1;
    //    }
    //    else{
    //        k = st.push_back(PhysicsCmp2{});
    //        e.template addCMP<PhysicsCmp2>(k);
    //        return 2;
    //    }
    //    //return st[k];
    //}

    EntityMan2(std::size_t defaultsize = 100) {
        entities_.reserve(defaultsize);
    }

    //template<typename Comp0, typename Comp1, typename Comp2>
    //auto& createEntity() {
    //    auto& e = entities_.emplace_back();
    //    e.c1 = cmpStorage_.template getStorage<Comp0>().push_back(Comp0{});
    //    e.c2 = cmpStorage_.template getStorage<Comp1>().push_back(Comp1{});
    //    e.c3 = cmpStorage_.template getStorage<Comp2>().push_back(Comp2{});
    //    return e;
    //}

    void forall(TypeProccessFunc process) {
        for(auto& e : entities_){
            process(e);
        }
    }

    template<typename CMP>
    auto& getComponent(Key<CMP> k){
        return cmpStorage_.getComp(k);
    }
private:
    std::vector<Entity> entities_{};
    cmp_storage cmpStorage_{};
};