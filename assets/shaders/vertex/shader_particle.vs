#version 400 core

layout(location = 0) in vec4 vertex;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 model;

uniform vec4 color;

void main() {
    float scale = 1.0f;
    TexCoords = vertex.zw;
    ParticleColor = color;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}