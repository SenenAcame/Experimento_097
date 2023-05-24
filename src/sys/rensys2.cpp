#include "rensys2.hpp"
//#include "../eng/engine.hpp"
#include "../eng/engine2.hpp"
#include "UIsys.hpp"
#include "soundsystem.hpp"
#include <cstddef>
#include <iostream>
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

/*NUEVO*/ void RenSys2::update2(EntyMan& EM, GraphicEngine& GE, UIsys& UISys, double dt) {
    ImGUI_Prerender();

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& ent, PhysicsCmp2& phy, RenderCmp2& rend) {
            rotateEnemy (ent, rend, phy); 
            rotateWeapon(ent, rend, phy);
            
            rend.node->setTranslation(Vec3 { phy.x, phy.y, phy.z });
            GE.drawScene();
        }
    );
    updateCamera(EM, GE);

    drawWorld(GE);
    UISys.renderInterface(EM, GE, dt); 
    
    //ImGUI_Postrender(GE);
}

void RenSys2::pantallaCarga(GraphicEngine& GE, UIsys& UISys, double progress){

    ImGUI_Prerender();
    UISys.pantallaCarga(GE,  progress);
    ImGUI_Postrender(GE);
}

size_t RenSys2::updateMenuInicio(GraphicEngine& GE, UIsys& UISys) {
    size_t abandon = 0;
    ImGUI_Prerender();
    abandon = UISys.menuIni(GE, abandon);
    ImGUI_Postrender(GE);
    return abandon;
}

size_t RenSys2::updateMenuDead(GraphicEngine& GE, UIsys& UISys) {
   size_t abandon = 2;
   ImGUI_Prerender();
   abandon = UISys.menuMuerto(GE, abandon);
   ImGUI_Postrender(GE);
   return abandon;
}

size_t RenSys2::updateMenuPausa(GraphicEngine& GE, UIsys& UISys, EntyMan& EM, SoundSystem_t& SouSys){
   size_t abandon = 3;
   ImGUI_Prerender();
   abandon = UISys.menuPausa(GE, abandon, EM, SouSys);
   ImGUI_Postrender(GE);
   return abandon;
}

size_t RenSys2::updateMenuControles(GraphicEngine& GE, UIsys& UISys) {
   size_t abandon = 4;
   ImGUI_Prerender();
   abandon = UISys.menuControles(GE, abandon);
   ImGUI_Postrender(GE);
   return abandon;
}

size_t RenSys2::updateMenuSonido(GraphicEngine& GE, UIsys& UISys, SoundSystem_t& Sou) {
    size_t abandon = 5;
    ImGUI_Prerender();
    abandon = UISys.menuSonido(GE, abandon, Sou);
    ImGUI_Postrender(GE);
    return abandon;
}

void RenSys2::updateCamera(EntyMan& EM, GraphicEngine& GE) {
    auto& player = EM.getEntityById(EM.getBoard().entyID);
    auto& ren    = EM.getComponent<RenderCmp2>(player);
    auto& phy    = EM.getComponent<PhysicsCmp2>(player);
    auto& inv    = EM.getComponent<InventarioCmp>(player);
    auto* cam = GE.getCamera();

    float pitch      = cam->Pitch;
    float yaw        = cam->Yaw;
    TwoAngles angles = walkAndReload(inv, phy.v_lin);

    float total_x = -yaw  + angles.alfa;
    float total_y = pitch + angles.beta;

    ren.node->setRotation(Vec3(0, total_x, total_y));
    cam->updateCameraVectors();

    phy.orienx = glm::radians(pitch);
    phy.orieny = glm::radians(yaw);
}

TwoAngles RenSys2::walkAndReload(InventarioCmp &inv, double speed) {
    if(inv.reloading == 1) {
        inv.ang_reload += inv.var_ang;
        //if(inv.ang_reload >= 10 || inv.ang_reload <= -10)
        //    inv.var_ang *= -1;
    }
    else inv.ang_reload = 0;

    if(speed != 0){
        inv.ang_walk_x += inv.var_x;
        inv.ang_walk_y += inv.var_y;
        if(inv.ang_walk_x >= 3 || inv.ang_walk_x <= -3)
            inv.var_x *= -1;
        if(inv.ang_walk_y >= 3 || inv.ang_walk_y <= -3)
            inv.var_y *= -1;
    }
    else {
        inv.ang_walk_x = 0;
        inv.ang_walk_y = 0;
    }
    
    return { inv.ang_walk_x, inv.ang_walk_y + inv.ang_reload };
}

void RenSys2::drawWorld(GraphicEngine &GE) {
    GE.beginScene();
    GE.drawAllScene();
    //GE.endScene();
}

void RenSys2::rotateWeapon(Enty& ent, RenderCmp2 &rend, PhysicsCmp2 &phy) {
    if(ent.hasTAG<TWeapon>() || ent.hasTAG<TPowerUp>()) {
        rend.node->rotate(Vec3 { 0, 1, 0 });

        phy.y += rend.elev;

        if(phy.y >= 3.5) rend.elev = -0.01;
        if(phy.y <= 2.5) rend.elev = 0.01;
    }
}

void RenSys2::rotateEnemy(Enty& ent, RenderCmp2 &rend, PhysicsCmp2 &phy) {
    if(ent.hasTAG<TEnemy>()) {
        auto rot = rend.node->getRotation();
        float giro_y = (-phy.orieny) * 180 / PI + 90;
        
        rend.node->setRotation(Vec3 { rot.x, giro_y, rot.z });
    }
}

//IMGUI
void RenSys2::initIMGUI(GraphicEngine& GE) {
    constexpr const char* glsl_version = "#version 130";
    auto* m_window = GE.getWindow();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImFont* pFont = io.Fonts->AddFontFromFileTTF("assets/Interface/Font/floyd.TTF", 60.0f);
    ImGuiStyle& style = ImGui::GetStyle();

    //Color negro
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.55f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 0.55f, 0.0f, 1.f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.55f, 0.0f, 1.f);
    style.Colors[ImGuiCol_Button] = ImVec4(0,0,0,0);
    //style.FramePadding = ImVec2(0.0f, 0.0f);
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

void RenSys2::ImGUI_RenderUI(EntyMan& EM, GraphicEngine& GE) const noexcept{
    //ImGui::Text("This is some useful text");
    auto* m_window = GE.getWindow();
    auto& player  = EM.getEntityById(EM.getBoard().entyID);
    auto& invent  = EM.getComponent<InventarioCmp>(player);
    auto stats      = EM.getComponent<EstadisticaCmp>(player);
    auto width  = GE.getWidth();
    auto height = GE.getHeight();
   
    int magazine = 0;
    int ammo = 0;
    double hp = stats.hitpoints/100;
    int wave = 0;
    int kills = 0;
    
    RTexture prueba("assets/Interface/1280x720/zarpazo.png");
    
    switch (invent.equipada) {
        case 0:
            magazine = invent.gun.magazine;
            ammo = invent.gun.ammo;
            break;
        case 1: 
            magazine = invent.shot.magazine;
            ammo = invent.shot.ammo;
            break;
        case 2: 
            magazine = invent.rifle.magazine;
            ammo = invent.rifle.ammo;
            break;
    }
    ImGui::SetNextWindowPos(ImVec2(10,10));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "UI", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)prueba.ID_, ImVec2(400, 350));
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(10,450));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UI2", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    
    ImGui::Text("Wave: %d", wave);
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(255,0,0,255));
    //ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0,0,0,0));
    ImGui::ProgressBar(hp,ImVec2(300,40), "");

    //ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(10,550));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UI3", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    //ImGui::Text("Wave: %d", wave);
    ImGui::Text("Kills: %d", kills);
    //ImGui::Text("HP: %d", hp);
    //ImGui::Text("%d/%d", magazine, ammo );
    
    ImGui::End();
    ImGui::SetNextWindowPos(ImVec2(870,550));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UI4", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    //ImGui::Text("Wave: %d", wave);
    //ImGui::Text("Kills: %d", kills);
    //ImGui::Text("HP: %d", hp);
    ImGui::Text("%d/%d", magazine, ammo );
    
    ImGui::End();    
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
    if(m_window) glfwDestroyWindow(m_window);
    glfwTerminate();
}