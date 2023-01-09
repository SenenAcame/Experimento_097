#pragma once

#include <string>
#include <iostream>
#include "../man/entitymanager.hpp"
#include "../eng/fachada.hpp"

struct SoundSystem_t{
    private:
        TheFachada facherita;

    public:
        explicit SoundSystem_t();
        void update();
        void createinstance(Entity&, int);
        void close();
        void startsound(Entity&);
        void changesound(Entity&,unsigned int);
    };
    
