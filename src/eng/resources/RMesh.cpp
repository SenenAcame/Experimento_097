#include "RMesh.hpp"

#include <assimp/material.h>
#include <iostream>
#include "../resource_gestor.hpp"
#include "RMaterial.hpp"

// ____CONSTRUCTORES____________
//______________________________

RMesh::RMesh() {

}

RMesh::RMesh(std::string name) {
    name_ = name;
}

RMesh::~RMesh(){

}

// ______FUNCTIONS______________
//______________________________

void RMesh::draw(Mat4 mat, bool border) {
    
    for(auto i = 0; i < meshes_.size(); i++){
        meshes_.at(i).draw(mat, border);
    }
}

unsigned int RMesh::findAdjacentIndex(aiMesh *mesh, const unsigned int index1, const unsigned int index2, const unsigned int index3) {

    for(unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        unsigned int *&indices = mesh->mFaces[i].mIndices;

        for(unsigned int j = 0; j < 3; ++j) {

            unsigned int v1 = indices[j];
            unsigned int v2 = indices[(j + 1) % 3];
            unsigned int vOpp = indices[(j + 2) % 3];

            if(((v1 == index1 && v2 == index2) || (v2 == index1 && v1 == index2)) && vOpp != index3)
                return vOpp;
        }
    }
    return index3;
}

void RMesh::processMesh(aiMesh *mesh, const aiScene *scene, bool sky, ResourceGestor &rg) {

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    //walk though each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {

        Vertex vertex;
        Vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;


        if(vector.x > maxVec.x)
            maxVec.x = vector.x;
        if(vector.y > maxVec.y)
            maxVec.y = vector.y;
        if(vector.z > maxVec.z)
            maxVec.z = vector.z;
        
        if(vector.x > minVec.x)
            minVec.x = vector.x;
        if(vector.y > minVec.y)
            minVec.y = vector.y;
        if(vector.z > minVec.z)
            minVec.z = vector.z;

        vertex.Position = vector;

        //normals
        if(mesh->HasNormals()) {

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        //tex coords
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;

            //tangent
            if(mesh->mTangents!=nullptr){
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
            }
            
            //bitangent
            if(mesh->mBitangents != nullptr){
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        //retreive all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //process materials
    auto cont = scene->mMaterials;
    std::cout << scene->mMaterials[0]->GetName().C_Str() << std::endl;
    auto ind = mesh->mMaterialIndex;
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    //aiMaterial *material = cont[ind];
    std::string matName = name_ + material->GetName().C_Str();
    std::cout << matName << std::endl;
    //RMaterial *rMat = rg.getResource<RMaterial>("assets/models/personajes/monstruo2.mtl");
    RMaterial *rMat = rg.getResource<RMaterial>(matName);

    if(!rMat->isLoaded())
        rMat->loadMaterial(material, rg);

    RShader *shader = rg.getResource<RShader>("SHADER_COLOR");
    RShader *shaderborder = rg.getResource<RShader>("SHADER_LINE");

    // add the mesh to the vector
    meshes_.emplace_back(vertices, indices, rMat, shader, shaderborder);    
}