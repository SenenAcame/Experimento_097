#include "engine.hpp"
#include <cstddef>
#include <irrlicht/IEventReceiver.h>
//IMGUI



TheEngine::TheEngine(uint32_t const w, uint32_t const h, irr::IEventReceiver* r) :width_{w}, height_{h}, receive{r}{
    if(!device_) throw std::runtime_error("Couldn't initialize device!!");
    auto* cam = smgr_->addCameraSceneNode();
    cam->bindTargetAndRotation(true);
}

auto TheEngine::loadNode(AnimatedMesh* model, Path text){
    AnimatedMeshNode* node = smgr_->addAnimatedMeshSceneNode(model);
    auto* texture = driver_->getTexture(text);
    if (!texture) throw std::runtime_error("Couldn't create texture");
    node->setMaterialTexture(0, texture);
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    return node;
}

TheEngine::AnimatedMeshNode* TheEngine::createModel(Path obj, Path asset) {
    AnimatedMesh* mesh = smgr_->getMesh(obj);
    if (!mesh){
        device_->drop();
        return nullptr;
    }
    auto node = loadNode(mesh, asset);
    return node;
}

TheEngine::AnimatedMeshNode* TheEngine::createPlayer(Path obj, Path asset) {
    auto node = createModel(obj, asset);
    auto* cam = getCamera();

    cam->setParent(node);
    cam->setPosition({ 0, 2, -3 });

    return node;
}

bool TheEngine::run() const { return device_->run(); }

void TheEngine::addStaticText(){
    guienv_->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                        irr::core::rect<irr::s32>(10,10,260,22), true);
}

void TheEngine::beginScene(){
    
    driver_->beginScene(true, true, irr::video::SColor(255, 200, 100, 140));
    
}

void TheEngine::initIMGUI(){
     glfwSetErrorCallback([](auto error, auto description){
        std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
        throw std::runtime_error("GLFW ERROR");
    });
    if (!glfwInit())
        throw std::runtime_error("ERROR GLFW INITIALIZATION");

     // GL 3.0 + GLSL 130
    constexpr const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    m_window = glfwCreateWindow(960, 720, "GAME", NULL, NULL);
    if (m_window == nullptr)
     throw std::runtime_error("ERROR GLFW creating WINDOW");
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync
    //Esto de glew creo que no hace falta
    //if(glewInit() != GLEW_OK){
    //    throw std::runtime_error("ERROR GLFW init GLEW");
    //}

    // Setup Dear ImGui context
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

}



void TheEngine::drawAll(){
    smgr_->drawAll();
    guienv_->drawAll();
}

void TheEngine::endScene(){ 
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if(m_window){
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
    driver_->endScene(); }