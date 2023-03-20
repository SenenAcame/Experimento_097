#define GL_GLEXT_PROTOTYPES

#include "mesh.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vertex> vert, std::vector<unsigned int> index, RMaterial *mat, RShader *shader, RShader *shaderBorder) {
   
    vertices = vert;
    indices = index;
    material_ = mat;
    shader_ = shader;
    shaderBorder_ = shaderBorder;
    setUpMesh();
}

Mesh::~Mesh(){

}

void Mesh::draw(Mat4 mat, bool border) {
    if(border) {
        shaderBorder_->use();
        shaderBorder_->setMat4("model", mat);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    else {
        shader_->use();
        shader_->setMat4("model", mat);

        unsigned int illum = glGetSubroutineUniformLocation(shader_->ID, GL_FRAGMENT_SHADER, "diffuseVar");
        unsigned int subroutine = glGetSubroutineIndex(shader_->ID, GL_FRAGMENT_SHADER, "colorDiff");

        if(material_->hasTexture()) {
            subroutine = glGetSubroutineIndex(shader_->ID, GL_FRAGMENT_SHADER, "textureDiff");

            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;
            for(unsigned int i = 0; i < material_->textures_.size(); i++) {

                glActiveTexture(GL_TEXTURE0 + i); //active texture before binding
                //retrieve texture number
                std::string number;
                std::string name = material_->textures_[i]->type_;
                if(name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if(name == "texture_specular")
                    number = std::to_string(specularNr++);
                else if(name == "texture_normal")
                    number = std::to_string(normalNr++);
                else if(name == "texture_height")
                    number = std::to_string(heightNr++);

                shader_->setInt("material.diffuseSampler", 0);
                shader_->setVec3("material.specular", material_->Kspecular_);
                shader_->setFloat("material.shininess", material_->Ns_);

                //set the sampler to the correct texture unit
                glUniform1i(glGetUniformLocation(shader_->ID, (name + number).c_str()), i);
                //and bind the texture
                glBindTexture(GL_TEXTURE_2D, material_->textures_[i]->id_);
            }
        }
        else {
            shader_->setVec4("material.diffuse", material_->Kdiffuse_);
            shader_->setVec3("material.specular", material_->Kspecular_);
            shader_->setFloat("material.shininess", material_->Ns_);
        }

        unsigned int indicesSub[1];
        indicesSub[illum] = subroutine;
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, indicesSub);

        //draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    
    }
}

void Mesh::setUpMesh() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    //vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    //vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    //vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    //ids
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
    //weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

    glBindVertexArray(0);
}