#include "Resource.hpp"

std::string Resource::getName() {
    return name_;
}

void Resource::setName(std::string name) {
    name_ = name;
}

void Resource::load() {
    loaded_ = true;
}

void Resource::unload() {
    loaded_ = false;
}

bool Resource::isLoaded() {
    return loaded_;
}