#pragma once
#include "physicscomponent.hpp"
#include "rendercomponent.hpp"
#include "inputcomponent.hpp"
#include <cstddef>
#include "../tags/tags.hpp"
#include <memory>

template <typename Tags, typename C1, typename C2 = void, typename C3 = void>
struct Entity {
    
    std::unique_ptr<C1> c1{};
    std::unique_ptr<C2> c2{};
    std::unique_ptr<C3> c3{};
    

   template <typename CMP>
    constexpr bool hasComponent() const noexcept{ //constexpr = se hace en tiempo de compilacion
        return (std::is_same_v<C1, CMP> 
        || std::is_same_v<C2, CMP>
        || std::is_same_v<C3, CMP>); //devuelve si C1 es = a CHealth
    }

    template <typename Tag>
    consteval static bool hasTag() noexcept{
        return Tags::template has<Tag>();
    }

    template <typename CMP>
    constexpr CMP& getComponent(){
        if constexpr(std::is_same_v<C1, CMP>) return *c1;
        else if constexpr(std::is_same_v<C2, CMP>) return *c2;
        else if constexpr(std::is_same_v<C3, CMP>) return *c3;
        throw "";
    }

    template <typename CMP>
    constexpr CMP const& getComponent() const{
        if constexpr(std::is_same_v<C1, CMP>) return *c1;
        else if constexpr(std::is_same_v<C2, CMP>) return *c2;
        else if constexpr(std::is_same_v<C3, CMP>) return *c3;
        throw "";
    }

    //explicit Entity() = default;
//
    //PhysicsComponent* physics {nullptr};
    //RenderComponent*  render  {nullptr};
    //InputComponent*   input   {nullptr};
};

//especializacion con 2
template <typename Tags, typename C1, typename C2> 
struct Entity<Tags,C1,C2,void>{
    std::unique_ptr<C1> c1 {};
    std::unique_ptr<C2> c2 {};


    template <typename Tag>
    consteval static bool hasTag() noexcept{
        return Tags::template has<Tag>();
    }

    template <typename CMP>
    constexpr bool hasComponent() const noexcept{ //constexpr = se hace en tiempo de compilacion
        return (std::is_same_v<C1, CMP> 
        || std::is_same_v<C2, CMP>); //devuelve si C1 es = a CHealth
    }

    template <typename CMP>
    constexpr CMP& getComponent(){
        if constexpr(std::is_same_v<C1, CMP>) return *c1;
        else if constexpr(std::is_same_v<C2, CMP>) return *c2;
        throw "";
    }

    template <typename CMP>
    constexpr CMP const& getComponent() const{
        if constexpr(std::is_same_v<C1, CMP>) return *c1;
        else if constexpr(std::is_same_v<C2, CMP>) return *c2;
        throw "";
    }
};