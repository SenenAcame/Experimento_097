#include "EModel.hpp"

#include "../resource_gestor.hpp"
#include <assimp/Importer.hpp>
#include <assimp/anim.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

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
    mesh_ = nullptr;
    transparency_ = 1.f;
}

void EModel::draw(Mat4 mat, bool border) {

    mesh_->meshes_[0].shader_->use();
    mesh_->meshes_[0].shader_->setFloat("material.transparecy", transparency_);

    mesh_->draw(mat);
}

void EModel::loadModel(std::string path, ResourceGestor &rg) {

    //variable de entity
    //unused_ = false;

    mesh_ = rg.getResource<RMesh>(path);
    if(mesh_->isLoaded())
        return;

    //read file with Assimp
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
     aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
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
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        processNode(node->mChildren[i], scene, rg);
    }
}

RMesh *EModel::getRMesh() {
    return mesh_;
}