#pragma once

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../utils/timer.hpp"

#include "RMesh.hpp"
#include <sys/types.h>
#include <vector>

struct ResourceGestor;

struct RAnimation : public Resource {

    RAnimation();
    RAnimation(std::string);
    ~RAnimation();

    void addAnimation(std::vector<RMesh>);
    int  getFrames(int animation); 

    void draw(Mat4, int *);

    constexpr inline static uint8_t id_{4};

    Timer animTimer{};

    int currentFrame = 0;
    int lastAnim = 0;

private:
    std::vector<std::vector<RMesh>> animations_;
};