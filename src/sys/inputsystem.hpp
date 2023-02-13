#pragma once
#include "../man/entitymanager.hpp"
#include "../util/keyboard.hpp"
#include "soundsystem.hpp"


struct InputSystem : public irr::IEventReceiver{
    explicit InputSystem() = default;
    
    void update(EntityManager<Entity>& EM, TheEngine& eng, SoundSystem_t& sounsys);

    virtual bool OnEvent(const irr::SEvent& event);
    void checkPressed(const irr::SEvent& event, KeySym k);

    private:
    static void onkeypressed(KeySym k);
    static void onkeyreleased(KeySym k);

    inline static Keyboard keyboard {};
};