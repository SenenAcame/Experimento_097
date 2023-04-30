#include "engine2.hpp"
#include "../man/levelman.hpp"

TNodo* GraphicEngine::createNode(std::string file) {
    TNodo* node = loadModel(file);
    //loadTexture(node, texture);
    return node;
}

TNodo* GraphicEngine::loadModel(std::string file) {
    return glEng.createModel(
        NULL,
        Vec3(1,0,0),
        Vec3(0.f),
        Vec3(1.f),
        file
    );
}

//void GraphicEngine::loadTexture(TNodo* node, std::string text) {
//    RTexture* texture = glEng.getRG()->getResource<RTexture>(text);
//    node->setTexture(texture);
//}