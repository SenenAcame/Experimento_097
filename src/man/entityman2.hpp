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

template<typename CMPLIST, typename TAGLIST, std::size_t Capacity=100>
struct EntityMan2 {
    struct Entity;
    using TypeProccessFunc = void (*)(Entity&);
    using cmp_storage = CmpStorage2<CMPLIST, TAGLIST, Capacity>;

    struct Entity {
        using key_list = MP::insert_t<Key, CMPLIST>;
        using key_storage = MP::replace_t<std::tuple, key_list>;

        template<typename CMP>
        constexpr void addCMP(Key<CMP> k) {
            cmpmask |= cmp_storage::cmp_info::template mask<CMP>();
            std::get<Key<CMP>>(st_key) = k;
        }

        template<typename CMP>
        [[nodiscard]] constexpr bool hasCMP() const noexcept{
            auto m = cmp_storage::cmp_info::template mask<CMP>();
            return cmpmask & m;
        }

        template<typename CMP>
        [[nodiscard]] constexpr Key<CMP> getKey() const{
            assert(hasCMP<CMP>());
            return std::get<Key<CMP>>(st_key);
        }

        template<typename TAG>
        constexpr void addTAG() { tagmask |= cmp_storage::tag_info::template mask<TAG>(); }

        template<typename TAG>
        [[nodiscard]] constexpr bool hasTAG() const noexcept{
            auto m = cmp_storage::tag_info::template mask<TAG>();
            return tagmask & m;
        }

        template<typename TAG>
        constexpr void removeTAG() {
            if(hasTAG<TAG>())
                tagmask -= cmp_storage::tag_info::template mask<TAG>();
        }

        private:
        std::size_t id { nextID++ };
        smallest_mask_type<CMPLIST> cmpmask;
        smallest_mask_type<TAGLIST> tagmask;
        key_storage st_key{};
        static inline std::size_t nextID { 1 };
    };

    EntityMan2(std::size_t defaultsize = 100) { entities_.reserve(defaultsize); }

    template<typename CMP, typename... InitParam>
    CMP& addComponent(Entity& e, InitParam&&... initVal) {
        auto& st = cmpStorage_.template getStorage<CMP>();
        Key<CMP> k;
        if(e.template hasCMP<CMP>()){
            k = e.template getKey<CMP>();
        }
        else{
            k = st.push_back(CMP{ std::forward<InitParam>(initVal)... });
            e.template addCMP<CMP>(k);
        }
        return st[k];
    }

    template<typename CMP>
    auto& getComponent(Key<CMP> k) { return cmpStorage_.getComp(k); }

    template<typename TAG>
    void addTag(Entity& e) { e.template addTAG<TAG>(); }

    template<typename TAG>
    void removeTag(Entity& e) { e.template removeTAG<TAG>(); }

    Entity& createEntity() { return entities_.emplace_back(); }

    template<typename T>
    void forall(T process) {
        for(auto& e : entities_){
            process(e);
        }
    }

private:
    std::vector<Entity> entities_{};
    cmp_storage cmpStorage_{};
};