#include "rensys2.hpp"
//#include "../eng/engine.hpp"
#include "../eng/engine2.hpp"
#include <cstddef>
#include <iterator>
//IMGUI
#include <GL/gl.h>
#include <imgui/src/imgui.h>
#include <imgui/src/imgui_impl_glfw.h>
#include <imgui/src/imgui_impl_opengl3.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

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

/*NUEVO*/ void RenSys2::update2(EntyMan& EM, GraphicEngine& GE, size_t player_ID) {
    //ImGUI_Prerender();

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& ent, PhysicsCmp2& phy, RenderCmp2& rend){
            if(ent.hasTAG<TEnemy>())  rotateEnemy (rend, phy); 
            if(ent.hasTAG<TWeapon>()) rotateWeapon(rend, phy); 
            
            rend.node->setTranslation(Vec3 { phy.x, phy.y, phy.z });
            GE.glEng.drawScene();
        }
    );
    updateCamera(EM, GE, player_ID);

    drawWorld(GE);

    //ImGUI_RenderUI();
    //ImGUI_Postrender(GE);
}

void RenSys2::updateCamera(EntyMan& EM, GraphicEngine& GE, size_t player_ID) {
    auto& player = EM.getEntityById(player_ID);
    auto& phy    = EM.getComponent<PhysicsCmp2>(player);
    auto& ren    = EM.getComponent<RenderCmp2>(player);
    auto& sala   = EM.getComponent<SalaCmp>(player);

    //std::cout<<"Posicion jugador: "<<phy.x<<" "<<phy.y<<" "<<phy.z<<"\n";
    //std::cout<<"Sala jugador: "<<sala.sala<<"\n";

    float pitch = GE.getCamera()->Pitch;
    float yaw   = GE.getCamera()->Yaw;

    ren.node->setRotation(Vec3(0, -yaw, pitch));

    phy.orienx = glm::radians(pitch);
    phy.orieny = glm::radians(yaw);
}


///*VIEJO*/ void RenSys2::drawAll(EntyMan& EM, TheEngine& GFX) {
//    GFX.beginScene();
//    GFX.drawAll();
//    //drawBBox(EM, GFX);
//    GFX.endScene();
//}

///*VIEJO*/ void RenSys2::drawBBox(EntyMan& EM, TheEngine& GFX) {
//    auto vd = GFX.getDevice()->getVideoDriver();
//    vd->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
//    EM.foreach<BOXCMPs, SYSTAGs>(
//        [&](Enty& ent, PhysicsCmp2 const& phy, EstadoCmp const& state){
//            vd->draw3DBox({
//                { (float)phy.x-state.width, (float)phy.y-state.height, (float)phy.z-state.depth }, 
//                { (float)phy.x+state.width, (float)phy.y+state.height, (float)phy.z+state.depth }
//            });
//        }
//    );
//}

void RenSys2::drawWorld(GraphicEngine &GE) {
    GE.glEng.beginScene();
    GE.glEng.drawScene();
    //GE.glEng.drawParticles();
    //GE.glEng.drawBorder();
    GE.glEng.drawSkybox(0);
    GE.glEng.endScene();
}

void RenSys2::rotateWeapon(RenderCmp2 &rend, PhysicsCmp2 &phy) {
    rend.node->rotate(Vec3 { 0, 1, 0 });

    phy.y += rend.elev;

    if(phy.y >= 3.5) rend.elev = -0.01;
    if(phy.y <= 2.5) rend.elev = 0.01;
}

void RenSys2::rotateEnemy(RenderCmp2 &rend, PhysicsCmp2 &phy) {
    float giro_y = (-phy.orieny) * 180 / PI + 90;
    rend.node->setRotation(Vec3 { 0, giro_y, 0 });
}

//IMGUI
void RenSys2::initIMGUI(GraphicEngine& GE) {
    //glfwSetErrorCallback([](auto error, auto description){
    //    std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    //    throw std::runtime_error("GLFW ERROR");
    //});
    //if (!glfwInit())
    //    throw std::runtime_error("ERROR GLFW INITIALIZATION");
    //
    //// GL 3.0 + GLSL 130
    //constexpr const char* glsl_version = "#version 130";
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    ////glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    ////glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    //auto* m_window = GE.getWindow();
    //if (m_window == nullptr)
    //throw std::runtime_error("ERROR GLFW creating WINDOW");
    //glfwMakeContextCurrent(m_window);
    //glfwSwapInterval(1); // Enable vsync
    ////Esto de glew creo que no hace falta
    ////if(glewInit() != GLEW_OK){
    ////    throw std::runtime_error("ERROR GLFW init GLEW");
    ////}

    constexpr const char* glsl_version = "#version 130";
    auto* m_window = GE.getWindow();
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

void RenSys2::ImGUI_Prerender() const noexcept {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void RenSys2::ImGUI_renderOpenGlContext() const noexcept {
    //auto* frameB{m_framebuffer.get()};
    //glDrawPixels(m_w, m_h, GL_RGBA, GL_UNSIGNED_BYTE, frameB);
    //
    ////int display_w, display_h;
    ////glfwGetFramebufferSize(m_window, &display_w, &display_h);
    ////glViewport(0, 0, display_w, display_h);
    ////glClearColor(0.0, 0.0, 0.0, 0.0);
    ////glClear(GL_COLOR_BUFFER_BIT);
}

void RenSys2::ImGUI_RenderUI() {
    ImGui::Text("This is some useful text");
    //ImGui::Begin("Hola mundo");
    //ImGui::End();
}

void RenSys2::ImGUI_Postrender(GraphicEngine& GE) const noexcept {
    auto* m_window = GE.getWindow();
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);

}

void RenSys2::EndImgui(GraphicEngine& GE) {
    auto* m_window = GE.getWindow();
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if(m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}