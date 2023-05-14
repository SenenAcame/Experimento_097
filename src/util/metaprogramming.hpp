#pragma once
#include <cstddef>

namespace MP {
    // CONSTANT
    template<typename T, T VAL>
    struct constant { constexpr static T value {VAL}; };

    // TYPE_ID
    template<typename T>
    struct type_id { using type = T; };

    // CONSTANT BOOL
    struct false_type : constant<bool, false>{};
    struct true_type  : constant<bool, true>{};

    // IS_SAME TYPE
    template <typename T, typename U>
    struct is_same : false_type {};
    template <typename T>
    struct is_same<T, T> : true_type {};
    template <typename T, typename U>
    constexpr bool is_same_v = is_same<T, U>::value;

    // NTH_TYPE
    template <size_t N, typename... Ts>
    struct nth_type { static_assert(sizeof... (Ts) != 0, "Error: No hay elemento"); };
    template <size_t N, typename... Ts>
    using nth_type_t = typename nth_type<N, Ts...>::type;
    template <typename T, typename... Ts>
    struct nth_type<0, T, Ts...> : type_id<T> {};
    template<size_t N, typename T, typename... Ts>
    struct nth_type<N, T, Ts...> : type_id<nth_type_t<N-1, Ts...>> {};

    // POS_TYPE
    template<typename T, typename... Ts>
    struct pos_type { static_assert(sizeof... (Ts) != 0, "Error: No hay elemento"); };
    template<typename T, typename... Ts>
    constexpr size_t pos_type_v = pos_type<T, Ts...>::value;
    template<typename T, typename... Ts>
    struct pos_type<T, T, Ts...> : constant<size_t, 0>{};
    template<typename T, typename U, typename... Ts>
    struct pos_type<T, U, Ts...> : constant<size_t, 1+pos_type_v<T, Ts...>> {};

    //IFT
    template<bool COND, typename TRUE, typename FALSE>
    struct IFT : type_id<FALSE>{};
    template<bool COND, typename TRUE, typename FALSE>
    using IFT_t = typename IFT<COND, TRUE, FALSE>::type;
    template<typename TRUE, typename FALSE>
    struct IFT<true, TRUE, FALSE> : type_id<TRUE>{};

    // TYPELIST
    template<typename... Ts>
    struct Typelist{
        //or consteval
        constexpr static size_t size() noexcept { return (sizeof...(Ts)); }
        template<typename T>
        //or consteval
        constexpr static bool contains() noexcept { return (false || ... || is_same_v<T, Ts>); }
        template<typename T>
        //or consteval
        constexpr static size_t pos() noexcept {
            static_assert(contains<T>());
            return pos_type_v<T, Ts...>;
        }
    };

    // REPLACE TYPE
    template<template<typename...> class NEW, typename LIST>
    struct replace {};
    template<template<typename...> class NEW, typename LIST>
    using replace_t = typename replace<NEW, LIST>::type;
    template<template<typename...> class NEW, typename... Ts>
    struct replace<NEW, Typelist<Ts...>> { using type = NEW<Ts...>; };

    //  INSERT TEMPLATE
    template<template<typename...> class NEW, typename LIST>
    struct insert{};
    template<template<typename...> class NEW, typename LIST>
    using insert_t = typename insert<NEW, LIST>::type;
    template<template<typename...> class NEW, typename... Ts>
    struct insert<NEW, Typelist<Ts...>> { using type = Typelist<NEW<Ts>...>; };
}