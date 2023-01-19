#include "rendersystem.hpp"
#include <imgui/src/imgui.h>
#include <imgui/src/imgui_impl_glfw.h>
#include <imgui/src/imgui_impl_opengl3.h>
#include <optional>
#include <stdio.h>

RenderSystem::RenderSystem(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
{
    glfwSetErrorCallback([](auto error, auto* description){
         //std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
         throw std::runtime_error("GLFW ERROR");
    });
    if(!glfwInit()){
        throw std::runtime_error("Error on GLFW init");
    }
    //init GL 3.0 + GLSL 130
    constexpr const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE); //3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);               //3.0+ only

    //create window
    m_window = glfwCreateWindow(960, 720, "Game", NULL, NULL);
    if(m_window == nullptr) throw std::runtime_error("GLFW Error creating Window");
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); //enable vsync

    // Init OpenGl
    if(glewInit() != GLEW_OK) throw std::runtime_error("Failed to initialize OpenGL loader\n");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //
    //
    ImGui::StyleColorsDark();
    //
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

RenderSystem::~RenderSystem(){

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if(m_window){
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

void RenderSystem::ImGui_preRender() const noexcept {

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void RenderSystem::ImGui_postRender() const noexcept {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
}

void RenderSystem::ImGui_renderFrameBuffer() const noexcept{
    auto* fb {m_framebuffer.get()};
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    display_h -= m_h;
    if(display_h < 0) display_h = 0;
    glWindowPos2i(0,0);
    glDrawPixels(m_w, m_h, GL_BGRA, GL_UNSIGNED_BYTE, fb);
    /*
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0,0, display_w, display_h); 
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    */
}
void RenderSystem::ImGui_renderUI() const noexcept{
    auto& io { ImGui::GetIO() };

    ImGui::Begin("Window test");
    ImGui::Text("Hola Mundo, ImGui!");
    static bool dbgWindow { false };
    {
        static bool showFPS { true };
        if(ImGui::Button("Boton")){
            if(showFPS==true)   showFPS=false;
            else                showFPS=true;
        }
        if(showFPS){
            ImGui::Text("FPS: %.2f", io.Framerate);
        } else{
            ImGui::Text("ms/f: %.2f", 1000.0f / io.Framerate);
        }

        ImGui::Checkbox("Debug Window", &dbgWindow);
        ImGui::End();
    }
    {//Debug Window
        if(dbgWindow){
        ImGui::Begin("Debug Window");
        ImGui::End();
        } 
    }
}

void RenderSystem::update(EntityManager<Entity>& EM, TheEngine& GFX){
    ImGui_preRender();

    auto lambda = [](Entity& e) {
        auto& phy {e.physics};
        //if(e.tipo=='p'){
        //    e.render->node->getParent()->setPosition({phy->x, phy->y, phy->z-10});
        //}
        //else{
            e.render->node->setPosition({phy->x, phy->y, phy->z});
        //}
    };
    
    EM.forall(lambda);
    
    GFX.beginScene();
    GFX.drawAll();
    GFX.endScene();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_renderUI();
    ImGui_renderFrameBuffer();
    ImGui_postRender();
}