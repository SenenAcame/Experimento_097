#pragma once
#include "GLgEngine.hpp"
#include "../util/types.hpp"
#include "TNodo.hpp"
#include "entities/ECamera.hpp"
#include "utils/typeUsing.hpp"

//struct LevelMan;

struct GraphicEngine {
    TNodo*   createNode(std::string file, std::string texture);
    ECamera* getCamera() { return glEng.getActiveCamera(); }

    GlEngine glEng;

    TNodo* loadModel(std::string file);

private:
    void   loadTexture(TNodo* node, std::string text);
};