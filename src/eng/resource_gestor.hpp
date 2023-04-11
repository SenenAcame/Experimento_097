#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <tuple>
#include <memory>
#include <string>
#include <stdio.h>
#include <iostream>
#include "resources/Resource.hpp"
#include "resources/RMaterial.hpp"
#include "resources/RMesh.hpp"
#include "resources/RShader.hpp"
#include "resources/RTexture.hpp"
#include "resources/RAnimation.hpp"

#define MATERIAL_ID 0

struct Resource;

struct ResourceGestor {

    using ResourceStorage = std::tuple<std::vector<RMaterial>, std::vector<RMesh>, std::vector<RShader>, std::vector<RTexture>, std::vector<RAnimation>>;

    ResourceGestor();
    ResourceGestor(unsigned int);

    unsigned int RMa, RMe, RS, RT, RAni;
    
    //Getters
    template <typename T>
    T *getResource(std::string rname) {

        auto &vResources = getResources<T>();

        for (unsigned int i = 0; i < vResources.size(); i++) {
            if(strcmp(rname.c_str(), vResources[i].getName().c_str()) == 0)
                return &(vResources[i]);
        }
        auto &resource = vResources.emplace_back(rname);

        return &resource;
    }

    template <typename T>
    std::vector<T> &getResources() {
        return std::get<T::id_>(resources_);
    }

private:
    //variables
    ResourceStorage resources_;
};