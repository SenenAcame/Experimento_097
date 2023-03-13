
#include "TNodo.hpp"
#include "shader.hpp"
#include "../assets/shaders/mesh.hpp"
#include "../assets/shaders/model.hpp"
#include <glm/gtc/matrix_transform.hpp>


// init by default a Node
TNodo::TNodo() noexcept {
    setTranslation({0.0f, 0.0f, 0.0f});
    setRotation({0.0f, 0.0f, 0.0f});
    setScale({1.0f, 1.0f, 1.0f});
}

// init a Node with the params
TNodo::TNodo(Vec3 trans, Vec3 rot, Vec3 scale) noexcept {
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
    translation_ = trans;
    updateMat_ = true;
}

void TNodo::rotate(Vec3 rot) {
    rotation_ = rot;
    updateMat_ = true;
}

void TNodo::scale(Vec3 scale) {
    scale_ = scale;
    updateMat_ = true;
}

void TNodo::run(Mat4 acumMat, bool fatherChange) {

    glDepthFunc(GL_LESS);
    bool actualChange = false;

    // Comprueba que no hemos cambiado la matriz acumulativa o un vector
    if(fatherChange || updateMat_) {
        matTransf_ = glm::translate(Mat4(1.0f), translation_);

        matTransf_ = glm::rotate(matTransf_, glm::radians(rotation_.y), {0, 1, 0});
        matTransf_ = glm::rotate(matTransf_, glm::radians(rotation_.z), {0, 0, 1});
        matTransf_ = glm::rotate(matTransf_, glm::radians(rotation_.x), {1, 0, 0});

        matTransf_ = glm::scale(matTransf_, scale_);

        matTransf_ = matTransf_ * acumMat;

        actualChange = true;
    }

    for(TNodo *son : nodeSons_) {
        son->run(matTransf_, actualChange);
    }
    if(entity_)
        // entity_.draw(matTransf_);

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
        //delete entity
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

void TNodo::setMesh(Mesh *sMesh) {
    mesh_ = sMesh;
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

void TNodo::setTexture(Texture *tex) {
    texture_ = tex;
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

Entity *TNodo::getEntity() noexcept {
    return entity_; 
}

TNodo *TNodo::getFather() noexcept { 
    return fatherNode_; 
};

TNodo::vecNodo *TNodo::getSons() noexcept {
    return &nodeSons_;
}