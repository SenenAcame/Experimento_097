#pragma once
#include <array>
#include <stdexcept>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cassert>

template <typename DataType, std::size_t Capacity>
struct Slotmap {
    using value_type = DataType;
    using index_type = std::uint32_t;
    using gen_type   = index_type;
    using key_type = struct {index_type id; gen_type gen;};

    constexpr explicit Slotmap(){clear();}
    [[nodiscard]] constexpr std::size_t size()      const noexcept {return size_;}
    [[nodiscard]] constexpr std::size_t capacity()  const noexcept {return Capacity;}
    [[nodiscard]] constexpr key_type    push_back(value_type&& value){
        return{};
    }

    constexpr void clear(){freelist_init();}

private:
    constexpr void freelist_init() noexcept{
        for(index_type i{}; i<indices_.size(); ++i){
            indices_[i].id = i+1;
        }
        freelist_ = 0;
    }

    [[nodiscard]] constexpr index_type allocate() noexcept{
        if(size_ >= Capacity) throw std::runtime_error("");
        assert(freelist_ < Capacity);

        auto slot = freelist_;
        return{};
    };

    index_type                       size_{};
    index_type                       freelist_{};
    gen_type                         generation_{};
    std::array<  key_type, Capacity> indices_{};
    std::array<value_type, Capacity> data_{};
    std::array<value_type, Capacity> erase_{};
};