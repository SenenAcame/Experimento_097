#pragma once
#include <X11/X.h>
#include <X11/keysym.h>
#include <cstdint>

struct InputCmp2 {
    KeySym key_up            {XK_W};
    KeySym key_left          {XK_A};
    KeySym key_right         {XK_D};
    KeySym key_down          {XK_S};
    KeySym key_interaction   {XK_E};
    KeySym key_reloadALLAmmo {XK_R};
    KeySym key_weapon1       {XK_1};
    KeySym key_weapon2       {XK_2};


    KeySym key_shot          {XK_P};

    static constexpr uint8_t id {2}; //0000000100
};