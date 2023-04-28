#include "ECamera.hpp"

ECamera::ECamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

ECamera::ECamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {

    Position = Vec3(posX, posY, posZ);
    WorldUp = Vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// devielve la matriz de vista
glm::mat4 ECamera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

// procesa el movimiento del raton y se lo aplica a la camara
void ECamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constraintPitch) {

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    //se limita el pitch de la camara
    if(constraintPitch) {
        if(Pitch > 89.0f){
            Pitch = 89.0f;
        }
        if(Pitch < -89.0f){
            Pitch = -89.0f;
        }
    }
    updateCameraVectors();
}

 //No hace nada
void ECamera::draw(Mat4 mat, bool){
    //this->Position = Vec3(mat[3][0], mat[3][1], mat[3][2]);
}

// actualiza la posicion y la suma a la que tenia
void ECamera::translate(Vec3 pos) {
    Position += pos;
    updateCameraVectors();
}

// actualiza a la nueva posicion
void ECamera::setPosition(Vec3 pos) {
    Position = pos;
    updateCameraVectors();
}

// actualiza los vectores de front, right y up
void ECamera::updateCameraVectors() {

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}