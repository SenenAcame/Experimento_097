#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

struct RenderSystem {
    explicit RenderSystem() = default;
    explicit RenderSystem(uint32_t, uint32_t);
    ~RenderSystem();
    void update(EntyMan& EM, TheEngine& GFX);

private:
void ImGui_preRender() const noexcept;
void ImGui_postRender() const noexcept;
void ImGui_renderFrameBuffer() const noexcept;
void ImGui_renderUI(EntyMan& EM) const noexcept;
    unsigned int const m_h, m_w;
    GLFWwindow* m_window {nullptr};
    std::unique_ptr<uint32_t[]> m_framebuffer;
};