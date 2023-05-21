#pragma once
#include "../eng/resources/RAnimation.hpp"
#include "../eng/engine2.hpp"

struct AnimMan {

    AnimMan(GraphicEngine& GE) {
        //initEnemy1Anim(GE);
        //initEnemy2Anim(GE);
        //initEnemy3Anim(GE);
    }

    void initEnemy1Anim(GraphicEngine& GE) {
        std::string file_model        = "assets/models/personajes/monstruo1/enemigo1.obj";
        std::vector<std::string> anim = { "monstruo1/caminar/monstruo1_caminar_" };
        std::vector<int> framesAnim   = { 108 };
        GE.createNodeAnim(file_model, anim, framesAnim)->remove(); //hay que eliminarlo
    }

    void initEnemy2Anim(GraphicEngine& GE) {
        std::string file_model        = "assets/models/personajes/monstruo2/enemigo2.obj";
        std::vector<std::string> anim = { "monstruo2/caminar/monstruo2_caminar_" };
        std::vector<int> framesAnim   = { 162 };
        GE.createNodeAnim(file_model, anim, framesAnim)->remove(); //hay que eliminarlo
    }

    void initEnemy3Anim(GraphicEngine& GE) {
        std::string file_model        = "assets/models/personajes/monstruo3/enemigo_3.obj";
        std::vector<std::string> anim = { "monstruo3/caminar/monstruo3_caminar_" };
        std::vector<int> framesAnim   = { 165 };
        GE.createNodeAnim(file_model, anim, framesAnim)->remove(); //hay que eliminarlo
    }
};