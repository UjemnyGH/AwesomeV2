#version 450 core

uniform sampler2D Texture[32];
uniform vec3 g_light;

in vec4 Col;
in vec2 TexCoords;
in float TextureID;
in vec3 Normal;
in vec4 Position;

out vec4 Color;

void main()
{
	vec4 light = vec4(max(0.1, g_light.x - Normal.x), max(0.1, g_light.y - Normal.y), max(0.1, g_light.z - Normal.z), 1.0);

	vec4 light_grey = vec4((light.x + light.y + light.z) / 3.0, (light.x + light.y + light.z) / 3.0, (light.x + light.y + light.z) / 3.0, 1.0);
	float light_shade = (inversesqrt(distance(normalize(Position), vec4(g_light, 1.0))));

	int tID = int(TextureID);
	vec4 test_Color = texture(Texture[tID], TexCoords) * Col * light_grey * light_shade;
	if(test_Color.w < 0.1) discard;

	Color = test_Color;
}