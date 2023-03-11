#pragma once
#include <glad/src/glad.h>
 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../assets/shaders/stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

struct Texture {
    Texture(std::string path);
    Texture(std::vector<std::string> faces);

    ~Texture();
    void loadTexture();
    void loadCubeMap();

    std::string getTexImage();

    std::vector<std::string> cubemaps_;
    std::string texImage_;
    std::string type_;
    unsigned int ID_;
    int width, height;

    constexpr inline static uint8_t id_ {3};
};