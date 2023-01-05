#pragma once
#include <X11/X.h>
#include <X11/keysym.h>

struct InputCmp2 {
    KeySym key_up    {XK_W};
    KeySym key_left  {XK_A};
    KeySym key_right {XK_D};
    KeySym key_down  {XK_S};
    KeySym key_shot  {XK_P};
};