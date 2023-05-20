#pragma once
#include "../eng/resources/RAnimation.hpp"
#include "../eng/GLgEngine.hpp"

struct AnimMan {

    AnimMan(GlEngine& glEng) {
        initEnemy1Anim(glEng);
        initEnemy2Anim(glEng);
        initEnemy3Anim(glEng);
    }

    void initEnemy1Anim(GlEngine& glEng) {
        std::string file_model        = "assets/models/personajes/monstruo1/enemigo1.obj";
        std::vector<std::string> anim = {"monstruo1/caminar/monstruo1_caminar_"/*, "monstruo1/atacar/monstruo1_atacar", "monstruo1/morir/monstruo1_morir"*/};
        std::vector<int> framesAnim   = {108/*, 1, 1*/};
        glEng.createModel( NULL, Vec3(100000.f), Vec3(0.f), Vec3(1.0), file_model, false, false, true, anim, framesAnim)->remove(); //hay que eliminarlo
    }

    void initEnemy2Anim(GlEngine& glEng) {
        std::string file_model        = "assets/models/personajes/monstruo2/enemigo2.obj";
        std::vector<std::string> anim = {"monstruo2/caminar_2/monstruo2_caminar_"/*, "monstruo2/atacar/monstruo2_atacar", "monstruo2/morir/monstruo2_morir"*/};
        std::vector<int> framesAnim   = {162/*, 1, 1*/};
        glEng.createModel( NULL, Vec3(100000.f), Vec3(0.f), Vec3(1.0), file_model, false, false, true, anim, framesAnim)->remove(); //hay que eliminarlo
    }

    void initEnemy3Anim(GlEngine& glEng) {
        std::string file_model        = "assets/models/personajes/monstruo3/enemigo_3.obj";
        std::vector<std::string> anim = {"monstruo3/caminar/monstruo3_caminar_"/*, "monstruo3/atacar/monstruo3_atacar", "monstruo3/morir/monstruo3_morir"*/};
        std::vector<int> framesAnim   = {165/*, 1, 1*/};
        glEng.createModel( NULL, Vec3(100000.f), Vec3(0.f), Vec3(1.0), file_model, false, false, true, anim, framesAnim)->remove(); //hay que eliminarlo
    }
};