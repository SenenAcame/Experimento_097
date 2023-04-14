#version 400 core
subroutine vec4 DiffuseFunc();
out vec4 FragColor;

struct Material {
    vec3 ambient;

    sampler2D diffuseSampler;
    vec4 diffuse;

    float shininess;
    float transparency;
};

struct DirLight {
    float intensity;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
};

struct PointLight {
    float intensity;
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
};

struct SpotLight {
    float intensity;
    vec3 position;

    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

#define NR_POINT_LIGTHS 4

uniform vec3 viewPos;
uniform DirLight dirLight;

uniform int pointSize;
uniform PointLight pointLights[NR_POINT_LIGTHS];
uniform SpotLight spotlight;
uniform Material material;

vec3 CalcDirLight(vec3 diffMat, DirLight light, vec3 normal);
vec3 CalcPointLight(vec3 diffMat, PointLight light, vec3 normal, vec3 fragPos);
vec3 CalcSpotLight(vec3 diffMat, SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

subroutine(DiffuseFunc)
vec4 colorDiff() {
    return material.diffuse;
}

subroutine(DiffuseFunc)
vec4 textureDiff() {
    return texture(material.diffuseSampler, TexCoords);
}

subroutine uniform DiffuseFunc diffuseVar;

const int levels = 4;
const float scaleFactor = 1.0/levels;
const float angleFactor = 3.14/levels;

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec4 diffuseColor = diffuseVar();

    if(diffuseColor.a < 0.1) 
        discard;
        // Phase 1: directional lightning
    vec3 result = CalcDirLight(diffuseColor.rgb, dirLight, norm);

    // Phase 2: point Lights
    for(int i = 0; i < pointSize; i++) {
        result += CalcPointLight(diffuseColor.rgb, pointLights[i], norm, FragPos);
    }
    // Phase 3: spot Lights
    //result += CalcSpotLight(diffuseColor.rgb, pointLights[i], norm, FragPos, viewDir);

    FragColor = vec4(result, diffuseColor.a * material.transparency);
    
}

vec3 CommonLight(vec3 diffMat, vec3 lPos, vec3 normal, vec3 ambient, vec3 diffuse, float intensity) {

    vec3 L = normalize(lPos);
    float df = max(0.0, dot(normal, L));

    return (diffMat * ambient + floor(df * levels) * scaleFactor * diffMat * diffuse) * intensity;
};

vec3 CalcDirLight(vec3 diffMat, DirLight light, vec3 normal) {
    return CommonLight(diffMat, -light.direction, normal, light.ambient, light.diffuse, light.intensity);
}

vec3 CalcPointLight(vec3 diffMat, PointLight light, vec3 normal, vec3 fragPos) {

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return CommonLight(diffMat, light.position -fragPos, normal, light.ambient, light.diffuse, light.intensity) * attenuation;
}

/*

vec3 CalcSpotLight(vec3 diffMat, SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

    vec3 s = normalize( light.position - fragPos );
    float angle = acos( dot( -s, light.direction));
    float cutOff = light.cutOff;
    vec3 ambient = light.ambient * diffMat;
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant  light.linear * distance + light.quadratic * (distance * distance));

    if(angle < cutOff) {
        angle = floor(3.14 - angle  levels) * angleFactor;
        if(angle >= angleFactor) {
            angle = 2 * angleFactor;
        } else {
            angle = angleFactor;
        }
        float spotFactor = pow(dot(-s, light.direction), light.constant);
        vec3 v = normalize(vec3(-fragPos));
        vec3 h = normalize(v+s);

        return ((ambient) + spotFactor *
                (light.diffuse * diffMat * max(  dot(s, nomal), 0.0))) * light.intensity.rgb * angle * attenuation;
    }

    return (ambient) * light.intensity.rgb * 0.05;
}

*/