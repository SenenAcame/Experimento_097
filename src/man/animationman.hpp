#include "../eng/resources/RAnimation.hpp"
#include "../eng/GLgEngine.hpp"

struct AnimMan {

    AnimMan(GlEngine& glEng) {
        initEnemy1Anim(glEng);
        initEnemy2Anim(glEng);
        initEnemy3Anim(glEng);
    }

    void initEnemy1Anim(GlEngine& glEng) {

    }

    void initEnemy2Anim(GlEngine& glEng) {
        std::string file_model = "assets/models/personajes/monstruo2/enemigo2.obj";
        std::vector<std::string> anim = {"monstruo2/caminar/monstruo2_caminar", "monstruo2/atacar/monstruo2_atacar", "monstruo2/morir/monstruo2_morir"};
        std::vector<int> framesAnim = {111,1, 1};
        glEng.createModel( NULL, Vec3(100000.f), Vec3(0.f), Vec3(1.0), file_model, false, false, true, anim, framesAnim); //hay que eliminarlo
    }

    void initEnemy3Anim(GlEngine& glEng) {

    }
};