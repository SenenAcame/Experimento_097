#pragma once

#include "../utils/typeUsing.hpp"
#include "Resource.hpp"
#include "RTexture.hpp"
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct ResourceGestor;

struct RMaterial : public Resource {

    RMaterial();
    RMaterial(std::string );
    RMaterial(Vec3 ka, Vec4 kd, Vec3 ks, float ns, float d, bool tex = false);
    ~RMaterial();
    void loadMaterial(aiMaterial *, ResourceGestor &rg);
    std::vector<RTexture *> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, ResourceGestor &rg);

    bool hasTexture();

    void setAll(Vec3 , Vec4 , Vec3 , float , float , bool tex = false);

    constexpr inline static  uint8_t id_{0};

    bool texture_{false};
    Vec3 Kambient_, Kspecular_;
    Vec4 Kdiffuse_;
    float Ns_, d_;
    std::vector<RTexture *> textures_;
};