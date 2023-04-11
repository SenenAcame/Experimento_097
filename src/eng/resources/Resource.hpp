#pragma once

#include "../utils/typeUsing.hpp"

#include <glm/glm.hpp>
#include <string>

struct Resource {

    Resource(){};

    //setters
    void setName(std::string name);
    void load();
    void unload();

    //getters
    std::string getName();
    bool isLoaded();

protected:
    std::string name_;
    bool loaded_ {false};
};