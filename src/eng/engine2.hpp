#pragma once
#include "GLgEngine.hpp"
#include "../util/types.hpp"
#include "TNodo.hpp"
#include "entities/ECamera.hpp"
#include "utils/typeUsing.hpp"

//struct LevelMan;

struct GraphicEngine {
    static TNodo* createNode(std::string file);

    ECamera*    getCamera() { return glEng.getActiveCamera(); }
    GLFWwindow* getWindow() { return glEng.getWindow();       }

    inline static GlEngine glEng {};

    static TNodo* loadModel(std::string file);

    void drawHitbox(Vec3 pos, Vec3 hitb);

private:
    void   loadTexture(TNodo* node, std::string text);
};