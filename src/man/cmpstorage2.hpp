#pragma once
#include <tuple>
#include "../util/slotmap.hpp"
#include "../util/gameengine.hpp"

template<typename CMPLIST, typename TAGLIST, size_t Capacity = 100>
struct CmpStorage2 {
    using cmp_info = cmps_traits<CMPLIST>;
    using tag_info = tags_traits<TAGLIST>;
    template<typename LIST>
    using to_tuple = MP::replace_t<std::tuple, LIST>;
    template<typename T>
    using to_slotmap = Slotmap<T, Capacity>;
    using store_t = to_tuple<MP::insert_t<to_slotmap, CMPLIST>>;

    template<typename CMP>
    [[nodiscard]] constexpr auto& getStorage() noexcept {
        constexpr auto id { cmp_info::template id<CMP>() };
        return std::get<id>(components_);
    }
private:
    store_t components_ {};
};