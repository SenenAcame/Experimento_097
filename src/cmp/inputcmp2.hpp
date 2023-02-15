#pragma once
#include <X11/X.h>
#include <X11/keysym.h>
#include <cstdint>

struct InputCmp2 {
    KeySym key_up                  {XK_W};
    KeySym key_left                {XK_A};
    KeySym key_right               {XK_D};
    KeySym key_down                {XK_S};
    KeySym key_shot                {XK_P};
    KeySym key_reloadALLAmmo       {XK_F};
    KeySym key_reloadCurrentAmmo   {XK_R};
    KeySym key_weapon1             {XK_1};
    KeySym key_weapon2             {XK_2};
    KeySym key_weapon3             {XK_3};
    KeySym key_sound1              {XK_B};
    KeySym key_sound2              {XK_N};
    KeySym key_sound3              {XK_M};

    static constexpr uint8_t id {2}; //0000000100
};