#pragma once
#include "GLgEngine.hpp"
#include "../util/types.hpp"
#include "TNodo.hpp"
#include "entities/ECamera.hpp"
#include "utils/typeUsing.hpp"
#include <cstdint>

struct GraphicEngine {
    TNodo* createNode    (std::string file, Vec3 sca = Vec3(1), Vec3 rot = Vec3(0), Vec3 tras = Vec3(0));
    TNodo* createNodeAnim(std::string file, std::vector<std::string> anim, std::vector<int> framesAnim, Vec3 sca = Vec3(1), Vec3 rot = Vec3(0), Vec3 tras = Vec3(0));
    TNodo* createPlayer  (Vec3 sca = Vec3(1), Vec3 rot = Vec3(0), Vec3 tras = Vec3(0));
    
    void   createPlayerModel(std::string file_model);
    void   removePlayerModel();

    void beginScene();
    void drawScene();
    void drawAllScene();
    void endScene();

    void setCameraPlayer(std::string file_model);
    void setWindowClose();
    void setWindowResolution(int width, int height);

    TNodo*   getNodeCamera() { return glEng.getActiveCameraNode(); }
    ECamera*     getCamera() { return glEng.getActiveCamera(); }
    Vec3&   getFrontCamera() { return getCamera()->Front; }
    GLFWwindow*  getWindow() { return glEng.getWindow(); }
    bool    getCloseWindow() { return glEng.shouldClose(); }
    uint16_t     getHeight() { return glEng.getHeight(); }
    uint16_t      getWidth() { return glEng.getWidth(); }
    Vec3 getPlayerModelPos() { return playerModel->getPosition(); }
    GlEngine glEng {};
    
private:
    
    TNodo* playerModel {};
};