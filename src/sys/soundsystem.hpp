#pragma once
#include "../eng/fachada.hpp"

struct SoundSystem_t{
    private:
        TheFachada facherita;

    public:
        explicit SoundSystem_t();
        void update();
        ProgrammerSoundContext createinstance(int);
        void close();
        void startsound(SoundCmp&);
        void changesound(SoundCmp&,unsigned int);
    };
    
