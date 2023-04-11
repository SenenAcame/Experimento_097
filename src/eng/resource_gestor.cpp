#include "resource_gestor.hpp"

ResourceGestor::ResourceGestor() {

    std::get<0>(resources_).reserve(4000);
    std::get<1>(resources_).reserve(1000);
    std::get<2>(resources_).reserve(1000);
    std::get<3>(resources_).reserve(1000);
}

ResourceGestor::ResourceGestor(unsigned int size) {
    
    std::get<0>(resources_).reserve(size);
    std::get<1>(resources_).reserve(size);
    std::get<2>(resources_).reserve(size);
    std::get<3>(resources_).reserve(size);
}