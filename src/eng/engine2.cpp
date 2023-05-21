#include "engine2.hpp"
#include "../man/levelman.hpp"
#include "GLgEngine.hpp"
#include "resources/RShader.hpp"
#include "utils/typeUsing.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>

TNodo* GraphicEngine::createNode(std::string file, Vec3 sca, Vec3 rot, Vec3 tras) {
    return glEng.createModel( NULL, tras, rot, sca, file);
}

TNodo* GraphicEngine::createNodeAnim(std::string file, std::vector<std::string> anim, std::vector<int> framesAnim, Vec3 sca, Vec3 rot, Vec3 tras) {
    return glEng.createModel( NULL, tras, rot, sca, file, false, false, true, anim, framesAnim);
}

TNodo* GraphicEngine::createPlayer(Vec3 sca, Vec3 rot, Vec3 tras) {
    return glEng.createCamera(NULL, tras, rot, sca);
}

void GraphicEngine::createPlayerModel(std::string file_model) {
    auto* n_cam = getNodeCamera();
    playerModel = glEng.createModel(n_cam, Vec3{ 0.15, -0.12, 0.05 }, Vec3{ 0 }, Vec3{ 1 }, file_model);
}

void GraphicEngine::setCameraPlayer(std::string file_model) {
    createPlayerModel(file_model);

    glEng.setActiveCamera(0);
    glEng.setCamera_(getCamera());
}

void GraphicEngine::setWindowClose() {
    glfwSetWindowShouldClose(getWindow(), GL_TRUE);
}

void GraphicEngine::setWindowResolution(int width, int height) {
    glEng.setResolution(width, height);
}

void GraphicEngine::beginScene() {
    glEng.beginScene();
}

void GraphicEngine::drawScene() {
    glEng.drawScene();
}

void GraphicEngine::drawAllScene() {
    drawScene();
    //glEng.drawParticles();
    //glEng.drawBorder();
    glEng.drawSkybox(0);
}

void GraphicEngine::endScene() {
    glEng.endScene();
}

void GraphicEngine::removePlayerModel() {
    playerModel->remove();
}

//TNodo* GraphicEngine::loadModel(std::string file) {
//    return glEng.createModel(
//        NULL,
//        Vec3(1,0,0),
//        Vec3(0.f),
//        Vec3(1.f),
//        file
//    );
//}

//void GraphicEngine::loadTexture(TNodo* node, std::string text) {
//    RTexture* texture = glEng.getRG()->getResource<RTexture>(text);
//    node->setTexture(texture);
//}

//void GraphicEngine::drawHitbox(Vec3 pos, Vec3 hitb) {
//
//    ResourceGestor* rg = glEng.getRG();
//    RShader* scolor = rg->getResource<RShader>("SHADER_LINE");
//    scolor->use();
//
//    float vertices[] = {
//   /*1*/-hitb.x/2, -hitb.y/2, -hitb.z/2,  
//         hitb.x/2, -hitb.y/2, -hitb.z/2,
//         hitb.x/2,  hitb.y/2, -hitb.z/2,  
//         hitb.x/2,  hitb.y/2, -hitb.z/2,
//        -hitb.x/2,  hitb.y/2, -hitb.z/2,  
//        -hitb.x/2, -hitb.y/2, -hitb.z/2,
//
//   /*2*/-hitb.x/2, -hitb.y/2,  hitb.z/2,  
//         hitb.x/2, -hitb.y/2,  hitb.z/2,
//         hitb.x/2,  hitb.y/2,  hitb.z/2,  
//         hitb.x/2,  hitb.y/2,  hitb.z/2,
//        -hitb.x/2,  hitb.y/2,  hitb.z/2,  
//        -hitb.x/2, -hitb.y/2,  hitb.z/2,
//
//   /*3*/-hitb.x/2,  hitb.y/2,  hitb.z/2,  
//        -hitb.x/2,  hitb.y/2, -hitb.z/2,
//        -hitb.x/2, -hitb.y/2, -hitb.z/2,  
//        -hitb.x/2, -hitb.y/2, -hitb.z/2,
//        -hitb.x/2, -hitb.y/2,  hitb.z/2,  
//        -hitb.x/2,  hitb.y/2,  hitb.z/2,
//
//   /*4*/ hitb.x/2,  hitb.y/2,  hitb.z/2,  
//         hitb.x/2,  hitb.y/2, -hitb.z/2,
//         hitb.x/2, -hitb.y/2, -hitb.z/2,  
//         hitb.x/2, -hitb.y/2, -hitb.z/2,
//         hitb.x/2, -hitb.y/2,  hitb.z/2,  
//         hitb.x/2,  hitb.y/2,  hitb.z/2,
//
//   /*5*/-hitb.x/2, -hitb.y/2, -hitb.z/2,  
//         hitb.x/2, -hitb.y/2, -hitb.z/2,
//         hitb.x/2, -hitb.y/2,  hitb.z/2,  
//         hitb.x/2, -hitb.y/2,  hitb.z/2,
//        -hitb.x/2, -hitb.y/2,  hitb.z/2,  
//        -hitb.x/2, -hitb.y/2, -hitb.z/2,
//
//   /*6*/-hitb.x/2,  hitb.y/2, -hitb.z/2,  
//         hitb.x/2,  hitb.y/2, -hitb.z/2,
//         hitb.x/2,  hitb.y/2,  hitb.z/2,  
//         hitb.x/2,  hitb.y/2,  hitb.z/2,
//        -hitb.x/2,  hitb.y/2,  hitb.z/2,  
//        -hitb.x/2,  hitb.y/2, -hitb.z/2,
//        
//    };
//
//    unsigned int VAO, VBO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    Mat4 model = Mat4(1.0f);
//    model = glm::translate(model, pos);
//    Mat4 projection = glm::perspective(glm::radians(glEng.getActiveCamera()->Zoom), (float)glEng.getWidth() / (float)glEng.getHeight(), 0.1f, 100.f);
//    Mat4 view = glEng.getActiveCamera()->GetViewMatrix();
//
//    scolor->setMat4("projection", projection);
//    scolor->setMat4("view", view);
//    scolor->setMat4("model", model);
//
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//}   