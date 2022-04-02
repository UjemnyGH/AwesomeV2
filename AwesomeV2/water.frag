#version 450 core

const float PI = 3.141592654;
const float G = 9.81;

uniform sampler2D Texture[32];

in vec4 Col;
in vec2 TexCoords;
in float TextureID;
in float time;

out vec4 Color;

void main()
{
    int tID = int(TextureID);
    //vec4 test_Color = texture(Texture[1], TexCoords) * Col;
    vec4 test_Color = ceil(vec4(0.0, sin(time), 0.0, 1.0));

    if(test_Color.w < 0.1) 
        discard;

    Color = test_Color;
}