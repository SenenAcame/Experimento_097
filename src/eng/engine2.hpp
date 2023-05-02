#pragma once
#include "GLgEngine.hpp"
#include "../util/types.hpp"
#include "TNodo.hpp"
#include "entities/ECamera.hpp"
#include "utils/typeUsing.hpp"

//struct LevelMan;

struct GraphicEngine {
    TNodo* createNode(std::string file, Vec3 sca = Vec3(1), Vec3 rot = Vec3(0), Vec3 tras = Vec3(0));

    ECamera*    getCamera() { return glEng.getActiveCamera(); }
    Vec3&  getFrontCamera() { return getCamera()->Front; }
    GLFWwindow* getWindow() { return glEng.getWindow(); }

    GlEngine glEng {};

    //static TNodo* loadModel(std::string file);

    //void drawHitbox(Vec3 pos, Vec3 hitb);

    //void   loadTexture(TNodo* node, std::string text);
};