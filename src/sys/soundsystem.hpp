#pragma once
#include "../util/types.hpp"
#include "../eng/fachada.hpp"

struct SoundSystem_t {
    using SYSCMPs = MP::Typelist<SoundCmp>;
    using SYSTAGs = MP::Typelist<>;

    explicit SoundSystem_t();
    void update(EntyMan& EM);
    ProgrammerSoundContext createinstance(int);
    void close();
    void startsound(SoundCmp&);
    void stopsound(SoundCmp&);
    bool isPlaying(SoundCmp&);
    void changesound(SoundCmp&);

private:
    TheFachada facherita;
};