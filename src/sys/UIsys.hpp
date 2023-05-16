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
    double cd {2};
    double clockHit1 {}, clockHit2 {}, clockHit3 {};
    int randWidth1 {}, randWidth2 {}, randWidth3 {};
    int randHeight1{}, randHeight2{}, randHeight3{};
    bool jugar{false};

    //weapons
    int equipada{0};

    //UI game
    void renderInterface(EntyMan& EM, GraphicEngine& GE, std::size_t player_ID, double dt);
    void hitInterface(GraphicEngine& GE);
    void renderInterfaceHits(GraphicEngine& GE ,double dt);

    //menus
    bool menuIni(GraphicEngine& GE, bool next);
    bool menuMuerto (GraphicEngine& GE, bool next);
    void menuControles (GraphicEngine& GE);
    bool menuPausa (GraphicEngine& GE, bool next);

    
};