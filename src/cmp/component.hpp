#pragma once
#include <cstddef>

struct Component{
    explicit Component (std::size_t eid) : entityID {eid}{};

    std::size_t componentID {++nextID};
    std::size_t entityID {0};
    private:
    inline static std::size_t nextID {0};
};