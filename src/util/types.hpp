#pragma once
#include "../cmp/rendercmp2.hpp"
#include "../cmp/physicscmp2.hpp"
#include "../cmp/inputcmp2.hpp"
#include "../cmp/estado.hpp"
#include "../cmp/estadisticas.hpp"
#include "../cmp/inventario.hpp"
#include "../cmp/aicmp.hpp"
#include "../cmp/nodocmp.hpp"
#include "../cmp/soundcmp2.hpp"
#include "../cmp/selfdestcmp.hpp"
#include "../man/entityman2.hpp"
#include "gameengine.hpp"
#include <iostream>

struct TPlayer      { static constexpr uint8_t id {0}; };
struct TEnemy       { static constexpr uint8_t id {1}; };
struct TBullet      { static constexpr uint8_t id {2}; };
struct TMap         { static constexpr uint8_t id {3}; };
struct TWeapon      { static constexpr uint8_t id {4}; };
struct TEneBullet   { static constexpr uint8_t id {5}; };
struct TSpawn       { static constexpr uint8_t id {6}; };
struct TDistEnemy   { static constexpr uint8_t id {7}; };

using ComponentList = MP::Typelist<
    PhysicsCmp2, 
    RenderCmp2, 
    InputCmp2, 
    EstadoCmp, 
    EstadisticaCmp, 
    InventarioCmp, 
    AICmp, 
    NodoCmp, 
    SoundCmp,
    SelfDestCmp>;
using TagList       = MP::Typelist<TPlayer, TEnemy, TBullet, TMap, TWeapon, TEneBullet, TSpawn, TDistEnemy>;
using EntyMan       = EntityMan2<ComponentList, TagList>;
using Enty          = EntyMan::Entity;

template<typename T>
void seetype(T) { std::cout<<__PRETTY_FUNCTION__<<"\n"; }