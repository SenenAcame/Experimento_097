#ifndef CAMERA_H
#define CAMERA_H

#include <glad/src/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

class Camera {

public:
    //camera attrib
    glm::vec3 Position;
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

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) 
     : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM){

        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM){
        
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix(){
        return glm::lookAt(Position, Position+Front, Up);
    }

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

    void ProcessMouseMovement(float offset_x, float offset_y, GLboolean constraintPitch = true){

        offset_x *= MouseSensitivity;
        offset_y *= MouseSensitivity;

        Yaw   += offset_x;
        Pitch += offset_y;

        if(constraintPitch){
            if(Pitch > 89.0f){
                Pitch = 89.0f;
            }
            if(Pitch < -89.0f){
                Pitch = -89.0f; 
            }
        }

        updateCameraVectors();
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

private:
    void updateCameraVectors(){

        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif