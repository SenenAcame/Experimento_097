#pragma once
#include "GLgEngine.hpp"

struct LevelMan;

struct GraphicEngine {
    void createEnemy(LevelMan& LM);

    GlEngine glEng;
};