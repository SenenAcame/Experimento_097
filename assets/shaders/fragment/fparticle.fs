#version 400 core

in vec2 TexCoords;
in vec4 ParticleColor;

out vec4 FragColor;
uniform sampler2D sprite;

void main() {
    vec4 diffuseColor = (texture(sprite, TexCoords) * ParticleColor);
    if(diffuseColor.a < 0.1)
        discard;
    FragColor = diffuseColor;
}