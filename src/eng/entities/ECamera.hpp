#pragma once

#include <glm/glm.hpp>
#include "Entity.hpp"

#include <vector>

enum Camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  5.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

struct ECamera : public Entity {

    ECamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    ECamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    glm::mat4 GetViewMatrix();

    void ProcessMouseMovement(float offset_x, float offset_y, GLboolean constraintPitch = true);
    
    void draw(Mat4, bool) override;

    void translate(Vec3 pos);
    void setPosition(Vec3 pos);
        //camera attrib
    glm::vec3 Position;
    Vec3 firstPosition;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    //euler angles
    float Yaw;
    float Pitch;

    //camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    void updateCameraVectors();
    /*
    void ProcessKeyboard(Camera_movement direction, float deltaTime){
        float speed = MovementSpeed * deltaTime;
        if(direction == FORWARD){
            Position += Front * speed;
        }
        if(direction == BACKWARD){
            Position -= Front * speed;
        }
        if(direction == LEFT){
            Position -= Right * speed;
        }
        if(direction == RIGHT){
            Position += Right * speed;
        }
        Position.y = 0.0f;
    }
    

    void ProcessMouseScroll(float offset_y){
        
        Zoom -= (float)offset_y;
        if(Zoom <1.0f){
            Zoom = 1.0;
        }
        if(Zoom > 45.0f){
            Zoom = 45.0f;
        }
    }
    */
};