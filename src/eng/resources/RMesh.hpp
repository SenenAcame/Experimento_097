#pragma once

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Resource.hpp"
#include "mesh.hpp"
#include <vector>

struct ResourceGestor;

struct RMesh : public Resource{
    RMesh();
    RMesh(std::string name);
    ~RMesh();

    void processMesh(aiMesh *mesh, const aiScene *scene, bool sky, ResourceGestor &rg);
    std::vector<RTexture *> loadMaterialTextures(aiMaterial *, aiTextureType , std::string , ResourceGestor &);

    unsigned int findAdjacentIndex(aiMesh *mesh, const unsigned int index1, const unsigned int index2, const unsigned int index3);

    void draw(Mat4 mat, bool border = false);

    constexpr inline static uint8_t id_{1};

    Vec3 maxVec {0.0f, 0.0f, 0.0f};
    Vec3 minVec {0.0f, 0.0f, 0.0f};
    std::vector<Mesh> meshes_;
};