#pragma once

#include "utils/typeUsing.hpp"

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TNodo.hpp"
#include "entities/EFoco.hpp"
#include "entities/ECamera.hpp"
#include "entities/EModel.hpp"
#include "entities/ESkybox.hpp"
#include "entities/EGenParticle.hpp"

#include "resource_gestor.hpp"
#include "resources/RShader.hpp"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#define c0 0.0f

struct Entity;
struct EFoco;
struct TNodo;
struct ResourceGestor;


struct GlEngine {

     GlEngine();
    ~GlEngine();

    //
    void createNode(TNodo *father, TNodo *son, bool UI = false);

    // Crea una camara con los parametros para setearla
    TNodo *createCamera(TNodo *father, Vec3 trans, Vec3 rot, Vec3 sca);

    //Crea una luz
    TNodo *createFoco(TNodo *father, Vec3 trans, Vec3 rot, Vec3 sca, float intensity, EFoco::lightType mLightType, float aperture, float angAtten, float constAtten, float linearAtten, float quadraAtten, Vec3 dir, Vec3 ambient, Vec3 diffuse, Vec3 pos, RShader *shader);

    // Crea un Model
    TNodo *createModel(TNodo *father, Vec3 trans, Vec3 rot, Vec3 sca, std::string file, bool floor = false, bool UI = false, bool animated = false, std::vector<std::string> animations = {}, std::vector<int> animationFrames = {});

    EGenParticle &createGenParticle(std::string texFileName = "assets/wall.jpg", unsigned int maxParticles = 50);

    void restartPFocos();
    TNodo *useFirstUnusedPFoco(int posx, int posy, int posz, float intensity, std::string color, int distance);

    TNodo &registryCamera(Vec3 transl, Vec3 rot, Vec3 sca);
    TNodo &registryFoco(Vec3 transl, Vec3 rot, Vec3 sca);
    TNodo &registryModel(Vec3 transl, Vec3 rot, Vec3 sca);

    void beginScene();
    void drawScene();
    void drawParticles();
    //void drawUI();
    void drawBorder();
    void drawSkybox(int);
    void endScene();
    void drawFocos();

    void drop() { glfwTerminate(); }; 
    

    //callBacks
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void setCallbackScroll(void (*function)(GLFWwindow *, double , double));
    //void processInput(GLFWwindow *window);
    
    void updateCameraRotation();

    //|___________________|
    //|      GETTERS      |
    //|___________________|

    TNodo *getRoot() { return &root_; }
    ECamera *getActiveCamera();
    TNodo *getActiveCameraNode();
    ResourceGestor *getRG() { return &resourceGestor_;}
    GLFWwindow *getWindow() { return window;  }
    uint16_t getWidth()     { return width_;  }
    uint16_t getHeight()    { return height_; }

    bool shouldClose() { return glfwWindowShouldClose(window); }

    Mat4 getPerspective();


    // _______________________
    // _______Setters_________
    // _______________________

    void setActiveCamera(int nCamera);
    void setActiveFoco(int nFoco, bool active);
    void setResolution(uint16_t width, uint16_t height);

    void eraseLastFoco() {
        pointSize--;
    }

    float deltaTime = 0.0f;

private:
    uint16_t width_{1080};
    uint16_t height_{720};

    TNodo root_{};
    TNodo rootScene_{};
    TNodo rootUI_{};
    ResourceGestor resourceGestor_{};

    std::vector<TNodo> registryFocos_;
    std::vector<TNodo> registryModels_;
    std::vector<TNodo> registryCameras_;
 
    std::vector<EFoco>   focoEntities_;
    std::vector<EModel>  modelEntities_;
    std::vector<ECamera> cameraEntities_;

    std::vector<EGenParticle> genParticleEntities_;

    float lastFrame = 0.0f;
    int activeCamera_, activeViewport_;
    std::vector<bool> activeFocos_;
    int pointSize{0};

    ESkybox Skybox;

    GLFWwindow *window{nullptr};
    inline static ECamera *camera_{nullptr}; // glm::vec3(0.0f, 0.0f, 3.0f)
    inline static float lastX_ = 1080.0f / 2.0f;
    inline static float lastY_ = 720.0f / 2.0f;
    inline static bool firstMouse_ = true;

    void initOpenGL();
};