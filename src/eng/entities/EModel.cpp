#include "EModel.hpp"

#include "../resource_gestor.hpp"
#include <assimp/Importer.hpp>
#include <assimp/anim.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

EModel::EModel(std::string name, ResourceGestor &rg, bool sky) {

    skybox_ = sky;
    loadModel(name, rg);
}

EModel::EModel() {

}

EModel::~EModel() {

}

void EModel::init() {
    
    skybox_ = false;
    animation_ = nullptr;
    currentAnim = 0;
    mesh_ = nullptr;
    transparency_ = 1.f;
}

void EModel::draw(Mat4 mat, bool border) {

    if(mesh_ == nullptr)
        std::cout << "null el de la clase RMesh" << std::endl;
    
    if(mesh_->meshes_.size() == 0)
        std::cout << "null el vector de Meshes" << std::endl;
    
    mesh_->meshes_[0].shader_->use();
    mesh_->meshes_[0].shader_->setFloat("material.transparecy", transparency_);
    if(animation_ != nullptr && currentAnim >= 0) {
        std::cout << "Entro en animacion\n";
        animation_->draw(mat, &currentAnim);
    }
    else {
        mesh_->draw(mat);
        std::cout << "Entro en modelo\n";
    }
}

void EModel::loadModel(std::string path, ResourceGestor &rg) {

    //variable de entity
    unused_ = false;

    mesh_ = rg.getResource<RMesh>(path);
    if(mesh_->isLoaded())
        return;

    //read file with Assimp
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    //check if ok
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    // process all nodes starting with the FatherNode
    processNode(scene->mRootNode, scene, rg);

    mesh_->load();
}

void EModel::processNode(aiNode *node, const aiScene *scene, ResourceGestor &rg) {
    // process all meshes of the node and sons
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        mesh_->processMesh(mesh, scene, skybox_, rg);
    }

    //all sons now
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, rg);
    }
}

RMesh *EModel::getRMesh() {
    return mesh_;
}

void EModel::loadAnimation(std::vector<std::string> animations, ResourceGestor &rg, std::vector<int> totalFrames) {
    int nSize = animations[0].size();
    auto minSize = nSize - animations[0].find('/') + 1;
    std::string splitted = animations[0].substr(animations[0].find('/') + 1, minSize);
    auto *anim = rg.getResource<RAnimation>(splitted);
    animation_ = anim;

    if(!anim->isLoaded()) {
        for(int y = 0; y < animations.size(); y++) {
            std::vector<RMesh> animation;
            int i = 1;
            while(i < totalFrames[y]) {
                                    //cambiar paths
                std::string route = "assets/animations" + animations[y] + std::to_string(i) + ".obj";
                mesh_ = rg.getResource<RMesh>(animations[y] + std::to_string(i));

                Assimp::Importer importer;
                const aiScene *scene = importer.ReadFile(route, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

                if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
                    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
                } else{
                    processNode(scene->mRootNode, scene, rg);
                    
                    animation.push_back(*mesh_);
                    i++;
                }
            }
            animation_->addAnimation(animation);
        }
        animation_->load();
    }
}

