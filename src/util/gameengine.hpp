#pragma once 
#include "metaprogramming.hpp"
#include <cstdint>

template<typename LIST>
using smallest_mask_type = 
        MP::IFT_t<(LIST::size() <= 8), uint8_t, 
            MP::IFT_t<(LIST::size() <= 16), uint16_t, 
                MP::IFT_t<(LIST::size() <= 32), uint32_t, 
                    uint64_t
                >
            >
        >;

template<typename LIST>
struct common_traits {
    using mask_type = smallest_mask_type<LIST>;
    
    //or consteval
    constexpr static uint8_t size() noexcept { return LIST::size(); }

    template <typename TAG>
    //or consteval
    constexpr static uint16_t id() noexcept {
        static_assert(LIST::template contains<TAG>());
        return LIST::template pos<TAG>(); 
    }

    template <typename... TAGS>
    //or consteval
    constexpr static mask_type mask() noexcept { 
        return (0 | ... | (1 << id<TAGS>())); 
    }
};

template <typename CMPLIST>
struct cmps_traits : common_traits<CMPLIST> {};
template <typename TAGLIST>
struct tags_traits : common_traits<TAGLIST> {};