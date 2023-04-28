
#include "TNodo.hpp"
#include "resources/RShader.hpp"
#include "resources/RMesh.hpp"
#include "entities/Entity.hpp"
#include "entities/EModel.hpp"
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>


// init by default a Node
TNodo::TNodo() {
    setTranslation({0.0f, 0.0f, 0.0f});
    setRotation({0.0f, 0.0f, 0.0f});
    setScale({1.0f, 1.0f, 1.0f});
}

// init a Node with the params
TNodo::TNodo(Vec3 trans, Vec3 rot, Vec3 scale) {
    translation_ = trans;
    rotation_ = rot;
    scale_ = scale;
    updateMat_ = true;
}

//  init node by defaults
void TNodo::initTNode() {
    entity_ = nullptr;

    matTransf_ = Mat4{1.0f};

    nodeSons_.clear();
    fatherNode_ = nullptr;

    updateMat_ = true;

    setTranslation({0.0f, 0.0f, 0.0f});
    setRotation({0.0f, 0.0f, 0.0f});
    setScale({1.0f, 1.0f, 1.0f});
}

//añade un hijo -> devuelve un int ">0" si lo hace, "0" si no 
int TNodo::addSon(TNodo *hijo) noexcept {
    if(hijo){
        this->nodeSons_.push_back(hijo);
        return 1;
    }
    return 0;
}

//borra un hijo -> devuelve un int ">0" si lo hace, "0" si no 
int TNodo::deleteSon(TNodo *hijo) noexcept {
    if(hijo){
        auto it = nodeSons_.begin();
        while(it != nodeSons_.end()){
            if(*it == hijo){
                nodeSons_.erase(it);
                return 1;
            }
            it++;
        }
    }
    return 0;
}

void TNodo::translade(Vec3 trans) {
    translation_ += trans;
    updateMat_ = true;
}

void TNodo::rotate(Vec3 rot) {
    rotation_ += rot;
    updateMat_ = true;
}

void TNodo::scale(Vec3 scale) {
    scale_ += scale;
    updateMat_ = true;
}

void TNodo::run(Mat4 acumMat, bool fatherChange, bool border) {

    glDepthFunc(GL_LESS);

    if(UI_)
        glDepthFunc(GL_ALWAYS);

    if(!border) {
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
    }
    if(floor_) {
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
    }

    bool actualChange = false;

    // Comprueba que no hemos cambiado la matriz acumulativa o un vector
    if(fatherChange || updateMat_) {
        if(fatherNode_!=nullptr){
            std::cout << "Matriz Acumulada :\n";
            std::cout << acumMat[0][0] << ", " << acumMat[0][1] << ", " << acumMat[0][2] << ", " << acumMat[0][3] << ", " << std::endl;
            std::cout << acumMat[1][0] << ", " << acumMat[1][1] << ", " << acumMat[1][2] << ", " << acumMat[1][3] << ", " << std::endl;
            std::cout << acumMat[2][0] << ", " << acumMat[2][1] << ", " << acumMat[2][2] << ", " << acumMat[2][3] << ", " << std::endl;
            std::cout << acumMat[3][0] << ", " << acumMat[3][1] << ", " << acumMat[3][2] << ", " << acumMat[3][3] << ", " << std::endl;
            std::cout << "______________________________________________\n";
        }
        matTransf_ = glm::translate(Mat4(1.f), translation_);

        matTransf_ = glm::rotate(matTransf_, glm::radians(rotation_.y), {0, 1, 0});
        matTransf_ = glm::rotate(matTransf_, glm::radians(rotation_.z), {0, 0, 1});
        matTransf_ = glm::rotate(matTransf_, glm::radians(rotation_.x), {1, 0, 0});

        matTransf_ = glm::scale(matTransf_, scale_);

        matTransf_ = matTransf_ * acumMat;

        std::cout << "Matriz Transformada :\n";
            std::cout << matTransf_[0][0] << ", " << matTransf_[0][1] << ", " << matTransf_[0][2] << ", " << matTransf_[0][3] << ", " << std::endl;
            std::cout << matTransf_[1][0] << ", " << matTransf_[1][1] << ", " << matTransf_[1][2] << ", " << matTransf_[1][3] << ", " << std::endl;
            std::cout << matTransf_[2][0] << ", " << matTransf_[2][1] << ", " << matTransf_[2][2] << ", " << matTransf_[2][3] << ", " << std::endl;
            std::cout << matTransf_[3][0] << ", " << matTransf_[3][1] << ", " << matTransf_[3][2] << ", " << matTransf_[3][3] << ", " << std::endl;
            std::cout << "______________________________________________\n";
        actualChange = true;
        setTranslation(matTransf_[3]);
    }

    if(border && floor_) {
        Mat4 matTmp = glm::translate(Mat4(1.0f), translation_);

        matTmp = glm::rotate(matTmp, glm::radians(rotation_.y), {0, 1, 0});
        matTmp = glm::rotate(matTmp, glm::radians(rotation_.z), {0, 0, 1});
        matTmp = glm::rotate(matTmp, glm::radians(rotation_.x), {1, 0, 0});

        matTmp = glm::scale(matTmp, scale_ + (scale_ * 0.025f));

        matTmp = matTmp * acumMat;

        for(TNodo *son : nodeSons_) 
            son->run(matTmp, actualChange, border);
        
        if(entity_){
            entity_->draw(matTmp, border);
        }
    } else if (!border) {
        for(TNodo *son : nodeSons_) {
            son->run(matTransf_, actualChange, border);
        }
        if(entity_)
            entity_->draw(matTransf_, border);
    }

    updateMat_ = false;
}
//delete node
void TNodo::remove() {

    if(fatherNode_){
        for(unsigned int i = 0; i < nodeSons_.size(); ++i){
            nodeSons_[i]->setFatherNode(fatherNode_);
        }

        for(unsigned int i = 0; i < fatherNode_->getSons()->size(); ++i) {
            if(fatherNode_->getSons()->at(i) == this){
                fatherNode_->getSons()->erase(fatherNode_->getSons()->begin() + i);
                break;
            }
        }
    }
    if(entity_){
        entity_->unused_ = true;
    
    initTNode();
    }

    //set to default
    initTNode();
}

void TNodo::setTranslation(Vec3 trans) { 
    translation_ = trans; 
    updateMat_ = true;
}

void TNodo::setRotation(Vec3 rot) { 
    rotation_ = rot; 
    updateMat_ = true;
}

void TNodo::setScale(Vec3 scale) { 
    scale_ = scale;
    updateMat_ = true; 
}

void TNodo::setMesh(RMesh *sMesh) {
    ((EModel *)entity_)->setMesh(sMesh);
}

void TNodo::setEntity(Entity *nEnt) {
    entity_ = nEnt; 
}

void TNodo::setFatherNode(TNodo *nFather) {
    fatherNode_ = nFather;
}

void TNodo::setMatrizTransf(Mat4 transf) { 
    matTransf_ = transf;  
}

void TNodo::setTexture(RTexture *tex) {
    ((EModel *)entity_)->setTexture(tex);
}

void TNodo::setAnimation(RAnimation *ranni) {
    ((EModel *)entity_)->setAnimation(ranni);
}
//-----------------------------------
//-----------  GETTERS  -------------
//-----------------------------------


Vec3 TNodo::getTranslation() const noexcept { 
    return translation_; 
}

Vec3 TNodo::getRotation() const noexcept { 
    return rotation_; 
}
Vec3 TNodo::getScale() const noexcept { 
    return scale_; 
}

Mat4 TNodo::getMatrizTransf() noexcept { 
    return matTransf_; 
}

TNodo *TNodo::getFather() const noexcept { 
    return fatherNode_; 
};

TNodo::vecNodo *TNodo::getSons() noexcept {
    return &nodeSons_;
}