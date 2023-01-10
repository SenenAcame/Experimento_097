#pragma once 
#include "metaprogramming.hpp"
#include <cstddef>
#include <tuple>

template<typename TAGLIST>
struct tag_traits {
    using mask_type = 
        MP::IFT_t<
            (TAGLIST::size() <= 8), 
            uint8_t, 
            MP::IFT_t<
                (TAGLIST::size() <= 16), 
                uint16_t, 
                MP::IFT_t<
                    (TAGLIST::size() <= 32), 
                    uint32_t, 
                    uint64_t
                >
            >
        >;

    consteval static uint8_t size() noexcept { return TAGLIST::size(); }

    template <typename TAG>
    consteval static uint id() noexcept {
        static_assert(TAGLIST::template contains<TAG>());
        return TAGLIST::template pos<TAG>(); 
    }

    template <typename TAG>
    consteval static mask_type mask() noexcept { return 1 << id<TAG>(); }
};

template <typename CMPLIST>
struct component_traits : tag_traits<CMPLIST> {};

template<typename CMPS, typename TAGS>
struct GameEngine{
    using cmps = component_traits<CMPS>;
    using tags = tag_traits<TAGS>; 
    using st_type = MP::replace_t<std::tuple, CMPS>;

    st_type components_{};
};