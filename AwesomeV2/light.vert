#version 450 core

uniform mat4 transform;

layout(location = 0)in vec4 aPos;
layout(location = 1)in vec4 aCol;
layout(location = 2)in vec2 aTexCoords;
layout(location = 3)in float aTextureID;
layout(location = 4)in vec3 aNormal;

out vec4 Col;
out vec2 TexCoords;
out float TextureID;
out vec3 Normal;
out vec4 Position;

void main()
{
	gl_Position = transform * aPos;
	Col = aCol;
	TexCoords = aTexCoords;
	TextureID = aTextureID;
	Normal = aNormal;
	Position = aPos;
}