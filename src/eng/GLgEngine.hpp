#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "../assets/shaders/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "camara.hpp"
#include "../assets/shaders/model.hpp"
#include "TNodo.hpp"
#include "camara.hpp"
#include "typeUsing.hpp"


struct Entity;
struct Node;


struct GlEngine {

     GlEngine();
    ~GlEngine();

    //
    void createNode(TNodo *p, TNodo *s);

    // Crea una camara con los parametros para setearla
    TNodo *createCamera(TNodo *p, Vec3 trans, Vec3 rot, Vec3 sca);

    // Crea un Model
    TNodo *createModel(TNodo *p, Vec3 trans, Vec3 rot, Vec3 sca, std::string file);

    void beginScene();
    void drawScene();
    void drawSkybox(int);
    void endScene();

    void drop() { glfwTerminate(); }; 
    

    //callBacks
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double offset_x, double offset_y);
    void processInput(GLFWwindow *window);
    
    //|___________________|
    //|      GETTERS      |
    //|___________________|

    Camera *getCamera();
    TNodo *getCameraNode();
    GLFWwindow *getWindow() { return window; };


    void setResolution(uint16_t width, uint16_t height);

private:
    uint16_t width_{1080};
    uint16_t height_{720};

    inline static float deltaTime = 0.0f;
    inline static float lastFrame = 0.0f;

    GLFWwindow *window{nullptr};
    inline static Camera *camera{nullptr}; // glm::vec3(0.0f, 0.0f, 3.0f)
    inline static float lastX_ = 1080.0f / 2.0f;
    inline static float lastY_ = 720.0f / 2.0f;
    inline static bool firstMouse_ = true;

    void initOpenGL();
};