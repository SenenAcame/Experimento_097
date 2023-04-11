#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "RShader.hpp"
#include "RTexture.hpp"
#include "RMaterial.hpp"
#include "../utils/typeUsing.hpp"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    //position
    glm::vec3 Position;
    //normal
    glm::vec3 Normal;
    //texture coords
    glm::vec2 TexCoords;
    //tangent
    glm::vec3 Tangent;
    //bitangent
    glm::vec3 Bitangent;
    
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Mesh {

    Mesh();
    Mesh(std::vector<Vertex> vert, std::vector<unsigned int> index, RMaterial *mat, RShader *shader, RShader *shaderBorder);
    ~Mesh();
    void draw(Mat4 mat, bool border = false);

    //mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;

    RMaterial* material_    {nullptr};
    RShader* shader_        {nullptr};
    RShader* shaderBorder_  {nullptr};

    unsigned int VAO;
    unsigned int VBO, EBO;

    void setUpMesh();
};
#endif