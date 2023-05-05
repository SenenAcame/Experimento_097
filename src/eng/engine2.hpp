#pragma once
#include "GLgEngine.hpp"
#include "../util/types.hpp"
#include "TNodo.hpp"
#include "entities/ECamera.hpp"
#include "utils/typeUsing.hpp"

//struct LevelMan;

struct GraphicEngine {
    TNodo* createNode  (std::string file, Vec3 sca = Vec3(1), Vec3 rot = Vec3(0), Vec3 tras = Vec3(0));
    TNodo* createPlayer(Vec3 sca = Vec3(1), Vec3 rot = Vec3(0), Vec3 tras = Vec3(0));
    void createPlayerModel(std::string file_model);

    void setCameraPlayer(std::string file_model);

    TNodo*  getNodeCamera() { return glEng.getActiveCameraNode(); }
    ECamera*    getCamera() { return glEng.getActiveCamera(); }
    Vec3&  getFrontCamera() { return getCamera()->Front; }
    GLFWwindow* getWindow() { return glEng.getWindow(); }

    GlEngine glEng {};
    TNodo* playerModel {};

    //static TNodo* loadModel(std::string file);

    //void drawHitbox(Vec3 pos, Vec3 hitb);

    //void   loadTexture(TNodo* node, std::string text);
};