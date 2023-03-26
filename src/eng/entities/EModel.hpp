#pragma once

#include <assimp/anim.h>
#include <assimp/scene.h>
#include <cstddef>
#include <glm/glm.hpp>
#include "Entity.hpp"
#include "../resources/RMesh.hpp"
//#include "../resources/RAnimation.hpp"
#include <string>
#include <vector>

struct RTexture;
struct ResourceGestor;

struct EModel : public Entity {

    EModel();
    EModel(std::string, ResourceGestor &, bool skybox = false);
    ~EModel();
    
    void draw(Mat4, bool);
    void init();

    void loadModel(std::string, ResourceGestor &);
    //void loadAnimation(std::vector<std::string>, ResourceGestor &, std::vector<int> totalFrames = {0});
    void processNode(aiNode *, const aiScene *, ResourceGestor &);

    RMesh *getRMesh();
    RMesh *getMesh() { return mesh_; }

    void setMesh(RMesh *messi) { mesh_ = messi; }
    //void setAnimation(RAnimation *ranni) { animation_ = ranni; }

    void setTexture (RTexture *textura);

    //int currentAnim = -1;
    bool skybox_{false};
    RMesh *mesh_{nullptr};
    //RAnimation animation_{nullptr};

    float transparency_ {1.0f};
};