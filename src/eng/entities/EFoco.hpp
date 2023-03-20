#pragma once 

#include <glm/glm.hpp>
#include "../resources/RShader.hpp"
#include <vector>
#include <string>
#include "../utils/typeUsing.hpp"
#include "../../cmp/entity.hpp"

#define White_light    Vec3(1.0f, 1.0f, 1.0f)
#define Black_light    Vec3(0.0f, 0.0f, 0.0f)

#define Red_light      Vec3(1.0f, 0.0f, 0.0f)
#define Green_light    Vec3(0.0f, 1.0f, 0.0f)
#define DarkBlue_light Vec3(0.0f, 0.0f, 1.0f)

#define Orange_light   Vec3(1.0f, 0.5f, 0.0f)
#define Yellow_light   Vec3(1.0f, 1.0f, 0.0f)

#define Sky_light      Vec3(0.22f, 0.69f, 0.26f)
#define LightYellow_light    Vec3(1.0f, 0.98f, 0.87f)


struct EFoco : public Entity {
    enum  lightType {
        directional, 
        punctual,
        focal
    };

    EFoco();
    EFoco(float intensity, lightType type, float aperture, float angle, float cons, float linear, float cuadratic, Vec3 direccion, Vec3 ambiente, Vec3 difusa, Vec3 pos, Shader *shader);
    ~EFoco();

    void init();
    void draw(Mat4, bool) /*override*/;

    //setters 
    void setIntensity_(float);
    void setLightType_(lightType);
    void setAperture_(float);
    void setAnglAttenuation_(float);
    void setConstAttenuation_(float);
    void setLinearAttenuation_(float);
    void setQuadraticAttenuation_(float);

    void setPosition(Vec3 pos);
    void changeAllColor(Vec3 color);
    void changeDiffClolor(Vec3 color);

    Vec3 checkColor(std::string color);

    void changeDistance(int distance);

    float getIntensity_() const noexcept;
    lightType getLightType() const noexcept;
    float getAperture_() const noexcept;
    float getAnglAttenuation_() const noexcept;
    float getConstAttenuation_() const noexcept;
    float getLinearAttenuation_() const noexcept;
    float getQuadraticAttenuation_() const noexcept;

    int pointID{0};

private:
    float intensity_;
    lightType tLightType_;
    float aperture_, angleAttenuation_;
    float constAttenuation_, linearAttenuation_, quadraticAttenuation_; // for punctual and focal lights
    Vec3 direction, ambient, diffuse, position;

    Shader *shader_{nullptr};
};