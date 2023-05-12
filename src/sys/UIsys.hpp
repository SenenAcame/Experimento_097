#pragma once
#include "../util/types.hpp"
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

struct GraphicEngine;

struct UIsys {
    
    using SYSCMPs      = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs      = MP::Typelist<>;

    //hits
    int activateHit {0};
    bool hit1{false}, hit2{false}, hit3{false};
    double cd {1};
    double clockHit1 {}, clockHit2 {}, clockHit3 {};

    //weapons
    int equipada{0};

    void renderInterface(EntyMan& EM, GraphicEngine& GE, std::size_t player_ID, double dt);
    void hitInterface(GraphicEngine& GE, Enty& player);
    void renderInterfaceHits(GraphicEngine& GE ,double dt);
    
};