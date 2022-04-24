#version 450

const float Air = 1.0;
const float Glass = 1.51714;

const float Eta = Air / Glass;
 
const float R0 = ((Air - Glass) * (Air - Glass)) / ((Air + Glass) * (Air + Glass));

uniform mat4 transform;

layout(location = 0)in vec4 a_vertex;
in vec3 a_normal;

out vec3 v_reflection;
out vec3 v_refraction;
out float v_fresnel;

void main(void)
{
	vec4 vertex = u_modelMatrix*a_vertex;
	
	vec3 incident = normalize(vec3(vertex-u_camera));

	vec3 normal = u_normalMatrix*a_normal;
	
	v_refraction = refract(incident, normal, Eta);
	v_reflection = reflect(incident, normal);
			
	v_fresnel = R0 + (1.0 - R0) * pow((1.0 - dot(-incident, normal)), 5.0);
		
	gl_Position = u_viewProjectionMatrix*vertex;
}