#pragma once
#include "../util/types.hpp"
#include <cstddef>
////IMGUI
//#include <GL/gl.h>
//#include <imgui/src/imgui.h>
//#include <imgui/src/imgui_impl_glfw.h>
//#include <imgui/src/imgui_impl_opengl3.h>
//#include <stdio.h>
//#define GL_SILENCE_DEPRECATION
//#if defined(IMGUI_IMPL_OPENGL_ES2)
//#include <GLES2/gl2.h>
//#endif
//#include <GLFW/glfw3.h> // Will drag system OpenGL headers

struct TheEngine;
struct GraphicEngine;

struct RenSys2 {
    using Render  = MP::Typelist<RenderCmp2>;
    using SYSCMPs = MP::Typelist<PhysicsCmp2, RenderCmp2>;
    using BOXCMPs = MP::Typelist<PhysicsCmp2, EstadoCmp>;
    using SYSTAGs = MP::Typelist<>;

    static constexpr double PI { std::numbers::pi };

    /*VIEJO*/ void update  (EntyMan& EM, TheEngine& GFX);
    /*NUEVO*/ void update2 (EntyMan& EM, GraphicEngine& GE, std::size_t player_ID);

    void updateCamera(EntyMan& EM, GraphicEngine& GE, std::size_t player_ID);
    
    void drawAll (EntyMan& EM, TheEngine& GFX);
    void drawBBox(EntyMan& EM, TheEngine& GFX);

    void drawWorld(GraphicEngine& GE);

    //IMGUI
    //void ImGUI_renderOpenGlContext() const noexcept;
    //void ImGUI_Prerender() const noexcept;
    //void ImGUI_Postrender() const noexcept;
    //void initIMGUI();
    //void EndImgui();

//private:
    //GLFWwindow* m_window {nullptr};
    //unsigned int m_h{1080}, m_w{720};
    //std::unique_ptr<uint32_t[]> m_framebuffer;
};