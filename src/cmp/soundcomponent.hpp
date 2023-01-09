#pragma once
#include "component.hpp"
extern "C"{
    #include <FMOD/src/fmod_errors.h>
}
#include <FMOD/src/fmod.hpp>
#include <FMOD/src/fmod_studio.hpp>
#include <FMOD/src/common.hpp>

struct ProgrammerSoundContext {
    FMOD::System* coreSystem;
    FMOD::Studio::System* system;
};

struct SoundComponent : public Component{
    explicit SoundComponent(std::size_t eid) : Component(eid){};
    ProgrammerSoundContext programmerSoundContext{};
    FMOD::Studio::EventInstance* sound{};
    FMOD_STUDIO_PARAMETER_ID id;
};