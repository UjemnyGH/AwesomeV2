#version 450 core
layout (location = 0) in vec4 aPos;
layout (location = 4) in vec3 aNormal;

out vec3 Normal;
out vec4 Position;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(transfrom / view / projection))) * aNormal;
    Position = transform * aPos;

    gl_Position = transform * aPos;
} 