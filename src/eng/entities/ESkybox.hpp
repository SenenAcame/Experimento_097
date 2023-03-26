#pragma once

#include <glm/glm.hpp>
#include "Entity.hpp"
#include "../resources/RMesh.hpp"
#include "ECamera.hpp"

#include <string>
#include <vector>

struct ESkybox {
    ESkybox();
    ESkybox(std::vector<std::string> images);
    ~ESkybox();
    void initSkybox();

    void draw(ECamera camera, int);

    void addFaces(std::vector<std::string> images);

private:
    RShader skyboxShader;
    unsigned int skyboxVAO, skyboxVBO;
    std::vector<RTexture> faces;
};