#pragma once
#include "../util/types.hpp"
#include "../eng/engine.hpp"


//static void glfw_error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}

//create windowm with IMGUI
//void createWindow(){
//
//    glfwSetErrorCallback([](auto error, auto description){
//        std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//        throw std::runtime_error("GLFW ERROR");
//    });
//    if (!glfwInit())
//        throw std::runtime_error("ERROR GLFW INITIALIZATION");
//}


struct RenSys2 {
    using SYSCMPs = MP::Typelist<PhysicsCmp2, RenderCmp2>;
    using SYSTAGs = MP::Typelist<>;

    void update(EntyMan& EM, TheEngine& GFX) {
        EM.foreach<SYSCMPs, SYSTAGs>(
            [&](Enty& e, PhysicsCmp2 const& p, RenderCmp2& r){
                r.n->setPosition({static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z)});
            }
        );
        drawAll(GFX);
    };

    void drawAll(TheEngine& GFX) {
        GFX.beginScene();
        GFX.drawAll();
        GFX.endScene();
    }
};