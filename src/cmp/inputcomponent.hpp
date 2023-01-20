#pragma once
#include "component.hpp"
#include <X11/X.h>
#include <X11/keysym.h>

struct InputComponent : public Component {
    explicit InputComponent(std::size_t eid) : Component(eid){};

    KeySym key_up     {XK_W};
    KeySym key_left   {XK_A};
    KeySym key_right  {XK_D};
    KeySym key_down   {XK_S};
    KeySym key_shot   {XK_P};
    KeySym key_sound1 {XK_B};
    KeySym key_sound2 {XK_N};
    KeySym key_sound3 {XK_M};
};