#pragma once
#include "../cmp/rendercmp2.hpp"
#include "../cmp/physicscmp2.hpp"
#include "../cmp/inputcmp2.hpp"
#include "../man/entityman2.hpp"
#include "gameengine.hpp"
#include <iostream>

struct TPlayer { static constexpr uint8_t id {0}; };
struct TEnemy  { static constexpr uint8_t id {1}; };
struct TBullet { static constexpr uint8_t id {2}; };

using ComponentList = MP::Typelist<PhysicsCmp2, RenderCmp2, InputCmp2>;
using TagList       = MP::Typelist<TPlayer, TEnemy, TBullet>;
using EntyMan       = EntityMan2<ComponentList, TagList>;
using Enty          = EntyMan::Entity;

void seetype(auto) { std::cout<<__PRETTY_FUNCTION__<<"\n"; }