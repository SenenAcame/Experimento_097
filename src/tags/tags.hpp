#pragma once
#include "TBullet.hpp"
#include "TBuyer.hpp"
#include "TDoor.hpp"
#include "TEnemy.hpp"
#include "TPlayer.hpp"
#include "TWeapon.hpp"

template <typename... TagsPack> //para poner cualquier numero de tipos
struct Tags {
    template<typename Tag> 
    consteval static bool has() noexcept{ //static porque solo necesito el nombre
    //compara con todo lo que tenga en TagsPack
        return (false || ... || std::is_same_v<Tag, TagsPack>);  //((a || b) || c)
        //return (std::is_same_v<tag, TagsPack> || ...);  //(a || (b || c))
        //return (std::is_same_v<Types, Tag> 
        //|| std::is_same_v<T2, Tag>)
    }
};