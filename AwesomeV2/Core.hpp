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
#include "Model_loader.hpp"
//#include "cgltf.h"

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

namespace aws 
{
	/**
	 * @brief const char*
	 * 
	 */
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
		"Color = texture(skybox, TexCoords) * Col;\n"
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

	/**
	 * @brief Type of buffer(general or element)
	 * 
	 */
	enum BuffType
	{
		general = GL_ARRAY_BUFFER,
		element = GL_ELEMENT_ARRAY_BUFFER
	};

	/**
	 * @brief Shader type(names gives you everything you need)
	 * 
	 */
	enum ShadType
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER,
		compute = GL_COMPUTE_SHADER,
		tesselation_control = GL_TESS_CONTROL_SHADER,
		tesselation_evaluation = GL_TESS_EVALUATION_SHADER,
		geometry = GL_GEOMETRY_SHADER
	};

	/**
	 * @brief Defines what GetCameraRotation returns
	 * 
	 */
	enum CameraGetMode
	{
		Rotation,
		Normalized,
		Crossed
	};

	/**
	 * @brief Camera rotation axis(now only working "xy")
	 * 
	 */
	enum Axis
	{
		xy,
		y,
		z
	};

	/**
	 * @brief Time class(please use aws::Time::)
	 * 
	 */
	class Aws_Time
	{
	private:
		float lastFrame;
		float currentFrame;
		float deltaTime;

	public:
		/**
		 * @brief Get the Delta Time object
		 * 
		 * @return float 
		 */
		float GetDeltaTime() {
			return deltaTime;
		}

		/**
		 * @brief Calculate Delta Time(DO NOT USE THIS FUNCTION)
		 * 
		 */
		void CalcDeltaTime() {
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			currentFrame = glfwGetTime();
		}

		/**
		 * @brief Get the Time object
		 * 
		 * @return float 
		 */
		float GetTime() {
			return glfwGetTime();
		}
	};

	/**
	 * @brief Helps batched objects have they axis
	 * 
	 */
	struct Aws_AxisHepler {
		float px, py, pz, sx, sy, sz, rx, ry, rz;

		Aws_AxisHepler() = default;

		Aws_AxisHepler(float p, float s, float r) {
			px = py = pz = p;
			sx = sy = sz = s;
			rx = ry = rz = r;
		}
	};

	/**
	 * @brief Data of rendered objects
	 * 
	 */
	struct Aws_RenderedData
	{
		std::vector<float> vertices;
		std::vector<float> color;
		std::vector<float> texture_coordinates;
		std::vector<float> normals;

		Aws_RenderedData() = default;

		Aws_RenderedData(std::vector<float> _vertices, std::vector<float> _color, std::vector<float> _texture_coordinates, std::vector<float> _normals) {
			this->vertices.clear();
			std::move(_vertices.begin(), _vertices.end(), std::back_inserter(this->vertices));

			this->color.clear();
			std::move(_color.begin(), _color.end(), std::back_inserter(this->color));

			this->texture_coordinates.clear();
			std::move(_texture_coordinates.begin(), _texture_coordinates.end(), std::back_inserter(this->texture_coordinates));

			this->normals.clear();
			std::move(_normals.begin(), _normals.end(), std::back_inserter(this->normals));
		}

		Aws_RenderedData& operator=(const Aws_RenderedData& data) {
			this->vertices.clear();
			this->color.clear();
			this->texture_coordinates.clear();
			this->normals.clear();

			this->vertices = data.vertices;
			this->color = data.color;
			this->texture_coordinates = data.texture_coordinates;
			this->normals = data.normals;

			return *this;
		}

		Aws_RenderedData& operator+=(const Aws_RenderedData& data) {
			this->vertices.insert(this->vertices.end(), data.vertices.begin(), data.vertices.end());
			this->color.insert(this->color.end(), data.color.begin(), data.color.end());
			this->texture_coordinates.insert(this->texture_coordinates.end(), data.texture_coordinates.begin(), data.texture_coordinates.end());
			this->normals.insert(this->normals.end(), data.normals.begin(), data.normals.end());

			return *this;
		}
	};

	/**
	 * @brief Data of rendered objects along with aws::Renderer instance statistics
	 * 
	 */
	struct Aws_Rendered
	{
		Aws_RenderedData data;

		std::vector<unsigned int> dataID;
		std::vector<Aws_AxisHepler> axis_helper;
		std::vector<float> textureID;
		unsigned int sizeID;
		unsigned int count;
		unsigned int textureCount = 0;
	};

	/**
	 * @brief Basicly shader
	 * 
	 */
	struct Aws_Shader
	{
		unsigned int ID;

		Aws_Shader() {

		}

		/**
		 * @brief Initialize shader
		 * 
		 */
		void init() {
			ID = glCreateProgram();
		}

		/**
		 * @brief Attach shader to existing shader instance
		 * 
		 * @param shader hard coded shader
		 * @param type type of shader
		 */
		void attachShader(InShader shader, ShadType type)
		{
			unsigned int sh = glCreateShader(type);
			glShaderSource(sh, 1, &shader, nullptr);
			glCompileShader(sh);

			glAttachShader(ID, sh);
		}

		/**
		 * @brief attach shader by ID
		 * 
		 * @param shaderID ID of loaded shader(aws::LoadShader)
		 */
		void attachShader(uint32_t shaderID) {
			glAttachShader(ID, shaderID);
		}

		/**
		 * @brief Links shader
		 * 
		 */
		void linkShader() {
			glLinkProgram(ID);
		}

		/**
		 * @brief Use shader
		 * 
		 */
		void use() {
			glUseProgram(ID);
		}

		/**
		 * @brief Unuse shader(glUseProgram(0);)
		 * 
		 */
		void unuse() {
			glUseProgram(0);
		}

		/**
		 * @brief Delete shader
		 * 
		 */
		void terminate() {
			glDeleteShader(ID);
		}

		~Aws_Shader() {
			glDeleteProgram(ID);
		}
	};

	/**
	 * @brief Basicly array
	 * 
	 */
	struct Aws_Array
	{
		unsigned int ID;

		Aws_Array() {

		}

		/**
		 * @brief Initialize array
		 * 
		 */
		void init() {
			glGenVertexArrays(1, &ID);
		}

		/**
		 * @brief Binds array
		 * 
		 */
		void bind() {
			glBindVertexArray(ID);
		}

		/**
		 * @brief Unbinds array(glBindVertexArray(0);)
		 * 
		 */
		void unbind() {
			glBindVertexArray(0);
		}

		/**
		 * @brief Delete array
		 * 
		 */
		void terminate() {
			glDeleteVertexArrays(1, &ID);
		}

		~Aws_Array() {
			glDeleteVertexArrays(1, &ID);
		}
	};

	/**
	 * @brief Basicly buffer
	 * 
	 */
	struct Aws_Buffer
	{
		unsigned int ID;

		Aws_Buffer() {

		}

		/**
		 * @brief Initialize buffer
		 * 
		 */
		void init() {
			glGenBuffers(1, &ID);
		}

		/**
		 * @brief Bind buffer
		 * 
		 * @tparam T typename of data
		 * @param buffer_type buffer type (BuffType)
		 * @param data basicly data(std::vector)
		 * @param index index in shader
		 * @param dimensions dimensions(1, 2, 3, 4)
		 */
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

		/**
		 * @brief Delete buffer
		 * 
		 */
		void terminate() {
			glDeleteBuffers(1, &ID);
		}

		~Aws_Buffer() {
			glDeleteBuffers(1, &ID);
		}
	};

	/**
	 * @brief <UNUSED> Matrix 4x4 buffer
	 * 
	 */
	struct Aws_Mat4Buffer
	{
		unsigned int ID;

		Aws_Mat4Buffer() {

		}

		/**
		 * @brief Initialize buffer
		 * 
		 */
		void init() {
			glGenBuffers(1, &ID);
		}

		/**
		 * @brief Bind buffer
		 * 
		 * @tparam T typename
		 * @param data data
		 * @param index index in shader
		 */
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
		
		/**
		 * @brief Delete buffer
		 * 
		 */
		void terminate() {
			glDeleteBuffers(1, &ID);
		}

		~Aws_Mat4Buffer() {
			glDeleteBuffers(1, &ID);
		}
	};

	/**
	 * @brief Basicly texture
	 * 
	 */
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

		/**
		 * @brief Initialize texture
		 * 
		 */
		void init() {
			glGenTextures(1, &ID);
		}

		/**
		 * @brief Bind texture
		 * 
		 */
		void bind() {
			glBindTexture(GL_TEXTURE_2D, ID);
		}

		/**
		 * @brief Bind texture by ID(0-31)
		 * 
		 * @param _id 
		 */
		void bind(const unsigned int _id) {
			glBindTextureUnit(_id, ID);
		}

		/**
		 * @brief Bind texture and set data
		 * 
		 * @param name name of .png file(only that is handled right now)
		 * @param wrapping GL_REPEAT, GL_CLAMP_TO_EDGE...
		 * @param pixelized true = pixelized art(good for pixel arts)
		 */
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

		/**
		 * @brief Sets shader uniform by name
		 * 
		 * @param program Shader program
		 * @param place how uniform in shader has named
		 */
		void uniform(const unsigned int program, const std::string place) {
			glUseProgram(program);

			glUniform1iv(glGetUniformLocation(program, place.c_str()), 32, samplers);
			
			glUseProgram(0);
		}

		/**
		 * @brief Delete texture
		 * 
		 */
		void terminate() {
			glDeleteTextures(1, &ID);
		}

		~Aws_Texture() {
			glDeleteTextures(1, &ID);
		}
	};

	/**
	 * @brief Basicly cubemap texture
	 * 
	 */
	struct Aws_Cubemap
	{
		unsigned int ID;

		Aws_Cubemap() {

		}

		/**
		 * @brief Initialize cubemap texture
		 * 
		 */
		void init() {
			glGenTextures(1, &ID);
		}

		/**
		 * @brief Bind cubemap texture
		 * 
		 */
		void bind() {
			glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
		}

		/**
		 * @brief Bind cubemap texture with faces
		 * 
		 * @param faces texture faces
		 */
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

		/**
		 * @brief Set uniform in shader
		 * 
		 * @param program Shader program
		 * @param name how uniform han named in shader
		 */
		void uniform(const unsigned int program, const std::string name) {
			glUseProgram(program);

			glUniform1i(glGetUniformLocation(ID, name.c_str()), 0);

			glUseProgram(0);
		}

		/**
		 * @brief Delete cubemap texture
		 * 
		 */
		void terminate() {
			glDeleteTextures(1, &ID);
		}

		~Aws_Cubemap() {
			glDeleteTextures(1, &ID);
		}
	};

	/**
	 * @brief Linear search algorithm
	 * 
	 * @tparam T typename
	 * @tparam Arr data to search
	 * @param _first first element
	 * @param _last last element
	 * @param arr data to research
	 * @param value value to be founded bt address
	 * @return size_t 
	 */
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

	/**
	 * @brief Binary search algorithm
	 * 
	 * @tparam T typename
	 * @tparam Arr data to search
	 * @param _first first element
	 * @param _last last element
	 * @param arr data to research
	 * @param value value to be founded bt address
	 * @return size_t 
	 */
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

	/**
	 * @brief Exponential search algorithm
	 * 
	 * @tparam T typename
	 * @tparam Arr data to search
	 * @param size size of data
	 * @param arr data to research
	 * @param value value to be founded bt address
	 * @return size_t 
	 */
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

	/**
	 * @brief Ternary search algorithm
	 * 
	 * @tparam T typename
	 * @tparam Arr data to search
	 * @param _first first element
	 * @param _last last element
	 * @param arr data to research
	 * @param value value to be founded bt address
	 * @return size_t 
	 */
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
	
	/**
	 * @brief inverse atan2 function
	 * 
	 * @tparam T 
	 * @param radians angle in radians
	 * @return T* return in order[x, y]
	 */
	template<typename T>
	T* invatan2(T radians) {
		T _val[2];
		_val[0] = cos(radians);
		_val[1] = sin(radians);

		return _val;
	}

	/**
	 * @brief Checks 2 unrotatable box if they collide
	 * 
	 * @param _Position1 position of first box
	 * @param _Scale1 scale of first box
	 * @param _Position2 position of second box
	 * @param _Scale2 scale of second box
	 * @return true they collide
	 * @return false they not collide
	 */
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

	/**
	 * @brief Loads .obj model to memory
	 * 
	 * @param location path to .obj model
	 * @return Aws_RenderedData 
	 */
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

		return { meshData.vertices, __Fast_color, meshData.textureCoordinates, meshData.normals };
	}

	/**
	 * @brief Load shader as InShader data by path
	 * 
	 * @param path path to shader file
	 * @return InShader 
	 */
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

	/**
	 * @brief Loads shader ad ID by path to shader and shader type
	 * 
	 * @param path path to shader file
	 * @param type type of shader (ShadType)
	 * @return uint32_t 
	 */
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

	/**
	 * @brief Hard coded cube data
	 * 
	 */
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
		},
		{
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,

			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,

			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f
		}
	);

	/**
	 * @brief Hard coded cube data 2
	 * 
	 */
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
		},
		{
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,

			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,

			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f
		}
	);

	static Aws_Time time;

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