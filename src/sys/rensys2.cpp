#include "rensys2.hpp"
#include "../eng/engine.hpp"
#include "../eng/engine2.hpp"
#include <GL/gl.h>

///*VIEJO*/ void RenSys2::update(EntyMan& EM, TheEngine& GFX) {
//    //ImGUI_Prerender();
//    EM.foreach<SYSCMPs, SYSTAGs>(
//        [&](Enty& ent, PhysicsCmp2 const& phy, RenderCmp2& rend) {
//            if(ent.hasTAG<TEnemy>()) {
//                float giro = (-phy.orieny)*180/irr::core::PI+360;
//                rend.n->setRotation({rend.n->getRotation().X,giro,rend.n->getRotation().Z});
//            }
//            rend.n->setPosition({static_cast<float>(phy.x), static_cast<float>(phy.y), static_cast<float>(phy.z)});
//        }
//    );
//    drawAll(EM, GFX);
//    //RENDER in Opengl context
//    //ImGUI_renderOpenGlContext();
//    //ImGUI_Postrender();
//};

/*NUEVO*/ void RenSys2::update2(EntyMan& EM, GraphicEngine& GE) {
    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& ent, PhysicsCmp2 const& phy, RenderCmp2& rend){

            auto* cam = GE.getCamera();
            auto* n_cam = GE.glEng.getActiveCameraNode();

            rend.node->setTranslation(Vec3 { phy.x, phy.y, phy.z });
            
            //TNodo* node_cam = GE.glEng.getActiveCameraNode();
            //auto* cam = GE.getCamera();

            //std::cout << "___________________________________________________________\n";
            //std::cout << "Translacion nodo :" << node_cam->getTranslation()[0] << ", " << node_cam->getTranslation()[1] << ", " <<  node_cam->getTranslation()[2] << std::endl;
            //std::cout << "___________________________________________________________\n";
            ////node_cam->translade(node_cam->translation_ - cam->Position);
            //std::cout << "___________________________________________________________\n";
            //std::cout << "Translacion nodo :" << cam->Position[0] << ", " << cam->Position[1] << ", " <<  cam->Position[2] << std::endl;
            //std::cout << "___________________________________________________________\n";
            if(ent.hasTAG<TPlayer>()) {
                float pitch = GE.getCamera()->Pitch;
                float yaw   = GE.getCamera()->Yaw;
            
                //std::cout<<pitch<<" "<<yaw<<"\n";
            
                //GE.getCamera()->setPosition(Vec3 { -0.1+phy.x, 0.5+phy.y, 0+phy.z });
                GE.getCamera()->setPosition(Vec3 { phy.x, 0.6+phy.y, -0.1+phy.z });
                //rend.node->setRotation(Vec3 {pitch, 0, 0});
            }
        }
    );

    drawWorld(GE);
}

void RenSys2::drawAll(EntyMan& EM, TheEngine& GFX) {
    GFX.beginScene();
    GFX.drawAll();
    //drawBBox(EM, GFX);
    GFX.endScene();
}

void RenSys2::drawBBox(EntyMan& EM, TheEngine& GFX) {
    auto vd = GFX.getDevice()->getVideoDriver();
    vd->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
    EM.foreach<BOXCMPs, SYSTAGs>(
        [&](Enty& ent, PhysicsCmp2 const& phy, EstadoCmp const& state){
            vd->draw3DBox({
                { (float)phy.x-state.width, (float)phy.y-state.height, (float)phy.z-state.depth }, 
                { (float)phy.x+state.width, (float)phy.y+state.height, (float)phy.z+state.depth }
            });
        }
    );
}

void RenSys2::drawWorld(GraphicEngine &GE) {
    GE.glEng.beginScene();
    GE.glEng.drawScene();
    //GE.glEng.drawParticles();
    //GE.glEng.drawBorder();
    GE.glEng.drawSkybox(0);
    GE.glEng.endScene();
}

//IMGUI
//void RenSys2::ImGUI_renderOpenGlContext() const noexcept {
//
//    auto* frameB{m_framebuffer.get()};
//    glDrawPixels(m_w, m_h, GL_RGBA, GL_UNSIGNED_BYTE, frameB);
//
//    //int display_w, display_h;
//    //glfwGetFramebufferSize(m_window, &display_w, &display_h);
//    //glViewport(0, 0, display_w, display_h);
//    //glClearColor(0.0, 0.0, 0.0, 0.0);
//    //glClear(GL_COLOR_BUFFER_BIT);
//}

//void RenSys2::ImGUI_Prerender() const noexcept {
//
//    // Poll and handle events (inputs, window resize, etc.)
//    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
//    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
//    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//    glfwPollEvents();
//
//    // Start the Dear ImGui frame
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//}

//void RenSys2::ImGUI_Postrender() const noexcept {
//
//    // Rendering
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//    glfwSwapBuffers(m_window);
//
//}

//void RenSys2::initIMGUI() {
//    glfwSetErrorCallback([](auto error, auto description){
//        std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//        throw std::runtime_error("GLFW ERROR");
//    });
//    if (!glfwInit())
//        throw std::runtime_error("ERROR GLFW INITIALIZATION");
//
//    // GL 3.0 + GLSL 130
//    constexpr const char* glsl_version = "#version 130";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
//
//    m_window = glfwCreateWindow(960, 720, "GAME", NULL, NULL);
//    if (m_window == nullptr)
//    throw std::runtime_error("ERROR GLFW creating WINDOW");
//    glfwMakeContextCurrent(m_window);
//    glfwSwapInterval(1); // Enable vsync
//    //Esto de glew creo que no hace falta
//    //if(glewInit() != GLEW_OK){
//    //    throw std::runtime_error("ERROR GLFW init GLEW");
//    //}
//    
//    // Setup Dear ImGui context
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//
//    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
//    //ImGui::StyleColorsLight();
//
//    // Setup Platform/Renderer backends
//    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//}

//void RenSys2::EndImgui() {
//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    if(m_window) {
//        glfwDestroyWindow(m_window);
//    }
//    glfwTerminate();
//}