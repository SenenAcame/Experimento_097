#pragma once
#include <unordered_map>
#include <X11/X.h>
#include <X11/keysym.h>
#include <string>
#include <functional>
#include <iostream>
#include <optional>

struct Keyboard{
    using OptIter = std::optional<std::unordered_map<KeySym, bool>::iterator>;
    
    explicit Keyboard() = default;

    Keyboard(const Keyboard&) = delete;
    Keyboard(Keyboard&&)      = delete;
    Keyboard& operator=(const Keyboard&) = delete;
    Keyboard& operator=(Keyboard&&)      = delete;

    bool isKeyPressed(KeySym k) noexcept;
    void keyPressed(KeySym k) noexcept;
    void keyReleased(KeySym k) noexcept;

private:
    OptIter getIterator(KeySym k) noexcept;
    void setValue(KeySym k, bool v) noexcept;

    std::unordered_map<KeySym, bool> pressedKeys{
        {XK_W , false},
        {XK_A , false},
        {XK_S , false},
        {XK_D , false}
    };
};