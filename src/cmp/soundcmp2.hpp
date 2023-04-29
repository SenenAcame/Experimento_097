#pragma once
//#include <cstdint>
extern "C" {
    #include <FMOD/src/fmod_errors.h>
}
#include <FMOD/src/fmod.hpp>
#include <FMOD/src/fmod_studio.hpp>

struct ProgrammerSoundContext {
    FMOD_SYSTEM *coreSystem;
    FMOD_STUDIO_SYSTEM *system;
    FMOD_STUDIO_EVENTINSTANCE* sound {};
    FMOD_STUDIO_PARAMETER_ID id;
};

struct SoundCmp{
    ProgrammerSoundContext programmerSoundContext {};
    int parametro;
    bool play      { false };
    bool loop      { false };
    bool cambia    { false };

    static constexpr uint8_t id { 7 }; //0010000000
};