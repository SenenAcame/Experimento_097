#pragma once
#include "../man/entitymanager.hpp"
#include "../util/keyboard.hpp"

struct InputSystem {
    explicit InputSystem();
    
    void update(EntityManager<Entity>& EM);

    private:
    static void onkeypressed(KeySym k);
    static void onkeyreleased(KeySym k);

    inline static Keyboard keyboard {};
};