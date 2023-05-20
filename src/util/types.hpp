#pragma once
#include "cmps.hpp"
#include "tags.hpp"
#include "../man/entityman2.hpp"

using ComponentList = MP::Typelist<
    PhysicsCmp2, RenderCmp2, InputCmp2, EstadoCmp, EstadisticaCmp, 
    InventarioCmp, AICmp, NodoCmp, SoundCmp, SelfDestCmp,
    SpawnCmp, InteractCMP, WeaponCmp, SalaCmp, ParticleCMP, PowerUp>;

using TagList = MP::Typelist<
    TPlayer, TEnemy, TBullet, TMap, TWeapon, 
    TEneBullet, TSpawn, TInteract, TDoor, TDistEnemy, 
    TWall, TKey, TTankEnemy, TSmallEnemy, TSpwEnemy, 
    TSpwWeapon, TPowerUp>;

using EntyMan = EntityMan2<ComponentList, TagList>;
using Enty    = EntyMan::Entity;

//template<typename T>
//void seetype(T) { std::cout<<__PRETTY_FUNCTION__<<"\n"; }