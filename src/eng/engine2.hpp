#pragma once
#include "GLgEngine.hpp"

struct LevelMan;

struct GraphicEngine {
    void createEnemy(LevelMan& LM);
    void createMap(LevelMan& LM);

    GlEngine glEng;
};