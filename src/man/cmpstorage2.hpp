#pragma once
#include <cstddef>
#include <tuple>
#include "../util/slotmap.hpp"

template<typename CMP0, typename CMP1, typename CMP2, std::size_t Capacity=100>
struct CmpStorage2 {
    using cmp_type = std::uint16_t;

    template<typename Comp>
    [[nodiscard]] static constexpr cmp_type getCmpID() noexcept { 
        return getCmpID(Comp{}); 
    }

    template<typename Comp>
    [[nodiscard]] constexpr auto& getStorage() noexcept {
        return  std::get<getCmpID<Comp>()>(tupla);
    }

    //template<typename Comp>
    //[[nodiscard]] constexpr auto& getStorage() noexcept {
    //    return  std::get<Slotmap<Comp, Capacity>>(tupla);
    //}

    template<typename Comp>
    [[nodiscard]] constexpr Comp& getComp(Key<Comp> k){
        return getStorage<Comp>().at(k);
    }

    template<typename Comp>
    [[nodiscard]] static constexpr cmp_type getMask() noexcept { 
        return getMask(getCmpID<Comp>()); 
    }
private:
    [[nodiscard]] static constexpr cmp_type getCmpID(CMP0) noexcept { return 0; }
    [[nodiscard]] static constexpr cmp_type getCmpID(CMP1) noexcept { return 1; }
    [[nodiscard]] static constexpr cmp_type getCmpID(CMP2) noexcept { return 2; }

    [[nodiscard]] static constexpr cmp_type getMask(cmp_type const id) noexcept { return 1 << id; }
    
    std::tuple<
        Slotmap<CMP0, Capacity>, 
        Slotmap<CMP1, Capacity>, 
        Slotmap<CMP2, Capacity>
    > tupla{};
};