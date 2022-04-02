#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include "stb_image.h"
#include "Model_Loader.hpp"
//#include "cgltf.h"

namespace aws 
{
	typedef const char* InShader;

	InShader cubemap_vs =
		"#version 450 core\n"
		"uniform mat4 transform;\n"
		"layout(location = 0)in vec4 aPos;\n"
		"layout(location = 1)in vec4 aCol;\n"
		"out vec3 TexCoords;\n"
		"out vec4 Col;\n"
		"void main()\n"
		"{\n"
		"TexCoords = aPos.xyz;\n"
		"Col = aCol;"
		"gl_Position = transform * aPos;\n"
		"}\n";

	InShader cubemap_fs =
		"#version 450 core\n"
		"uniform samplerCube skybox;\n"
		"in vec3 TexCoords;\n"
		"in vec4 Col;\n"
		"out vec4 Color;\n"
		"void main()\n"
		"{\n"
		"Color = texture(skybox, TexCoords / vec3(2.0, 2.0, 2.0)) * Col;\n"
		"}\n";

	InShader vs =
		"#version 450 core\n"
		"uniform mat4 transform;\n"
		"layout(location = 0)in vec4 aPos;\n"
		"layout(location = 1)in vec4 aCol;\n"
		"layout(location = 2)in vec2 aTexCoords;\n"
		"layout(location = 3)in float aTextureID;\n"
		"out vec4 Col;\n"
		"out vec2 TexCoords;\n"
		"out float TextureID;\n"
		"void main()\n"
		"{\n"
		"gl_Position = transform * aPos;\n"
		"Col = aCol;\n"
		"TexCoords = aTexCoords;\n"
		"TextureID = aTextureID;\n"
		"}\n";

	InShader fs = 
		"#version 450 core\n"
		"uniform sampler2D Texture[32];\n"
		"in vec4 Col;\n"
		"in vec2 TexCoords;\n"
		"in float TextureID;\n"
		"out vec4 Color;\n"
		"void main()\n"
		"{\n"
		"int tID = int(TextureID);"
		"vec4 test_Color = texture(Texture[tID], TexCoords) * Col;\n"
		"if(test_Color.w < 0.1) discard;\n"
		"Color = test_Color;\n"
		"}\n";

	//Source: https://github.com/McNopper/OpenGL/blob/master/Example15/shader/Water.vert.glsl
	InShader water_vs = 
		"#version 450 core\n"
		"#define NUMBERWAVES 4\n"
		"\n"
		"const float PI = 3.141592654;\n"
		"const float G = 9.81;\n"
		"\n"
		"uniform mat4 u_projectionMatrix;\n"
		"uniform mat4 u_viewMatrix;\n"
		"uniform mat4 u_transform;\n"
		"\n"
		"uniform float u_passedTime;\n"
		"\n"
		"uniform float u_waterPlaneLength;\n"
		"\n"
		"uniform vec4 u_waveParameters[NUMBERWAVES];\n"
		"uniform vec2 u_waveDirections[NUMBERWAVES];\n"
		"\n"
		"layout(location = 0)in vec4 vertex;\n"
		"\n"
		"out vec3 v_incident;\n"
		"\n"
		"out vec3 v_bitangent;\n"
		"out vec3 v_normal;\n"
		"out vec3 v_tangent;\n"
		"\n"
		"out vec2 v_texCoord;\n"
		"\n"
		"void main(void)\n"
		"{\n"
		"	vec4 finalVertex;\n"
		"\n"
		"	finalVertex.x = a_vertex.x;\n"
		"	finalVertex.y = a_vertex.y;\n"
		"	finalVertex.z = a_vertex.z;\n"
		"	finalVertex.w = 1.0;\n"
		"\n"
		"	vec3 finalBitangent;\n"
		"	vec3 finalNormal;\n"
		"	vec3 finalTangent;\n"
		"\n"
		"	finalBitangent.x = 0.0;\n"
		"	finalBitangent.y = 0.0;\n"
		"	finalBitangent.z = 0.0;\n"
		"\n"
		"	finalNormal.x = 0.0;\n"
		"	finalNormal.y = 0.0;\n"
		"	finalNormal.z = 0.0;\n"
		"\n"
		"	finalTangent.x = 0.0;\n"
		"	finalTangent.y = 0.0;\n"
		"	finalTangent.z = 0.0;\n"
		"\n"
		"	// see GPU Gems: Chapter 1. Effective Water Simulation from Physical Models\n"
		"	for (int i = 0; i < NUMBERWAVES; i++)\n"
		"	{\n"
		"		vec2 direction = normalize(u_waveDirections[i]);\n"
		"		float speed = u_waveParameters[i].x;\n"
		"		float amplitude = u_waveParameters[i].y;\n"
		"		float wavelength = u_waveParameters[i].z;\n"
		"		float steepness = u_waveParameters[i].w;\n"
		"\n"
		"		float frequency = sqrt(G * 2.0 * PI / wavelength);\n"
		"		float phase = speed * frequency;\n"
		"		float alpha = frequency * dot(direction, a_vertex.xz) + phase * u_passedTime;\n"
		"\n"
		"		finalVertex.x += steepness * amplitude * direction.x * cos(alpha);\n"
		"		finalVertex.y += amplitude * sin(alpha);\n"
		"		finalVertex.z += steepness * amplitude * direction.y * cos(alpha);\n"
		"	}\n"
		"\n"
		"	for (int i = 0; i < NUMBERWAVES; i++)\n"
		"	{\n"
		"		vec2 direction = normalize(u_waveDirections[i]);\n"
		"		float speed = u_waveParameters[i].x;\n"
		"		float amplitude = u_waveParameters[i].y;\n"
		"		float wavelength = u_waveParameters[i].z;\n"
		"		float steepness = u_waveParameters[i].w;\n"
		"\n"
		"		float frequency = sqrt(G * 2.0 * PI / wavelength);\n"
		"		float phase = speed * frequency;\n"
		"		float alpha = frequency * dot(direction, finalVertex.xz) + phase * u_passedTime;\n"
		"\n"
		"		// x direction\n"
		"		finalBitangent.x += steepness * direction.x * direction.x * wavelength * amplitude * sin(alpha);\n"
		"		finalBitangent.y += direction.x * wavelength * amplitude * cos(alpha);\n"
		"		finalBitangent.z += steepness * direction.x * direction.y * wavelength * amplitude * sin(alpha);\n"
		"\n"
		"		// y direction\n"
		"		finalNormal.x += direction.x * wavelength * amplitude * cos(alpha);\n"
		"		finalNormal.y += steepness * wavelength * amplitude * sin(alpha);\n"
		"		finalNormal.z += direction.y * wavelength * amplitude * cos(alpha);\n"
		"\n"
		"		// z direction\n"
		"		finalTangent.x += steepness * direction.x * direction.y * wavelength * amplitude * sin(alpha);\n"
		"		finalTangent.y += direction.y * wavelength * amplitude * cos(alpha);\n"
		"		finalTangent.z += steepness * direction.y * direction.y * wavelength * amplitude * sin(alpha);\n"
		"	}\n"
		"\n"
		"	finalTangent.x = -finalTangent.x;\n"
		"	finalTangent.z = 1.0 - finalTangent.z;\n"
		"	finalTangent = normalize(finalTangent);\n"
		"\n"
		"	finalBitangent.x = 1.0 - finalBitangent.x;\n"
		"	finalBitangent.z = -finalBitangent.z;\n"
		"	finalBitangent = normalize(finalBitangent);\n"
		"\n"
		"	finalNormal.x = -finalNormal.x;\n"
		"	finalNormal.y = 1.0 - finalNormal.y;\n"
		"	finalNormal.z = -finalNormal.z;\n"
		"	finalNormal = normalize(finalNormal);\n"
		"\n"
		"	v_bitangent = finalBitangent;\n"
		"	v_normal = finalNormal;\n"
		"	v_tangent = finalTangent;\n"
		"\n"
		"	v_texCoord = vec2(clamp((finalVertex.x + u_waterPlaneLength * 0.5 - 0.5) / u_waterPlaneLength, 0.0, 1.0), clamp((-finalVertex.z + u_waterPlaneLength * 0.5 + 0.5) / u_waterPlaneLength, 0.0, 1.0));\n"
		"\n"
		"	vec4 vertex = u_viewMatrix * finalVertex;\n"
		"\n"
		"	// We caculate in world space.\n"
		"	v_incident = u_transform * vec3(vertex);\n"
		"\n"
		"	gl_Position = u_projectionMatrix * u_viewMatrix * u_transform * vertex;\n"
		"}";

	//Source: https://github.com/McNopper/OpenGL/blob/master/Example15/shader/Water.frag.glsl
	InShader water_fs =
		"#version 450 core\n"
		"\n"
		"const float Eta = 0.15; // Water\n"
		"\n"
		"uniform samplerCube u_cubemap;\n"
		"uniform sampler2D Texture;\n"
		"\n"
		"in vec3 v_incident;\n"
		"\n"
		"in vec3 v_bitangent;\n"
		"in vec3 v_normal;\n"
		"in vec3 v_tangent;\n"
		"\n"
		"in vec2 v_texCoord;\n"
		"\n"
		"out vec4 fragColor;\n"
		"\n"
		"vec3 textureToNormal(vec4 orgNormalColor)\n"
		"{\n"
		"	return normalize(vec3(clamp(orgNormalColor.r * 2.0 - 1.0, -1.0, 1.0), clamp(orgNormalColor.g * 2.0 - 1.0, -1.0, 1.0), clamp(orgNormalColor.b * 2.0 - 1.0, -1.0, 1.0)));\n"
		"}\n"
		"\n"
		"void main(void)\n"
		"{\n"
		"	// The normals stored in the texture are in object space. No world transformations are yet done.\n"
		"	vec3 objectNormal = textureToNormal(texture(Texture, v_texCoord));\n"
		"\n"
		"	// These three vectors span a basis depending on the world transformations e.g. the waves.\n"
		"	mat3 objectToWorldMatrix = mat3(normalize(v_bitangent), normalize(v_normal), normalize(v_tangent));\n"
		"\n"
		"	vec3 worldNormal = objectToWorldMatrix * objectNormal;\n"
		"\n"
		"	vec3 worldIncident = normalize(v_incident);\n"
		"\n"
		"	vec3 refraction = refract(worldIncident, worldNormal, Eta);\n"
		"	vec3 reflection = reflect(worldIncident, worldNormal);\n"
		"\n"
		"	vec4 refractionColor = texture(u_cubemap, refraction);\n"
		"	vec4 reflectionColor = texture(u_cubemap, reflection);\n"
		"\n"
		"	float fresnel = Eta + (1.0 - Eta) * pow(max(0.0, 1.0 - dot(-worldIncident, worldNormal)), 5.0);\n"
		"\n"
		"	fragColor = mix(refractionColor, reflectionColor, fresnel);\n"
		"}";

	enum BuffType
	{
		general = GL_ARRAY_BUFFER,
		element = GL_ELEMENT_ARRAY_BUFFER
	};

	enum ShadType
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER,
		compute = GL_COMPUTE_SHADER,
		tesselation_control = GL_TESS_CONTROL_SHADER,
		tesselation_evaluation = GL_TESS_EVALUATION_SHADER,
		geometry = GL_GEOMETRY_SHADER
	};

	enum Axis
	{
		xy,
		y,
		z
	};

	class Aws_Time
	{
	private:
		float lastFrame, currentFrame, deltaTime;

	public:

		float GetDeltaTime() {
			return deltaTime;
		}

		void CalcDeltaTime() {
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			currentFrame = glfwGetTime();
		}

		float GetTime() {
			return glfwGetTime();
		}
	};

	struct Aws_AxisHepler {
		float px, py, pz, sx, sy, sz, rx, ry, rz;

		Aws_AxisHepler() = default;

		Aws_AxisHepler(float p, float s, float r) {
			px = py = pz = p;
			sx = sy = sz = s;
			rx = ry = rz = r;
		}
	};

	struct Aws_RenderedData
	{
		std::vector<float> vertices;
		std::vector<float> color;
		std::vector<float> texture_coordinates;

		Aws_RenderedData() = default;

		Aws_RenderedData(std::vector<float> _vertices, std::vector<float> _color, std::vector<float> _texture_coordinates) {
			this->vertices.clear();
			std::move(_vertices.begin(), _vertices.end(), std::back_inserter(this->vertices));

			this->color.clear();
			std::move(_color.begin(), _color.end(), std::back_inserter(this->color));

			this->texture_coordinates.clear();
			std::move(_texture_coordinates.begin(), _texture_coordinates.end(), std::back_inserter(this->texture_coordinates));
		}

		Aws_RenderedData operator=(const Aws_RenderedData& data) {
			this->vertices.clear();
			this->color.clear();
			this->texture_coordinates.clear();

			this->vertices = data.vertices;
			this->color = data.color;
			this->texture_coordinates = data.texture_coordinates;

			return data;
		}

		Aws_RenderedData operator+=(const Aws_RenderedData& data) {
			this->vertices.insert(this->vertices.end(), data.vertices.begin(), data.vertices.end());
			this->color.insert(this->color.end(), data.color.begin(), data.color.end());
			this->texture_coordinates.insert(this->texture_coordinates.end(), data.texture_coordinates.begin(), data.texture_coordinates.end());

			return data;
		}
	};

	struct Aws_Rendered
	{
		Aws_RenderedData data;

		std::vector<unsigned int> dataID;
		std::map<int, std::string> name;
		std::vector<Aws_AxisHepler> axis_helper;
		std::vector<float> textureID;
		unsigned int sizeID;
		unsigned int count;
		unsigned int textureCount = 0;
	};

	struct Aws_Shader
	{
		unsigned int ID;

		Aws_Shader() {

		}

		void init() {
			ID = glCreateProgram();
		}

		void attachShader(InShader shader, ShadType type)
		{
			unsigned int sh = glCreateShader(type);
			glShaderSource(sh, 1, &shader, nullptr);
			glCompileShader(sh);

			glAttachShader(ID, sh);
		}

		void attachShader(uint32_t shaderID) {
			glAttachShader(ID, shaderID);
		}

		void linkShader() {
			glLinkProgram(ID);
		}

		void use() {
			glUseProgram(ID);
		}

		void unuse() {
			glUseProgram(0);
		}

		void terminate() {
			glDeleteShader(ID);
		}

		~Aws_Shader() {
			glDeleteProgram(ID);
		}
	};

	struct Aws_Array
	{
		unsigned int ID;

		Aws_Array() {

		}

		void init() {
			glGenVertexArrays(1, &ID);
		}

		void bind() {
			glBindVertexArray(ID);
		}

		void unbind() {
			glBindVertexArray(0);
		}

		void terminate() {
			glDeleteVertexArrays(1, &ID);
		}

		~Aws_Array() {
			glDeleteVertexArrays(1, &ID);
		}
	};

	struct Aws_Buffer
	{
		unsigned int ID;

		Aws_Buffer() {

		}

		void init() {
			glGenBuffers(1, &ID);
		}

		template<class T>
		void bind(BuffType buffer_type, std::vector<T> data, uint32_t index = 0, uint8_t dimensions = 0) {
			glBindBuffer(buffer_type, ID);
			glBufferData(buffer_type, sizeof(T) * data.size(), data.data(), GL_DYNAMIC_DRAW);

			if (buffer_type == BuffType::general)
			{
				glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, 0, nullptr);
				glEnableVertexAttribArray(index);
			}
		}

		void terminate() {
			glDeleteBuffers(1, &ID);
		}

		~Aws_Buffer() {
			glDeleteBuffers(1, &ID);
		}
	};

	struct Aws_Mat4Buffer
	{
		unsigned int ID;

		Aws_Mat4Buffer() {

		}

		void init() {
			glGenBuffers(1, &ID);
		}

		template<class T>
		void bind(std::vector<T> data, uint32_t index = 0) {
			glBindBuffer(GL_ARRAY_BUFFER, ID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), GL_DYNAMIC_DRAW);

			glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, sizeof(T) * 16, (void*)0);
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index + 1, 4, GL_FLOAT, GL_FALSE, sizeof(T) * 16, (void*)(sizeof(T) * 4));
			glEnableVertexAttribArray(index + 1);
			glVertexAttribPointer(index + 2, 4, GL_FLOAT, GL_FALSE, sizeof(T) * 16, (void*)(sizeof(T) * 8));
			glEnableVertexAttribArray(index + 2);
			glVertexAttribPointer(index + 3, 4, GL_FLOAT, GL_FALSE, sizeof(T) * 16, (void*)(sizeof(T) * 12));
			glEnableVertexAttribArray(index + 3);
		}

		void terminate() {
			glDeleteBuffers(1, &ID);
		}

		~Aws_Mat4Buffer() {
			glDeleteBuffers(1, &ID);
		}
	};

	struct Aws_Texture
	{
		unsigned int ID;
		unsigned char* data;
		int width, height, nrChannels;

		int samplers[32] = {
		0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     14,     15,
		16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31
		};

		Aws_Texture() {

		}

		void init() {
			glGenTextures(1, &ID);
		}

		void bind() {
			glBindTexture(GL_TEXTURE_2D, ID);
		}

		void bind(const unsigned int _id) {
			glBindTextureUnit(_id, ID);
		}

		void bind(const std::string& name, const unsigned int& wrapping, bool pixelized = false) {
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
			if (!pixelized)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else if (pixelized)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}

			stbi_set_flip_vertically_on_load(1);

			data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Error loading image\n";
			}

			stbi_image_free(data);
		}

		void uniform(const unsigned int program, const std::string place) {
			glUseProgram(program);

			glUniform1iv(glGetUniformLocation(program, place.c_str()), 32, samplers);
			
			glUseProgram(0);
		}

		void terminate() {
			glDeleteTextures(1, &ID);
		}

		~Aws_Texture() {
			glDeleteTextures(1, &ID);
		}
	};

	struct Aws_Cubemap
	{
		unsigned int ID;

		Aws_Cubemap() {

		}

		void init() {
			glGenTextures(1, &ID);
		}

		void bind() {
			glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
		}

		void bind(std::vector<std::string> faces)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

			int width, height, nrChannels;
			for (unsigned int i = 0; i < faces.size(); i++)
			{
				unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
				if (data)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
				}
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		void uniform(const unsigned int program, const std::string name) {
			glUseProgram(program);

			glUniform1i(glGetUniformLocation(ID, name.c_str()), 0);

			glUseProgram(0);
		}

		void terminate() {
			glDeleteTextures(1, &ID);
		}

		~Aws_Cubemap() {
			glDeleteTextures(1, &ID);
		}
	};

	template<class T, class Arr>
	size_t Search(size_t _first, size_t _last, Arr arr, T value) {
		size_t pos;

		if (_first <= _last && value >= arr[_first] && value <= arr[_last]) {
			pos = _first + ((_last - _first) / (arr[_last] - arr[_first]) * (value - arr[_first]));

			if (arr[pos] == value)
				return pos;

			if (arr[pos] < value)
				return Search(pos + 1, _last, arr, value);

			if (arr[pos] > value)
				return Search(_first, pos - 1, arr, value);
		}

		return -1;
	}

	template<class T, class Arr>
	size_t binSearch(size_t _first, size_t _last, Arr arr, T value) {
		if (_last >= 1) {
			int pos = _first + (_last - _first) / 2;

			if (arr[pos] == value)
				return pos;

			if (arr[pos] > value)
				return binSearch(_first, pos - 1, arr, value);

			return binSearch(pos + 1, _last, arr, value);
		}

		return -1;
	}

	template<class T, class Arr>
	size_t expSearch(size_t size, Arr arr, T value) {
		if (arr[0] == value)
			return arr[0];

		int i = 1;
		while (i < size && arr[i] <= value) {
			i = i * 2;
		}

		return binSearch(i / 2, fmin(i, size - 1), arr, value);
	}

	template<class T, class Arr>
	size_t ternSearch(size_t _first, size_t _last, Arr arr, T value) {
		if (_last >= 1) {
			int pos1 = _first + (_last - 1) / 3;
			int pos2 = _last - (_last - 1) / 3;

			if (arr[pos1] == value)
				return pos1;

			if (arr[pos2] == value)
				return pos2;

			if (value < arr[pos1])
				return ternSearch(_first, pos1 - 1, arr, value);
			else if (value > arr[pos2])
				return ternSearch(pos2 + 1, _last, arr, value);
			else
				return ternSearch(pos1 + 1, pos2 - 1, arr, value);
		}

		return -1;
	}

	bool CheckAABBCollision(const glm::vec3 _Position1, const glm::vec3 _Scale1, const glm::vec3 _Position2, const glm::vec3 _Scale2) {
		glm::vec3 Position1 = _Position1 - _Scale1;
		glm::vec3 Scale1 = _Scale1 * glm::vec3(2.0f, 2.0f, 2.0f);

		glm::vec3 Position2 = _Position2 - _Scale2;
		glm::vec3 Scale2 = _Scale2 * glm::vec3(2.0f, 2.0f, 2.0f);

        bool collisionX = Position1.x + Scale1.x >= Position2.x &&
			Position2.x + Scale2.x >= Position1.x;

        bool collisionY = Position1.y + Scale1.y >= Position2.y &&
			Position2.y + Scale2.y >= Position1.y;

        bool collisionZ = Position1.z + Scale1.z >= Position2.z &&
			Position2.z + Scale2.z >= Position1.z;

        return collisionX && collisionY && collisionZ;
    }

	Aws_RenderedData LoadOBJModel(const std::string& location) {
		BufferMeshData meshData = LoadMeshBuffer(location);

		std::vector<float> __Fast_color;

		for (int i = 0; i < (meshData.vertices.size() / 3); i++)
		{
			__Fast_color.push_back(1.0f);
			__Fast_color.push_back(1.0f);
			__Fast_color.push_back(1.0f);
			__Fast_color.push_back(1.0f);
		}

		/*for (int i = 0; i < meshData.vertices.size() / 3; i++)
		{
			std::cout << "Iter: " << i << '\t' << meshData.vertices[i * 3] << ' ' << meshData.vertices[i * 3 + 1] << ' ' << meshData.vertices[i * 3 + 2] << "\n";
		}*/

		return { meshData.vertices, __Fast_color, meshData.textureCoordinates };
	}

	InShader LoadShader(const std::string& path) {
		std::ifstream f;

		f.open(path.c_str(), std::ios_base::binary);

		if (f.bad())
		{
			return "NULL";
		}

		f.seekg(0, std::ios_base::end);

		int len = static_cast<int>(f.tellg());

		f.seekg(0, std::ios_base::beg);

		char* src = new char[(len + 1) * sizeof(char)];
		f.read(src, len);
		src[len] = '\0';
		f.close();

		std::string source = src;

		delete[] src;

		std::cout << source.c_str();

		return source.c_str();
	}

	uint32_t LoadShader(const std::string& path, ShadType type) {
		std::ifstream f;

		f.open(path.c_str(), std::ios_base::binary);

		if (f.bad())
		{
			return 0;
		}

		f.seekg(0, std::ios_base::end);

		int len = static_cast<int>(f.tellg());

		f.seekg(0, std::ios_base::beg);

		char* src = new char[(len + 1) * sizeof(char)];
		f.read(src, len);
		src[len] = '\0';
		f.close();

		uint32_t shader = glCreateShader(type);

		glShaderSource(shader, 1, &src, nullptr);

		delete[] src;

		glCompileShader(shader);

		return shader;
	}

	/*Aws_RenderedData LoadGLTFModel(const std::string location) {
		cgltf_options options = { cgltf_file_type_invalid };
		cgltf_data* data = NULL;
		cgltf_result result = cgltf_parse_file(&options, location.c_str(), &data);

		if (result == cgltf_result_success)
		{
			result = cgltf_load_buffers(&options, data, location.c_str());

			std::cout << "" << data->nodes->mesh->

			cgltf_free(data);
		}

	}*/

	const Aws_RenderedData cube = Aws_RenderedData(
		{
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,

			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			//
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			//
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,

			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			//
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			//
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,

			-1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			//
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f
		},
		{
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f
		},
		{
			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		}
	);

	const Aws_RenderedData skybox = Aws_RenderedData(
		{
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		},
		{
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,

			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f,
			0.86f, 0.86f, 0.86f, 1.0f
		},
		{
			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			1.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		}
	);

	Aws_Time time;

	typedef Aws_Time Time;

	typedef Aws_AxisHepler AxisHelper;
	typedef Aws_RenderedData RenderedData;
	typedef Aws_Rendered Rendered;
	typedef Aws_Shader Shader;
	typedef Aws_Array Array;
	typedef Aws_Buffer Buffer;
	typedef Aws_Mat4Buffer Mat4Buffer;
	typedef Aws_Texture Texture;
	typedef Aws_Cubemap Cubemap;
}