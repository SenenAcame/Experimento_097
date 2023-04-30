#pragma once
#include "GLgEngine.hpp"
#include "../util/types.hpp"
#include "TNodo.hpp"
#include "entities/ECamera.hpp"
#include "utils/typeUsing.hpp"

//struct LevelMan;

struct GraphicEngine {
    TNodo* createNode(std::string file);

    ECamera*    getCamera() { return glEng.getActiveCamera(); }
    GLFWwindow* getWindow() { return glEng.getWindow();       }

    GlEngine glEng;

    TNodo* loadModel(std::string file);

private:
    void   loadTexture(TNodo* node, std::string text);
};