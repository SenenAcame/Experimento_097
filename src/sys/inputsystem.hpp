#pragma once
#include "../man/entitymanager.hpp"
#include <X11/X.h>
#include <X11/keysym.h>

struct InputSystem {
    explicit InputSystem() = default;
    void update(EntityManager<Entity>& EM);

    KeySym key_up    {XK_W};
    KeySym key_left  {XK_A};
    KeySym key_right {XK_S};
    KeySym key_down  {XK_D};
};