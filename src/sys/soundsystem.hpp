#pragma once
#include "../util/types.hpp"
#include "../eng/fachada.hpp"

struct SoundSystem_t {
    using SYSCMPs = MP::Typelist<SoundCmp>;
    using PHYCMPs = MP::Typelist<PhysicsCmp2, SoundCmp>;
    using SYSTAGs = MP::Typelist<>;
    using ENETAGs = MP::Typelist<TEnemy>;

    explicit SoundSystem_t();
    void update(EntyMan&, std::size_t);
    ProgrammerSoundContext createinstance(int);
    void close();
    void startsound(SoundCmp&);
    void setloop(SoundCmp&);
    void stopsound(SoundCmp&);
    bool isPlaying(SoundCmp&);
    void changesound(SoundCmp&);

private:
    TheFachada facherita;
};