#include "EFoco.hpp"

EFoco::EFoco(float intensity, lightType type, float aperture, float angle, float cons, float linear, float quadratic, Vec3 direccion, Vec3 ambiente, Vec3 difusa, Vec3 pos, Shader *shader)

    intensity_ = intensity; // R , G , B , A(lpha)
    tLightType_ = type;
    aperture_ = aperture;
    angleAttenuation_ = angle;
    // -------------------------
    constAttenuation_ = cons;
    linearAttenuation_ = linear;
    quadraticAttenuation_ = quadratic;

    direction = direccion;
    ambient = ambiente;
    diffuse = difusa;
    shader_ = shader;
}

EFoco::EFoco(){
    init();
}

EFoco::~EFoco(){
    init();
}

void EFoco::init(){

    intensity_ = 1.0f;
    tLightType_ = directional;
    aperture = 0.0f;
    angleAttenuation_ = 0.0f;
    constAttenuation_ = 0.0f;
    linearAttenuation_ = 0.0f;
    quadraticAttenuation_ = 0.0f;
}

Vec3 EFoco::checkColor(std::string color){
    Vec3 retorno(1.0f);

    if(strcmp(color.c_str()), "white" == 0)
        retorno = White_light;
    else if (strcmp(color.c_str()), "black" == 0)
        retorno = Black_light;
    else if (strcmp(color.c_str()), "red" == 0)
        retorno = Red_light;
    else if (strcmp(color.c_str()), "green" == 0)
        retorno = Green_light;
    else if (strcmp(color.c_str()), "dark_blue" == 0)
        retorno = DarkBlue_light;
    else if (strcmp(color.c_str()), "orange" == 0)
        retorno = Orange_light;
    else if (strcmp(color.c_str()), "yellow" == 0)
        retorno = Yellow_light;
    else if (strcmp(color.c_str()), "sky" == 0)
        retorno = Sky_light;
    else if (strcmp(color.c_str()), "light_yellow" == 0)
        retorno = LightYellow;

    return retorno;
}

void EFoco::draw(Mat4 modelMat, bool ){

    shader_->use();
    shader_->setMat4("model", modelMat);

    std::string p_strLights{};
    
    switch (tLightType_){

    case directional:
        shader_->setFloat("dirLight.intensity", intensity_);

        shader_->setVec3("dirLight.ambient", ambient);
        shader_->setVec3("dirLight.diffuse", diffuse);

        shader_->setVec3("dirLight.direction", direction);
        break;

    case punctual:
        p_strLights = "pointLights[" + std::to_string(pointID) + "].";

        shader_->setFloat(p_strLights + "intensity", intensity_);

        shader_->setVec3(p_strLights + "ambient", ambient);
        shader_->setVec3(p_strLights + "diffuse", diffuse);

        shader_->setVec3(p_strLights + "position", position);

        shader_->setFloat(p_strLights + "constant", constAttenuation_);
        shader_->setFloat(p_strLights + "linear", linearAttenuation_);
        shader_->setFloat(p_strLights + "quadratic", quadraticAttenuation_);
        break;
    
    case focal: 
        shader_->setFloat("spotLight.intensity", intensity_);

        shader_->setVec3("spotLight.ambient", ambient);
        shader_->setVec3("spotLight.diffuse", diffuse);

        shader_->setFloat("spotLight.constant", constAttenuation_);
        shader_->setFloat("spotLight.linear", linearAttenuation_);
        shader_->setFloat("spotLight.quadratic", quadraticAttenuation_);

        shader_->setFloat("spotLight.cutOff", glm::cos(glm::radians(45.5f)));
        shader_->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(35.0f)));
        break;

    default:
        break;
    }
}
//_____________________________
// SETTERS --------------------
//_____________________________

void EFoco::setIntensity_(float intensity) {
    intensity_ = intensity;
}

void EFoco::setLightType_(EFoco::lightType type) {
    tLightType_ = type;
}

void EFoco::setAperture_(float aperture) {
    aperture_ = aperture;
}

void EFoco::setAnglAttenuation_(float angle) {
    angleAttenuation_ = angle;
}

void EFoco::setConstAttenuation_(float constant) {
    constAttenuation_ = constant;
}

void EFoco::setLinearAttenuation_(float linear) {
    linearAttenuation_ = linear;
}

void EFoco::setQuadraticAttenuation_(float quadratic) {
    quadraticAttenuation_ = quadratic;
}

void EFoco::setPosition(Vec3 pos) {

    position = pos;
}

void EFoco::changeDiffClolor(Vec3 color) {
    this->diffuse = color;
}

void EFoco::changeDistance(int distance) {

    constAttenuation_ = 1.0f;

    switch(distance) {
    
    case 7:
        linearAttenuation_ = 0.7f;
        quadraticAttenuation_ = 1.8f;
        break;
    case 13:
        linearAttenuation_ = 0.35f;
        quadraticAttenuation_ = 0.44f;
        break;
    case 20:
        linearAttenuation_ = 0.22f;
        quadraticAttenuation_ = 0.20f;
        break;
    case 32:
        linearAttenuation_ = 0.14f;
        quadraticAttenuation_ = 0.07f;
        break;
    case 50:
        linearAttenuation_ = 0.09f;
        quadraticAttenuation_ = 0.032f;
        break;
    case 65:
        linearAttenuation_ = 0.07f;
        quadraticAttenuation_ = 0.017f;
        break;
    case 100:
        linearAttenuation_ = 0.045f;
        quadraticAttenuation_ = 0.0075f;
        break;
    case 200:
        linearAttenuation_ = 0.022f;
        quadraticAttenuation_ = 0.0019f;
        break;
    case 400:
        linearAttenuation_ = 0.01f;
        quadraticAttenuation_ = 0.0006f;
        break;
    case 1500:
        linearAttenuation_ = 0.0022;
        quadraticAttenuation_ = 0.000001f;
        break;

    default:
        linearAttenuation_ = 0.09f;
        quadraticAttenuation_ = 0.032f;
        break;
    }
}

// GETTERS

float EFoco::getIntensity_() const noexcept{
    return intensity_;
}