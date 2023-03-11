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
    void createNode(TNode *p, TNode *s);

    // Crea una camara con los parametros para setearla
    TNode *createCamera(TNode *p, Vec1 trans, Vec3 rot, Vec3 sca);

    // Crea un Model
    TNode *createModel(TNode *p, Vec3 trans, Vec3 rot, Vec3 sca, std::string file);

    void beginScene();
    void drawScene();
    void drawSkybox(int);
    void endScene();

    void drop() { glfwTerminate(); }; 


    //callBacks
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double offset_x, double offset_y);

    //|___________________|
    //|      GETTERS      |
    //|___________________|

    camera *getCamera();
    TNode *getCameraNode();
    GLFWwindow *getWindow() { return window; };


    void setResolution(uint16_t width, uint16_t height);

private:
    uint16_t width_{1080};
    uint16_t height_{720};

    
    GLFWwindow window{nullptr};
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    float lastX_ = width_ / 2.0f;
    float lastY_ = height_ / 2.0f;
    bool firstMouse_ = true;

    void initOpenGL();
}