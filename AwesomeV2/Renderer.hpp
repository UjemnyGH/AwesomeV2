#pragma once
#include "Core.hpp"

namespace aws
{
	class Aws_Renderer
	{
	private:
		Shader shader;
		Array vao;
		Buffer vertices_buf;
		Buffer color_buf;
		Buffer texture_coords_buf;
		Buffer texture_id_buf;
		Texture texture[32];
		Cubemap cubemap_texture;

		RenderedData data;
		Rendered objects_data;

		glm::mat4 transform = glm::mat4(1.0);

		float psr[3][3] = {
			{0.0f, 0.0f, 0.0f},
			{1.0f, 1.0f, 1.0f},
			{0.0f, 0.0f, 0.0f}
		};

		bool cubemap = false;

	public:
		Aws_Renderer() {

		}

		void Init() {
			shader.init();
			vao.init();
			vertices_buf.init();
			color_buf.init();
			texture_id_buf.init();
			texture_coords_buf.init();

			for (int i = 0; i < 31; i++)
			{
				texture[i].init();
			}

			shader.attachShader(vs, ShadType::vertex);
			shader.attachShader(fs, ShadType::fragment);
			shader.linkShader();

			texture[0].uniform(shader.ID, "Texture");

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);	
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);

			vao.unbind();
		}

		void Init(InShader vertex_shader, InShader fragment_shader, bool cubemap_init = false) {
			shader.init();
			vao.init();
			vertices_buf.init();
			color_buf.init();
			texture_id_buf.init();
			texture_coords_buf.init();

			for (int i = 0; i < 31; i++)
			{
				texture[i].init();
			}

			if(cubemap_init)
				cubemap_texture.init();
			
			shader.~Aws_Shader();
			shader.attachShader(vertex_shader, ShadType::vertex);
			shader.attachShader(fragment_shader, ShadType::fragment);
			shader.linkShader();

			if (cubemap_init)
				cubemap_texture.uniform(shader.ID, "skybox");
			else
				texture[0].uniform(shader.ID, "Texture");

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);

			vao.unbind();
		}

		void AddShader(InShader _shader, ShadType _type) {
			shader.attachShader(_shader, _type);
			shader.linkShader();

			texture[0].uniform(shader.ID, "Texture");
			cubemap_texture.uniform(shader.ID, "skybox");

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);

			vao.unbind();
		}

		void Render(glm::mat4 projection = glm::mat4(1.0), glm::mat4 view = glm::mat4(1.0)) {
			if (cubemap)
			{
				//glDepthFunc(GL_LEQUAL);
				glDepthMask(GL_FALSE);
			}

			shader.use();
			vao.bind();
			if (!cubemap)
			{
				texture[0].bind(0);
				texture[1].bind(1);
				texture[2].bind(2);
				texture[3].bind(3);
				texture[4].bind(4);
				texture[5].bind(5);
				texture[6].bind(6);
				texture[7].bind(7);
				texture[8].bind(8);
				texture[9].bind(9);
				texture[10].bind(10);
				texture[11].bind(11);
				texture[12].bind(12);
				texture[13].bind(13);
				texture[14].bind(14);
				texture[15].bind(15);
				texture[16].bind(16);
				texture[17].bind(17);
				texture[18].bind(18);
				texture[19].bind(19);
				texture[20].bind(20);
				texture[21].bind(21);
				texture[22].bind(22);
				texture[23].bind(23);
				texture[24].bind(24);
				texture[25].bind(25);
				texture[26].bind(26);
				texture[27].bind(27);
				texture[28].bind(28);
				texture[29].bind(29);
				texture[30].bind(30);
				texture[31].bind(31);
			}
			else
			{
				cubemap_texture.bind();
			}

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * transform));

			glDrawArrays(GL_TRIANGLES, 0, objects_data.sizeID);

			if (cubemap)
			{
				//glDepthFunc(GL_LESS);
				glDepthMask(GL_TRUE);
			}

			vao.unbind();
			shader.unuse();
		}

		void SetCubemap(std::vector<std::string> paths) {
			cubemap = true;
			
			shader.use();
			vao.bind();

			cubemap_texture.uniform(shader.ID, "skybox");
			cubemap_texture.bind(paths);

			vao.unbind();
			shader.unuse();
		}

		void SetRendererData(const RenderedData& m_data) {
			data = m_data;
			objects_data.count = 1;
			objects_data.sizeID = 0;
			objects_data.dataID.clear();

			objects_data.data = data;
			objects_data.sizeID = data.vertices.size() / 3;
			objects_data.axis_helper.push_back(AxisHelper(0.0f, 1.0f, 0.0f));

			for (int i = 0; i < objects_data.sizeID; i++) {
				objects_data.textureID.push_back(0.0f);
			}

			objects_data.dataID.push_back(objects_data.count);
			objects_data.name.insert(std::make_pair(objects_data.count, "Object " + std::to_string(objects_data.count)));

			objects_data.count++;

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);

			vao.unbind();
		}

		void AddObject() {
			objects_data.data += data;
			objects_data.axis_helper.push_back(AxisHelper(0.0f, 1.0f, 0.0f));

			objects_data.dataID.push_back(objects_data.count);
			objects_data.name.insert(std::make_pair(objects_data.count, "Object " + std::to_string(objects_data.count)));

			objects_data.count++;

			for (int i = 0; i < objects_data.count * objects_data.sizeID; i++) {
				objects_data.textureID.push_back(0.0f);
			}

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);

			vao.unbind();
		}

		void SetObjectName(const unsigned int ID, const std::string _name) {
			objects_data.name[ID] = _name;
		}

		void SetPositionByID(unsigned int ID, float x, float y, float z) {
			if (objects_data.axis_helper[ID].px != x && objects_data.axis_helper[ID].py != y && objects_data.axis_helper[ID].pz != z)
			{
				objects_data.axis_helper[ID].px = x;
				objects_data.axis_helper[ID].py = y;
				objects_data.axis_helper[ID].pz = z;

				for (size_t i = 0; i < objects_data.sizeID; i++)
				{
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3)] = data.vertices[i * 3] * objects_data.axis_helper[ID].sx + objects_data.axis_helper[ID].px;
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3 + 1)] = data.vertices[i * 3 + 1] * objects_data.axis_helper[ID].sy + objects_data.axis_helper[ID].py;
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3 + 2)] = data.vertices[i * 3 + 2] * objects_data.axis_helper[ID].sz + objects_data.axis_helper[ID].pz;
				};

				vao.bind();

				vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);

				vao.unbind();
			}
		}

		void SetScaleByID(unsigned int ID, float x, float y, float z) {
			if (objects_data.axis_helper[ID].sx != x && objects_data.axis_helper[ID].sy != y && objects_data.axis_helper[ID].sz != z)
			{
				objects_data.axis_helper[ID].sx = x;
				objects_data.axis_helper[ID].sy = y;
				objects_data.axis_helper[ID].sz = z;

				for (size_t i = 0; i < objects_data.sizeID; i++)
				{
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3)] = data.vertices[i * 3] * objects_data.axis_helper[ID].sx + objects_data.axis_helper[ID].px;
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3 + 1)] = data.vertices[i * 3 + 1] * objects_data.axis_helper[ID].sy + objects_data.axis_helper[ID].py;
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3 + 2)] = data.vertices[i * 3 + 2] * objects_data.axis_helper[ID].sz + objects_data.axis_helper[ID].pz;
				}

				vao.bind();

				vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);

				vao.unbind();
			}
		}

		void AddTexture(std::string name) {
			vao.bind();

			if (objects_data.textureCount < 32)
			{
				texture[objects_data.textureCount].bind(name, GL_REPEAT);

				objects_data.textureCount++;
			}
			else
			{
				texture[31].bind(name, GL_REPEAT);
			}

			vao.unbind();
		}

		void ChangeTextureInID(unsigned int textureID, std::string name) {
			vao.bind();

			if (textureID < 32)
			{
				texture[textureID].bind(name, GL_REPEAT);
			}
			else
			{
				texture[31].bind(name, GL_REPEAT);
			}

			vao.unbind();
		}

		void SetTextureByID(unsigned int ID, float textureID) {
			vao.bind();

			for (int i = ID * objects_data.sizeID; i < ID * objects_data.sizeID + objects_data.sizeID; i++) {
				objects_data.textureID[ID * objects_data.sizeID + i] = (float)textureID;
			}

			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);

			vao.unbind();
		}

		void SetPosition(float x, float y, float z) {
			psr[0][0] = x;
			psr[0][1] = y;
			psr[0][2] = z;

			transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
			transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
		}

		void SetScale(float x, float y, float z) {
			psr[1][0] = x;
			psr[1][1] = y;
			psr[1][2] = z;

			transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
			transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
		}

		void SetRotation(float x, float y, float z) {
			psr[2][0] = x;
			psr[2][1] = y;
			psr[2][2] = z;

			transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
			transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
		}

		void SetColorByID(unsigned int ID, float r, float g, float b, float a) {
			//if (objects_data.data.color[ID * objects_data.sizeID] != r && objects_data.data.color[ID * objects_data.sizeID + 1] != g && objects_data.data.color[ID * objects_data.sizeID + 2] != b && objects_data.data.color[ID * objects_data.sizeID + 3] != a)
			//{
				for (size_t i = 0; i < objects_data.sizeID; i++)
				{
					objects_data.data.color[ID * objects_data.sizeID + (i * 4)] = r;
					objects_data.data.color[ID * objects_data.sizeID + (i * 4 + 1)] = g;
					objects_data.data.color[ID * objects_data.sizeID + (i * 4 + 2)] = b;
					objects_data.data.color[ID * objects_data.sizeID + (i * 4 + 3)] = a;
				}

				vao.bind();

				color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);

				vao.unbind();
			//}
		}

		void SetInt1(const std::string _name, int _value) {
			shader.use();

			glUniform1i(glGetUniformLocation(shader.ID, _name.c_str()), _value);

			shader.unuse();
		}

		void SetInt2(const std::string _name, int _value1, int _value2) {
			shader.use();

			glUniform2i(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2);

			shader.unuse();
		}

		void SetInt3(const std::string _name, int _value1, int _value2, int _value3) {
			shader.use();

			glUniform3i(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2, _value3);

			shader.unuse();
		}

		void SetInt4(const std::string _name, int _value1, int _value2, int _value3, int _value4) {
			shader.use();

			glUniform4i(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2, _value3, _value4);

			shader.unuse();
		}

		void SetInt1v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform1iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetInt2v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform2iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetInt3v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform3iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetInt4v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform4iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetFloat1(const std::string _name, float _value) {
			shader.use();

			glUniform1f(glGetUniformLocation(shader.ID, _name.c_str()), _value);

			shader.unuse();
		}

		void SetFloat2(const std::string _name, float _value1, float _value2) {
			shader.use();

			glUniform2f(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2);

			shader.unuse();
		}

		void SetFloat3(const std::string _name, float _value1, float _value2, float _value3) {
			shader.use();

			glUniform3f(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2, _value3);

			shader.unuse();
		}

		void SetFloat4(const std::string _name, float _value1, float _value2, float _value3, float _value4) {
			shader.use();

			glUniform4f(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2, _value3, _value4);

			shader.unuse();
		}

		void SetFloat1v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform1fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetFloat2v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform2fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetFloat3v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform3fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetFloat4v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform4fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		void SetFloatMat2(const std::string _name, unsigned int _count, float* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix2fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, _value);

			shader.unuse();
		}

		void SetFloatMat3(const std::string _name, unsigned int _count, float* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix3fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, _value);

			shader.unuse();
		}

		void SetFloatMat4(const std::string _name, unsigned int _count, float* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, _value);

			shader.unuse();
		}

		void SetFloatMat2g(const std::string _name, unsigned int _count, glm::mat2* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix2fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, glm::value_ptr(*_value));

			shader.unuse();
		}

		void SetFloatMat3g(const std::string _name, unsigned int _count, glm::mat3* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix3fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, glm::value_ptr(*_value));

			shader.unuse();
		}

		void SetFloatMat4g(const std::string _name, unsigned int _count, glm::mat4* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, glm::value_ptr(*_value));

			shader.unuse();
		}

		~Aws_Renderer() {
			shader.~Aws_Shader();
			vao.~Aws_Array();
			vertices_buf.~Aws_Buffer();
			color_buf.~Aws_Buffer();
			texture_coords_buf.~Aws_Buffer();
		}
	};

	typedef Aws_Renderer Renderer;
};