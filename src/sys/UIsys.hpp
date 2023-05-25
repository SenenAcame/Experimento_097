#pragma once
#include "../util/types.hpp"
#include "../eng/engine2.hpp"
#include "soundsystem.hpp"
#include <cstddef>
#include <iterator>
#include "../eng/GLgEngine.hpp"

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
struct GLFWwindow;

struct UIsys {
    
    using SYSCMPs      = MP::Typelist<PhysicsCmp2>;
    using SYSTAGs      = MP::Typelist<>;
    using SoundCMPs    = MP::Typelist<SoundCmp>;
    using MAPTAGs      = MP::Typelist<TMap>;

    //hits
    RTexture zarpazo;
    RTexture zarpazo1;
    RTexture golpe;


    //Pantallas
    RTexture cargando;
    RTexture inicio;
    RTexture muerte;
    RTexture controles;
    RTexture pausa;
   
    //RTexture sonido;

    //Icons
    RTexture iconoEscopeta;
    RTexture iconoPistola;
    RTexture iconoSubfusil;
    RTexture iconoRonda;
    RTexture iconoBajas;
    RTexture iconoMira;
    RTexture iconoVida;
    RTexture iconoPower;
    RTexture iconoSpeed;
    
    int activateHit {0};
    bool hit1{false}, hit2{false}, hit3{false}, redHit{false};
    double cd {2}, cdG{0.5};
    double clockHit1 {}, clockHit2 {}, clockHit3 {}, clockGolpe{};
    int randWidth1 {}, randWidth2 {}, randWidth3 {};
    int randHeight1{}, randHeight2{}, randHeight3{};
    bool jugar{false};

    //weapons
    int equipada{0};

    //Sound
    float SoundMaster = 1;
    float SoundAmbient = 1;
    float SoundMusic = 1;
    float SoundSFX = 1;
    float SoundVoices = 1;
    bool iChangeMaster = false;

    //UI game
    void renderInterface(EntyMan& EM, GraphicEngine& GE, double dt);
    void hitInterface(GraphicEngine& GE);
    void renderInterfaceHits(GraphicEngine& GE ,double dt);

    float moveX = 0;
    float moveY = 0;

    //menus
    size_t menuIni(GraphicEngine& GE, size_t next);
    size_t menuMuerto (GraphicEngine& GE, size_t next);
    size_t menuControles (GraphicEngine& GE, size_t next);
    size_t menuPausa (GraphicEngine& GE, size_t next, EntyMan& EM, SoundSystem_t& Sou);
    size_t menuSonido (GraphicEngine& GE, size_t next, SoundSystem_t& Sou);
    bool pantallaCompleta = false;
    size_t resolution = 1;
    void pantallaCarga(GraphicEngine& GE, double progress);
    bool inGame{false};
    bool pause{false};



    void iniText(GraphicEngine& GE);

    
};