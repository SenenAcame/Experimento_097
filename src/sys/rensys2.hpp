#pragma once
#include "../util/types.hpp"
#include <cstddef>

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
    
    /*VIEJO*/ void drawAll (EntyMan& EM, TheEngine& GFX);
    /*VIEJO*/ void drawBBox(EntyMan& EM, TheEngine& GFX);

    void drawWorld(GraphicEngine& GE);

    //IMGUI
    void initIMGUI(GraphicEngine& GE);
    void ImGUI_Prerender() const noexcept;
    void ImGUI_RenderUI(EntyMan& EM, GraphicEngine& GE, std::size_t player_ID) const noexcept;
    void ImGUI_renderOpenGlContext() const noexcept;
    void ImGUI_Postrender(GraphicEngine& GE) const noexcept;
    void EndImgui(GraphicEngine& GE);

//private:
    //GLFWwindow* m_window {nullptr};
    //unsigned int m_h{1080}, m_w{720};
    //std::unique_ptr<uint32_t[]> m_framebuffer;
};