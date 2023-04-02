#pragma once
#include <cstdint>

struct TPlayer     { static constexpr uint8_t id {0};  };
struct TEnemy      { static constexpr uint8_t id {1};  };
struct TBullet     { static constexpr uint8_t id {2};  };
struct TMap        { static constexpr uint8_t id {3};  };
struct TWeapon     { static constexpr uint8_t id {4};  };
struct TEneBullet  { static constexpr uint8_t id {5};  };
struct TSpawn      { static constexpr uint8_t id {6};  };
struct TInteract   { static constexpr uint8_t id {7};  };
struct TDoor       { static constexpr uint8_t id {8};  };
struct TDistEnemy  { static constexpr uint8_t id {9};  };
struct TWall       { static constexpr uint8_t id {10}; };
struct TKey        { static constexpr uint8_t id {11}; };
struct TTankEnemy  { static constexpr uint8_t id {12}; };
struct TSmallEnemy { static constexpr uint8_t id {13}; };