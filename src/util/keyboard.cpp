#include "keyboard.hpp"
#include <X11/X.h>
#include <unordered_map>

bool Keyboard::isKeyPressed(KeySym k) noexcept{
    if(auto key = getIterator(k)){
        return (*key)->second;
    }
    return false;
}

void Keyboard::keyPressed(KeySym k) noexcept{
    setValue(k, true);
}

void Keyboard::keyReleased(KeySym k) noexcept{
    setValue(k, false);
}

void Keyboard::setValue(KeySym k, bool v) noexcept{
    if(auto key = getIterator(k)){
        (*key)->second = v;
    }
}

Keyboard::OptIter Keyboard::getIterator(KeySym k) noexcept{
    auto key = pressedKeys.find(k);
    if(key != pressedKeys.end()){
        return key;
    }
    return {};
}