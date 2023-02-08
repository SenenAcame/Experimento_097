#pragma once
#include "../eng/fachada.hpp"
#include "../util/types.hpp"

struct SoundSystem_t{
    private:
        TheFachada facherita;

    public:
    using SYSCMPs = MP::Typelist<SoundCmp>;
    using SYSTAGs = MP::Typelist<>;
        explicit SoundSystem_t();
        void update(EntyMan& EM){
            EM.foreach<SYSCMPs,SYSTAGs>(
            [&](Enty& e, SoundCmp& s) {
                if(s.cambia){
                    changesound(s);
                    s.cambia=false;
                }
                if(s.play){
                    if(isPlaying(s)){
                        s.isplaying=true;
                        s.play=false;
                        startsound(s);
                    }
                    else
                        s.isplaying=false;
                }
                //if(s.release){
                //    s.programmerSoundContext.sound->release();
                //}
            }
            );
            facherita.update();
        };
        ProgrammerSoundContext createinstance(int);
        void close();
        void startsound(SoundCmp&);
        void stopsound(SoundCmp&);
        bool isPlaying(SoundCmp&);
        void changesound(SoundCmp&);
    };
    
