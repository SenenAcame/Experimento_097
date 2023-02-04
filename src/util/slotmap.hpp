#pragma once
#include <array>
#include <stdexcept>
#include <cstdint>
#include <cassert>

template<typename CMP>
struct Key {
    using index_type = std::uint64_t;
    using gen_type   = index_type;

    index_type id{};
    gen_type   gen{};
};

template <typename DataType, std::size_t Capacity>
struct Slotmap {
    using value_type = DataType;
    using index_type = std::uint64_t;

    using gen_type   = index_type;
    using key_type   = Key<value_type>;
    using iterator   = value_type*;
    using const_iterator = value_type const*;

    constexpr explicit Slotmap() { clear(); }

    [[nodiscard]] constexpr std::size_t capacity()   const noexcept { return Capacity; }
    [[nodiscard]] constexpr std::size_t size()       const noexcept { return size_; }
    [[nodiscard]] constexpr std::size_t freelist()   const noexcept { return freelist_; }
    [[nodiscard]] constexpr std::size_t generation() const noexcept { return generation_; }
    [[nodiscard]] constexpr key_type    push_back(value_type&& value) {
        auto reservedid = allocate();
        auto& slot = indices_[reservedid];

        data_ [slot.id] = std::move(value);
        erase_[slot.id] = reservedid;

        auto key {slot};
        key.id = reservedid;

        return key;
    }
    [[nodiscard]] constexpr key_type    push_back(value_type const& value) {
        return push_back(value_type{value});
    }
    [[nodiscard]] constexpr DataType& operator[](key_type const& k) noexcept {
        assert(is_valid(k));
        auto dataID = indices_[k.id].id;
        return data_[dataID];
    }
    [[nodiscard]] constexpr DataType const& operator[](key_type const& k) const noexcept {
        assert(is_valid(k));
        auto dataID = indices_[k.id].id;
        return data_[dataID];
    }
    constexpr void clear() noexcept { freelist_init(); }

    constexpr void erase(key_type key) noexcept {
        assert(is_valid(key));
        free(key);
    }
    //constexpr bool erase(key_type key) noexcept {
    //    if(!is_valid(key)) return false;
    //        free(key);
    //    return true;
    //}
    
    [[nodiscard]] constexpr bool is_valid(key_type key) const noexcept{
        if (key.id >= Capacity || indices_[key.id].gen != key.gen) 
            return false;
        return true;
    }

    [[nodiscard]] constexpr value_type& at(key_type k){
        assert(is_valid(k));
        return data_[k.id];
    }
    
    [[nodiscard]] constexpr iterator begin() noexcept { return data_.begin(); }
    [[nodiscard]] constexpr iterator   end() noexcept { return data_.begin() + size_; }
    [[nodiscard]] constexpr iterator cbegin() const noexcept { return data_.cbegin(); }
    [[nodiscard]] constexpr iterator   cend() const noexcept { return data_.cbegin() + size_; }
private:
    [[nodiscard]] constexpr index_type allocate() {
        if(size_ >= Capacity) throw std::runtime_error("No space left in the slotmap");
        assert(freelist_ < Capacity);

        auto slotid = freelist_;
        freelist_ = indices_[slotid].id;

        auto& slot = indices_[slotid];
        slot.id = size_;
        slot.gen = generation_;

        ++size_;
        ++generation_;

        return slotid;
    }
    constexpr void free(key_type key) noexcept{
        assert(is_valid(key));

        auto& slot  = indices_[key.id];
        auto dataid = slot.id;
        slot.id     = freelist_;
        slot.gen    = generation_;
        freelist_   = key.id;

        if(dataid != size_-1){
            data_ [dataid] = data_ [size_-1];
            erase_[dataid] = erase_[size_-1];
            indices_[erase_[dataid]].id = dataid;
        }
        --size_;
        ++generation_;
    }
    constexpr void freelist_init() noexcept{
        for(index_type i{}; i<indices_.size(); ++i){
            indices_[i].id = i+1;
        }
        freelist_ = 0;
    }

    index_type                       size_{};
    index_type                       freelist_{};
    gen_type                         generation_{};
    std::array<  key_type, Capacity> indices_{};
    std::array<value_type, Capacity> data_{};
    std::array<index_type, Capacity> erase_{};
};