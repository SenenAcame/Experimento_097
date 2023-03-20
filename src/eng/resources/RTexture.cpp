#include "RTexture.hpp"


RTexture::RTexture(std::string path){
    texImage_ = path;
    loadTexture();
}

RTexture::RTexture(std::vector<std::string> faces) {
    cubemaps_ = faces;
    loadCubeMap();
}

RTexture::~RTexture(){
    texImage_ = "";
}

void RTexture::loadTexture(){

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int nrComponents;
    unsigned char *data = stbi_load(texImage_.c_str(), &width, &height, &nrComponents, 0);
    if(data){
        GLenum format;
        GLenum format2;
        format = format2 = GL_RED;

        if(nrComponents == 3){
            format = GL_RGB;
            format2 = GL_SRGB;
        } else if(nrComponents == 4){
            format = GL_RGBA;
            format2 = GL_SRGB_ALPHA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format2, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else{
        std::cout << "Texture failed to load" << texImage_ << std::endl;
        stbi_image_free(data);
    }
    ID_ = textureID;
}

void RTexture::loadCubeMap(){
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int nrChannels;
    for(unsigned int i = 0; i < cubemaps_.size(); i++){
        unsigned char *data = stbi_load(cubemaps_[i].c_str(), &width, &height, &nrChannels, 0);
        if(data){               
            GLenum format = GL_RED;
            if(nrChannels == 3){
            format = GL_RGB;
            } else if(nrChannels == 4){
                format = GL_RGBA;
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load to path: " << cubemaps_[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    ID_ = textureID;
}

std::string RTexture::getTexImage(){
    return texImage_;
}