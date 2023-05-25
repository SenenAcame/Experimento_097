
#include "GLgEngine.hpp"
#include "TNodo.hpp"
#include "entities/ECamera.hpp"
#include "entities/EFoco.hpp"
#include "entities/EGenParticle.hpp"
#include "entities/EModel.hpp"
#include "resources/RMaterial.hpp"
#include "resources/RShader.hpp"
#include "resources/RTexture.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stb_image.h>

GlEngine::GlEngine() {
    initOpenGL();
    root_.addSon(&rootScene_);
    root_.addSon(&rootUI_);

    registryCameras_.reserve(2);
    registryFocos_.reserve(6);
    registryModels_.reserve(1000);

    cameraEntities_.reserve(2);
    genParticleEntities_.reserve(100);
    focoEntities_.reserve(6);
    modelEntities_.reserve(1000);

    RShader *scolor = resourceGestor_.getResource<RShader>("SHADER_COLOR");
    RShader *shaderLine = resourceGestor_.getResource<RShader>("SHADER_LINE");
    RShader *shaderParticle = resourceGestor_.getResource<RShader>("SHADER_PARTICLE");

    scolor->setShader("assets/shaders/vertex/vcolor.vs", "assets/shaders/fragment/fcolor.fs", "");
    shaderLine->setShader("assets/shaders/vertex/vline.vs", "assets/shaders/fragment/fline.fs", "");
    shaderParticle->setShader("assets/shaders/vertex/vparticle.vs", "assets/shaders/fragment/fparticle.fs", "");

    scolor->loadShaders();
    shaderLine->loadShaders();
    shaderParticle->loadShaders();

    Vec3 trans(0.0f, 10.0f, 0.0f);
    Vec3 trans3(c0);
    Vec3 trans2(20.0f, 10.0f, -3.0f);
    Vec3 rot(0.0f, 0.0f, 0.0f);
    Vec3 scl(1.0f);

    //createCamera(NULL, Vec3{0, 0, 0}, rot, scl);
    //setActiveCamera(0);
    //camera_ = getActiveCamera();

    EFoco::lightType direct = EFoco::directional;
    EFoco::lightType point  = EFoco::punctual;

    // foco direccional
    createFoco(NULL, trans, rot, scl, 
               0.5f,                        //  intensidad
               direct,                      //  tipo  
               1,                           //  aper
               1,                           //  angAttenuation
               0,                           //  constAtt
               0,                           //  linearAtt
               0,                           //  quadratic
               Vec3(-0.2f, -1.0f, -0.3f),   //  direction
               Vec3(0.2f),                  //  ambient
               Vec3(0.8f),                  //  diffusion
               Vec3(0.05f),                 //  pos
               scolor );               //  shader
    
    createFoco(NULL, trans2, rot, scl, 
               0.5f,                        //  intensidad
               point,                       //  tipo  
               1,                           //  aper
               1,                           //  angAttenuation
               1.0f,                        //  constAtt
               0.09f,                       //  linearAtt
               0.032f,                      //  quadratic
               Vec3(0.f),                   //  direction
               Vec3(0.1f),                  //  ambient
               White_light,                 //  diffusion
               Vec3(-3.0f, 3.0f, 3.0f),     //  pos
               scolor );               //  shader
    
    createFoco(NULL, trans2, rot, scl, 
               0.5f,                        //  intensidad
               point,                       //  tipo  
               1,                           //  aper
               1,                           //  angAttenuation
               1.0f,                        //  constAtt
               0.09f,                       //  linearAtt
               0.032f,                      //  quadratic
               Vec3(0.f),   //  direction
               Vec3(0.1f),                  //  ambient
               White_light,                //  diffusion
               Vec3(3.0f, 3.0f, 3.0f),            //  pos
               scolor );               //  shader
    
    createFoco(NULL, trans2, rot, scl, 
               0.5f,                        //  intensidad
               point,                       //  tipo  
               1,                           //  aper
               1,                           //  angAttenuation
               1.0f,                        //  constAtt
               0.09f,                       //  linearAtt
               0.032f,                      //  quadratic
               Vec3(-0.f),   //  direction
               Vec3(0.1f),                  //  ambient
               White_light,                //  diffusion
               Vec3(4.0f, -4.f, -4.f),            //  pos
               scolor );               //  shader
    
    createFoco(NULL, trans2, rot, scl, 
               1.f,                        //  intensidad
               point,                       //  tipo  
               1,                           //  aper
               1,                           //  angAttenuation
               1.0f,                        //  constAtt
               0.09f,                       //  linearAtt
               0.032f,                      //  quadratic
               Vec3(0.f),   //  direction
               Vec3(0.1f),                  //  ambient
               White_light,                //  diffusion
               Vec3(-4.f, 10.f, 4.f),            //  pos
               scolor );               //  shader

    pointSize = 0;

    //RTexture *textule = resourceGestor_.getResource<RTexture>("assets/textures/partExplosion.png");
    //EGenParticle partGen (shaderParticle, textule, 50);

    // Skybox
    std::vector<std::string> faces {
        "assets/skybox/fondito.jpg",
        "assets/skybox/fondito.jpg",
        "assets/skybox/fondito.jpg",
        "assets/skybox/fondito.jpg",
        "assets/skybox/fondito.jpg",
        "assets/skybox/fondito.jpg"
    };

    Skybox.initSkybox();
    Skybox.addFaces(faces);
}

GlEngine::~GlEngine(){

}

void GlEngine::get_resolution() {
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    width_ = mode->width;
    height_ = mode->height;
}

void GlEngine::initOpenGL() {
    //_________GLFW INIT_____________
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    //get_resolution();
    //______CREATE GLFW WINDOW__________
    window = glfwCreateWindow(width_, height_, "Experimento 097",/*glfwGetPrimaryMonitor()*/NULL, NULL);
    if(window == NULL) throw std::runtime_error("GLFW Error creating Window");
    
    //pantalla grande
    //glfwMaximizeWindow(window);
    

    //elimina la pantalla grande
    //glfwRestoreWindow(window);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback); // optional

   
    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // IMAGEN DE LA  VENTANA

    //GLFWimage images[1];
    //images[0].pixels = stbi_load();
    //glfwSetWindowIcon(window, 1, images);
    //stbi_image_free(images[0].pixels);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    stbi_set_flip_vertically_on_load(false);
    //configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glEnable(GL_CULL_FACE);
    glEnable(GL_FRAMEBUFFER_SRGB);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GlEngine::createNode(TNodo *father, TNodo *son, bool UI) {

    if(father == nullptr) {
        if(UI) {
            father = &rootUI_;
            son->setTranslation(Vec3(0.0f));
            son->UI_ = true;
        }
        else {
            father = &rootScene_;
        }
    }
    son->setFatherNode(father);
    father->addSon(son);
    son->updateMat_ = true;
}

TNodo *GlEngine::createCamera(TNodo *father, Vec3 trans, Vec3 rot, Vec3 sca) {
    TNodo &son = registryCamera(trans, rot, sca);

    createNode(father, &son, false);

    auto &camera = cameraEntities_.emplace_back();
    son.setEntity(&camera);

    return &son;
}

TNodo *GlEngine::createFoco(TNodo *father, Vec3 trans, Vec3 rot, Vec3 sca, float intensity, EFoco::lightType mLightType, float aperture, float angAtten, float constAtten, float linearAtten, float quadraAtten, Vec3 dir, Vec3 ambient, Vec3 diffuse, Vec3 pos, RShader *shader) {

    auto &son = registryFoco(trans, rot, sca);
    createNode(father, &son);

    auto &foco = focoEntities_.emplace_back(intensity, mLightType, aperture, angAtten, constAtten, linearAtten, quadraAtten, dir, ambient, diffuse, pos, shader);
    son.setEntity(&foco);

    if(mLightType == EFoco::lightType::punctual) {
        foco.pointID = pointSize;
        pointSize++;
    }

    return &son;
}

TNodo *GlEngine::createModel(TNodo *father, Vec3 trans, Vec3 rot, Vec3 sca, std::string file, bool floor, bool UI, bool animated, std::vector<std::string> animations, std::vector<int> animationFrames) {

    auto &son = registryModel(trans, rot, sca);
    createNode(father, &son, UI);

    EModel *model{nullptr};

    for (unsigned int i = 0; i < modelEntities_.size(); ++i) {
        if(modelEntities_[i].unused_) {
            model = &(modelEntities_[i]);

            model->init();

            model->loadModel(file, resourceGestor_);

            break;
        }
    }

    if(!model)
        model = &(modelEntities_.emplace_back(file, resourceGestor_, false));
    
    son.setEntity(model);
    son.floor_ = floor;
    
    auto *mesh = model->getMesh();

    son.xRad = (abs(mesh->maxVec.x) + abs(mesh->minVec.x)) / 2.0f;
    son.yRad = (abs(mesh->maxVec.y) + abs(mesh->minVec.y)) / 2.0f;
    son.zRad = (abs(mesh->maxVec.z) + abs(mesh->minVec.z)) / 2.0f;

    if(animated && animations.size() > 0) {
        model->loadAnimation(animations, resourceGestor_, animationFrames);
    }

    return &son;
}

int partCont = 0;
EGenParticle &GlEngine::createGenParticle(std::string textureFileName /* = assets/wall.jpg */, unsigned int maxParticles) {

    if(partCont != 0) {
        for(uint16_t i = 0; i < genParticleEntities_.size(); i++) {
            if(strcmp(genParticleEntities_[i].texture->getName().c_str(), textureFileName.c_str())) //if his maxparticles is less -> rescale
                return genParticleEntities_[i];
        }
    }
    partCont++;
    
    RShader *shaderParticle = resourceGestor_.getResource<RShader>("SHADER_PARTICLE");
    RTexture *texture = resourceGestor_.getResource<RTexture>(textureFileName);

    return genParticleEntities_.emplace_back(shaderParticle, texture, maxParticles);
}

void GlEngine::restartPFocos() {
    pointSize = 0;

    for (unsigned int i=0; i < registryFocos_.size(); ++i) {
        EFoco *foco = registryFocos_[i].getEntity<EFoco>();
        if(foco->getLightType() == EFoco::lightType::punctual) {
            foco->unused_ = true;
            foco->setIntensity_(0.0f);
            foco->setPosition(Vec3(100000.0f));
        }
    }
}

TNodo *GlEngine::useFirstUnusedPFoco(int posx, int posy, int posz, float intensity, std::string color, int distance) {
    for (unsigned int i = 0; i < registryFocos_.size(); ++i) {
        EFoco *foco = registryFocos_[i].getEntity<EFoco>();
        if(foco->unused_ && foco->getLightType() == EFoco::lightType::punctual) {
            foco->unused_ = false;
            foco->changeDiffClolor(foco->checkColor(color));
            foco->changeDistance(distance);
            foco->setPosition(Vec3(posx, posz, posy));
            foco->setIntensity_(intensity);

            pointSize++;
            return &(registryFocos_[i]);
        }
    }
    return &(registryFocos_[registryFocos_.size()-1]);
}

void GlEngine::beginScene() {

    // Per frame time logic
    // ____________________
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
    //________
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GlEngine::drawSkybox(int actual) {
    setActiveCamera(0);
    auto *camera = getActiveCamera();
    Skybox.draw(*camera, actual);
}

void GlEngine::endScene() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void GlEngine::drawScene() {

    setActiveCamera(0);
    auto *camera = getActiveCamera();

    Mat4 matrix(1.0f);
    Mat4 projection = getPerspective();
    Mat4 view = camera->GetViewMatrix();

    RShader *shaderColor = resourceGestor_.getResource<RShader>("SHADER_COLOR");

    shaderColor->use();
    shaderColor->setVec3("viewPos", camera->Position);
    shaderColor->setInt("pointSize", pointSize);
    shaderColor->setVec3("spotLight.position", camera->Position);
    shaderColor->setVec3("spotLight.direction", camera->Front);

    shaderColor->setMat4("projection", projection);
    shaderColor->setMat4("view", view);

    rootScene_.run(matrix, false);
}

void GlEngine::drawParticles() {

    setActiveCamera(0);
    auto *camera = getActiveCamera();

    Mat4 projection = getPerspective();
    Mat4 view = camera->GetViewMatrix();

    RShader *shaderParticle = resourceGestor_.getResource<RShader>("SHADER_PARTICLE");

    shaderParticle->use();
    shaderParticle->setMat4("projection", projection);

    for(uint8_t i = 0; i < genParticleEntities_.size(); ++i) {
        genParticleEntities_[i].draw(view);
    }
}

TNodo &GlEngine::registryCamera(Vec3 transl, Vec3 rot, Vec3 sca) {
    return registryCameras_.emplace_back(transl, rot, sca);
}

TNodo &GlEngine::registryFoco(Vec3 transl, Vec3 rot, Vec3 sca) {
    activeFocos_.push_back(true);
    return registryFocos_.emplace_back(transl, rot, sca);
}

TNodo &GlEngine::registryModel(Vec3 transl, Vec3 rot, Vec3 sca) {
    for (unsigned int i = 0; i < registryModels_.size(); ++i) {
        if(!(registryModels_[i].entity_)) {
            registryModels_[i].translation_ = transl;
            registryModels_[i].rotation_ = rot;
            registryModels_[i].scale_ = sca;
            registryModels_[i].updateMat_ = true;
            return registryModels_[i];
        }
    }
    return registryModels_.emplace_back(transl, rot, sca);
}
/*
void GlEngine::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //camera->ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //camera->ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //camera->ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        //camera->ProcessKeyboard(RIGHT, deltaTime);
    }
}
*/
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void GlEngine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void GlEngine::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse_)
    {
        lastX_ = xpos;
        lastY_ = ypos;
        firstMouse_ = false;
    }

    float xoffset = xpos - lastX_;
    float yoffset = lastY_ - ypos; // reversed since y-coordinates go from bottom to top

    lastX_ = xpos;
    lastY_ = ypos;

    camera_->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void GlEngine::setCallbackScroll(void (*function)(GLFWwindow *, double , double))
{
    glfwSetScrollCallback(window, function);
}

void GlEngine::updateCameraRotation() {
    TNodo *cameraNode = getActiveCameraNode();
    ECamera *cEntity = getActiveCamera();


    Vec3 tmpRot(0.0f);
    tmpRot = {cEntity->Pitch, cEntity->Yaw, 0.0f};

    cameraNode->setRotation(tmpRot);
}

ECamera *GlEngine::getActiveCamera() {
    return registryCameras_[activeCamera_].getEntity<ECamera>();
}

TNodo *GlEngine::getActiveCameraNode() {
    return &(registryCameras_[activeCamera_]);
}

Mat4 GlEngine::getPerspective() {
    auto *camera = getActiveCamera();
    return glm::perspective(glm::radians(camera->Zoom), (float)width_ / (float)height_, 0.01f, 100.0f);
}

void GlEngine::updateAllParticles(float dt) {
    for(uint16_t i=0; i < genParticleEntities_.size(); i++) {
        genParticleEntities_[i].update(dt);
    }
}

void GlEngine::setCamera_(ECamera* cam) {
    camera_ =cam;
}

void GlEngine::setActiveCamera(int nCamera) {
    activeCamera_ = nCamera;
}

void GlEngine::setActiveFoco(int nFoco, bool active) {
    activeFocos_[nFoco] = active;
}

void GlEngine::setResolution(uint16_t width, uint16_t height) {
    width_ = width;
    height_ = height;
    glfwSetWindowSize(window, width_, height_);
}

void GlEngine::drawFocos() {
    setActiveCamera(0);
    auto *camera = getActiveCamera();

    Mat4 projection = getPerspective();
    Mat4 view = camera->GetViewMatrix();
    
    for(uint8_t i = 0; i < focoEntities_.size(); i++) {
        focoEntities_[i].draw(projection, true);
    }
}
