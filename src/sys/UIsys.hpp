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
    RTexture zarpazo;
    RTexture inicio;
    RTexture muerte;
    RTexture controles;
    RTexture pausa;
    //RTexture sonido;
    
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
    void renderInterface(EntyMan& EM, GraphicEngine& GE, double dt);
    void hitInterface(GraphicEngine& GE);
    void renderInterfaceHits(GraphicEngine& GE ,double dt);

    //menus
    size_t menuIni(GraphicEngine& GE, size_t next);
    size_t menuMuerto (GraphicEngine& GE, size_t next);
    size_t menuControles (GraphicEngine& GE, size_t next);
    size_t menuPausa (GraphicEngine& GE, size_t next);
    size_t menuSonido (GraphicEngine& GE, size_t next);
    bool inGame{false};

    void iniText();

    
};