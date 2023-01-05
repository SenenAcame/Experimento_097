#pragma once
#include <memory>

template<typename C1, typename C2=void, typename C3=void>
struct Entity2 {

    std::unique_ptr<C1> c1{};
    std::unique_ptr<C2> c2{};
    std::unique_ptr<C3> c3{};

    template<typename Comp>
    constexpr bool hasComp() const noexcept{
        return (std::is_same<C1, Comp>::value ||
                std::is_same<C2, Comp>::value ||
                std::is_same<C3, Comp>::value);
    }

    template<typename Comp>
    constexpr Comp& getComp(){
        if constexpr      (std::is_same<C1, Comp>::value) return *c1;
        else if constexpr (std::is_same<C2, Comp>::value) return *c2;
        else if constexpr (std::is_same<C3, Comp>::value) return *c3;
    }

    template<typename Comp>
    constexpr Comp const& getComp() const{
        if constexpr      (std::is_same<C1, Comp>::value) return *c1;
        else if constexpr (std::is_same<C2, Comp>::value) return *c2;
        else if constexpr (std::is_same<C3, Comp>::value) return *c3;
    }
};

template<typename C1, typename C2>
struct Entity2<C1, C2, void>{

    std::unique_ptr<C1> c1{};
    std::unique_ptr<C2> c2{};

    template<typename Comp>
    constexpr bool hasComp() const noexcept{
        return (std::is_same<C1, Comp>::value ||
                std::is_same<C2, Comp>::value);
    }

    template<typename Comp>
    constexpr Comp& getComp(){
        if constexpr      (std::is_same<C1, Comp>::value) return *c1;
        else if constexpr (std::is_same<C2, Comp>::value) return *c2;
    }

    template<typename Comp>
    constexpr Comp const& getComp() const{
        if constexpr      (std::is_same<C1, Comp>::value) return *c1;
        else if constexpr (std::is_same<C2, Comp>::value) return *c2;
    }
};

template<typename C>
struct Entity2<C, void, void>{

    std::unique_ptr<C> c{};

    template<typename Comp>
    constexpr bool hasComp() const noexcept{
        return (std::is_same<C, Comp>::value);
    }

    template<typename Comp>
    constexpr Comp& getComp(){
        if constexpr (std::is_same<C, Comp>::value) return *c;
    }

    template<typename Comp>
    constexpr Comp const& getComp() const{
        if constexpr (std::is_same<C, Comp>::value) return *c;
    }
};