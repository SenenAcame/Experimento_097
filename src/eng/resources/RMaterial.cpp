#include "RMaterial.hpp"
#include "../resource_gestor.hpp"

RMaterial::RMaterial() {
    Ns_ = 500;
    d_ = 1;
    Kambient_ = Kspecular_ = {0.8f, 0.8f, 0.8f};
    Kdiffuse_ = {0.8f, 0.8f, 0.8f, 1.0f};
}

RMaterial::RMaterial(std::string name) {
    name_ = name;
    Ns_ = 500;
    d_ = 1;
    Kambient_ = Kspecular_ = {0.8f, 0.8f, 0.8f};
    Kdiffuse_ = {0.8f, 0.8f, 0.8f, 1.0f};
}

RMaterial::RMaterial(Vec3 ka, Vec4 kd, Vec3 ks, float ns, float d, bool tex) {

    setAll(ka, kd, ks, ns, d, tex);
}

RMaterial::~RMaterial(){

}

void RMaterial::loadMaterial(aiMaterial *mtl, ResourceGestor &rg) {

    if(mtl->GetTextureCount(aiTextureType_DIFFUSE) == 0 && mtl->GetTextureCount(aiTextureType_HEIGHT) == 0) {
        aiColor4D diffuse;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            Kdiffuse_ = {diffuse.r, diffuse.g, diffuse.b, diffuse.a};
    }
    else {
        texture_ = true;

        //1. diffuse maps
        std::vector<RTexture *> diffuseMaps = loadMaterialTextures(mtl, aiTextureType_DIFFUSE, "texture_diffuse", rg);
        textures_.insert(textures_.end(), diffuseMaps.begin(), diffuseMaps.end());

        //2. specular maps
        std::vector<RTexture *> specularMaps = loadMaterialTextures(mtl, aiTextureType_SPECULAR, "texture_specular", rg);
        textures_.insert(textures_.end(), specularMaps.begin(), specularMaps.end());

        //3. normal maps
        std::vector<RTexture *> normalMaps = loadMaterialTextures(mtl, aiTextureType_HEIGHT, "texture_normal", rg);
        textures_.insert(textures_.end(), normalMaps.begin(), normalMaps.end());

        //4. height maps
        std::vector<RTexture *> heightMaps = loadMaterialTextures(mtl, aiTextureType_AMBIENT, "texture_height", rg);
        textures_.insert(textures_.end(), heightMaps.begin(), heightMaps.end());
    }

    aiColor4D ambient;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
        Kambient_ = {ambient.r, ambient.g, ambient.b};
    
    aiColor4D especular;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &especular))
        Kspecular_ = {especular.r, especular.g, especular.b};

    aiGetMaterialFloat(mtl, AI_MATKEY_OPACITY, &d_);
    aiGetMaterialFloat(mtl, AI_MATKEY_SHININESS, &Ns_);
    load();
}

std::vector<RTexture *> RMaterial::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, ResourceGestor &rg) {

    std::vector<RTexture *> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::string name = (str.C_Str());

        auto nSize = name.size();
        auto minSize = nSize - name.find_last_of('\\') -1;

        if(nSize != minSize)
            name = name.substr(name.find_last_of('\\') +1, minSize);

        name = "assets/textures/" + name;
        RTexture *tmptex = rg.getResource<RTexture>(name);

        if(tmptex->isLoaded()) {
            bool alreadyLoaded = false;
            for(unsigned int j = 0; j<textures.size(); j++) {
                if(strcmp(tmptex->getName().c_str(), textures[j]->getName().c_str()) == 0) {
                    alreadyLoaded = true;
                    break;
                }
            }
            if(!alreadyLoaded) {
                textures.push_back(tmptex);
            }
            continue;
        }
        tmptex->type_= typeName;
        tmptex->load();
        textures.push_back(tmptex);
    }

    return textures;
}

// ________Setters___________

void RMaterial::setAll(Vec3 ka, Vec4 kd, Vec3 ks, float ns, float d, bool tex) {
    Ns_ = ns;
    d_ = d;
    Kambient_ = ka;
    Kdiffuse_ = kd;
    Kspecular_ = ks;
    texture_ = tex;
}

// ________Getters__________

bool RMaterial::hasTexture() {
    return texture_;
}