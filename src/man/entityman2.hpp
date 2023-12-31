#pragma once
#include "../cmp/blackboardcmp.hpp"
#include "cmpstorage2.hpp"
#include "../util/cmps.hpp"

template<typename CMPLIST, typename TAGLIST, std::size_t Capacity=1000>
struct EntityMan2 {
    using cmp_storage = CmpStorage2<CMPLIST, TAGLIST, Capacity>;

    struct Entity {
        using key_list    = MP::insert_t<Key, CMPLIST>;
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

        template<typename CMP>
        constexpr void removeCMP() {
            assert(hasCMP<CMP>());
            cmpmask -= cmp_storage::cmp_info::template mask<CMP>(); //RESTA de bit
            //devuelve un 1 espaciado con un valor de id
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
            if(hasTAG<TAG>()) tagmask -= cmp_storage::tag_info::template mask<TAG>();
        }

        constexpr void setDestroy() { destroy = true; }

        constexpr bool getDestroy() { return destroy; }

        [[nodiscard]] size_t constexpr getID() const noexcept{ return id; }

        private:
        std::size_t id { nextID++ };
        smallest_mask_type<CMPLIST> cmpmask;
        smallest_mask_type<TAGLIST> tagmask;
        key_storage st_key {};
        bool destroy { false };
        static inline std::size_t nextID { 1 };
    };

    EntityMan2(std::size_t defaultsize = Capacity) { entities_.reserve(defaultsize); }

    template<typename CMP, typename... InitParam>
    CMP& addComponent(Entity& e, InitParam&&... initVal) {
        if(e.template hasCMP<CMP>()) return getComponent<CMP>(e);
        return createComponent<CMP>(e, initVal...);
    }

    template<typename CMP>
    CMP& getComponent(Entity const& e) {
        auto& st = cmpStorage_.template getStorage<CMP>();
        Key<CMP> k = e.template getKey<CMP>();
        return st[k];
    }

    template<typename CMP>
    CMP const& getComponent(Entity const& e) const{
        auto& st = cmpStorage_.template getStorage<CMP>();
        Key<CMP> k = e.template getKey<CMP>();
        return st[k];
    }

    template<typename... CMPs>
    void removeComponents(Entity& e){
        assert(sizeof...(CMPs) !=0);
        (... && removeComponent<CMPs>(e));
    }
    
    template<typename CMP>
    bool removeComponent(Entity& e) {
        if(e.template hasCMP<CMP>()) deleteComponent<CMP>(e);
        return true;
    }

    template<typename TAG>
    void addTag(Entity& e) { e.template addTAG<TAG>(); }

    template<typename TAG>
    void removeTag(Entity& e) { e.template removeTAG<TAG>(); }

    Entity& createEntity() { return new_entities_.emplace_back(); }

    template<typename T>
    void forall(T process) {
        for(auto& e : entities_) {
            process(e);
        }

    }

    template<typename CMPs, typename TAGs>
    void foreach(auto&& process){ foreach_impl(process, CMPs{}, TAGs{}); }

    template<typename CMP>
    void foreach(auto&& process) {
        auto& sm = cmpStorage_.template getStorage<CMP>();
        for(auto& a : sm) {
            process(a);
        }
    }

    void update() {
        destroy_entities();
        transfer_entities();
    }

    auto& getEntityById(std::size_t id) { 
        for(auto& cont : entities_){
            if(cont.getID()== id) return cont; 
        }
    }

    void changeSound(SoundCmp& sound, uint8_t value) {
        sound.parametro = value;
        sound.cambia = true;
        sound.play   = true;
    }

    void callDestroy() { destroy_entities(); }

    auto& getEntities() { return entities_; }
    auto& getStorage()  { return cmpStorage_; }
    auto& getBoard()    { return blackboard_; }

private:
    void destroy_entities() {
        for(auto i {entities_.size()}; i != 0; i--){
            auto& e = entities_[i-1];
            if(e.getDestroy())  removeEntity(e, i-1);
        }
    }

    template<typename... CMPs, typename... TAGs>
    void foreach_impl(auto&& process, MP::Typelist<CMPs...>, MP::Typelist<TAGs...>) {
        for(auto& e : entities_){
            bool hasCMPs = (true && ... && e.template hasCMP<CMPs>());
            bool hasTAGs = (true && ... && e.template hasTAG<TAGs>());
            if(hasCMPs && hasTAGs) process(e, getComponent<CMPs>(e)...); 
        }
    }

    template<typename CMP, typename... InitParam>
    CMP& createComponent(Entity& e, InitParam&&... initVal) {
        auto& st = cmpStorage_.template getStorage<CMP>();
        Key<CMP> k = st.push_back(CMP { std::forward<InitParam>(initVal)... });
        e.template addCMP<CMP>(k);
        return st[k];
    }

    template<typename CMP>
    constexpr bool deleteComponent(Entity& e) noexcept {
        assert(e.template hasCMP<CMP>());
        auto k = e.template getKey<CMP>();
        cmpStorage_.template getStorage<CMP>().erase(k);
        e.template removeCMP<CMP>();
        return true;
    }

    void removeRender(Entity& e) {
        RenderCmp2& r = getComponent<RenderCmp2>(e);
        r.n->remove();
    }

    void removeEntity(Entity& e, int i) {
        if(e.template hasCMP<RenderCmp2>()) { removeRender(e); }
        removeComponents<
            PhysicsCmp2, RenderCmp2, InputCmp2, EstadoCmp, EstadisticaCmp, 
            InventarioCmp, AICmp, NodoCmp, SoundCmp, SelfDestCmp,
            SpawnCmp, InteractCMP, WeaponCmp, SalaCmp>(e);
        entities_.erase(entities_.begin() + i);
    }

    void transfer_entities() {
        for(auto& e : new_entities_)
            entities_.push_back(std::move(e));
            
        new_entities_.clear();
    }

    BlackBoardCmp       blackboard_   {};
    std::vector<Entity> entities_     {};
    std::vector<Entity> new_entities_ {};
    cmp_storage         cmpStorage_   {};
};