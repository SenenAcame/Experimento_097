#pragma once
//#include <cstdint>
extern "C" {
    #include <FMOD/src/fmod_errors.h>
}
#include <FMOD/src/fmod.hpp>
#include <FMOD/src/fmod_studio.hpp>
#include <FMOD/src/common.hpp>

struct ProgrammerSoundContext {
    FMOD::System* coreSystem;
    FMOD::Studio::System* system;
    FMOD::Studio::EventInstance* sound {};
    FMOD_STUDIO_PARAMETER_ID id;
};

struct SoundCmp{
    ProgrammerSoundContext programmerSoundContext {};
    int parametro;
    bool play      { false };
    bool isplaying { false };
    bool cambia    { false };

    static constexpr uint8_t id { 7 }; //0010000000
};