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
		Buffer normals_buf;
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

		/**
		 * @brief Initialize Renderer
		 * 
		 */
		void Init() {
			shader.init();
			vao.init();
			vertices_buf.init();
			color_buf.init();
			texture_id_buf.init();
			texture_coords_buf.init();
			normals_buf.init();

			for (int i = 0; i < 31; i++)
			{
				texture[i].init();
			}

			shader.attachShader(vs, ShadType::vertex);
			shader.attachShader(fs, ShadType::fragment);
			shader.linkShader();

			texture[0].uniform(shader.ID, "Texture");
			cubemap_texture.uniform(shader.ID, "skybox");

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);	
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);
			normals_buf.bind(BuffType::general, objects_data.data.normals, 4, 3);

			vao.unbind();
		}

		/**
		 * @brief Initialize Renderer with inline shaders
		 * 
		 * @param vertex_shader
		 * @param fragment_shader 
		 * @param cubemap_init true to initialize cubemap 
		 */
		void Init(InShader vertex_shader, InShader fragment_shader, bool cubemap_init = false) {
			shader.init();
			vao.init();
			vertices_buf.init();
			color_buf.init();
			texture_id_buf.init();
			texture_coords_buf.init();
			normals_buf.init();

			for (int i = 0; i < 31; i++)
			{
				texture[i].init();
			}

			if(cubemap_init)
				cubemap_texture.init();
			
			shader.attachShader(vertex_shader, ShadType::vertex);
			shader.attachShader(fragment_shader, ShadType::fragment);
			shader.linkShader();

			cubemap_texture.uniform(shader.ID, "skybox");
			texture[0].uniform(shader.ID, "Texture");

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);
			normals_buf.bind(BuffType::general, objects_data.data.normals, 4, 3);

			vao.unbind();
		}

		/**
		 * @brief Initialize Renderer with ID to shaders
		 * 
		 * @param vertex_shader 
		 * @param fragment_shader 
		 * @param cubemap_init true to initialize cubemap
		 */
		void Init(uint32_t vertex_shader, uint32_t fragment_shader, bool cubemap_init = false) {
			shader.init();
			vao.init();
			vertices_buf.init();
			color_buf.init();
			texture_id_buf.init();
			texture_coords_buf.init();
			normals_buf.init();

			for (int i = 0; i < 31; i++)
			{
				texture[i].init();
			}

			if (cubemap_init)
				cubemap_texture.init();

			shader.attachShader(vertex_shader);
			shader.attachShader(fragment_shader);
			shader.linkShader();

			cubemap_texture.uniform(shader.ID, "skybox");
			texture[0].uniform(shader.ID, "Texture");

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);
			normals_buf.bind(BuffType::general, objects_data.data.normals, 4, 3);

			vao.unbind();
		}

		/**
		 * @brief Adds shader to Renderer
		 * 
		 * @param _shader inline shader
		 * @param _type type of shader
		 */
		void AddShader(InShader _shader, ShadType _type) {
			shader.attachShader(_shader, _type);
			shader.linkShader();

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);
			normals_buf.bind(BuffType::general, objects_data.data.normals, 4, 3);

			vao.unbind();
		}

		/**
		 * @brief Adds shader by ID of them
		 * 
		 * @param _shader LoadShader function loads shader by ID
		 */
		void AddShader(uint32_t _shader) {
			shader.attachShader(_shader);
			shader.linkShader();

			texture[0].uniform(shader.ID, "Texture");
			cubemap_texture.uniform(shader.ID, "skybox");

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);
			normals_buf.bind(BuffType::general, objects_data.data.normals, 4, 3);

			vao.unbind();
		}

		/**
		 * @brief Renders data
		 * 
		 * @param projection matrix 4x4
		 * @param view matrix 4x4
		 * @param skybox_cubemap true if renders skybox
		 */
		void Render(glm::mat4 projection = glm::mat4(1.0), glm::mat4 view = glm::mat4(1.0), bool skybox_cubemap = false) {
			if (cubemap && skybox_cubemap)
			{
				//glDepthFunc(GL_LEQUAL);
				glDepthMask(GL_FALSE);
			}

			shader.use();
			vao.bind();
			
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

			if(cubemap)
			{
				cubemap_texture.bind();
			}

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * transform));

			glDrawArrays(GL_TRIANGLES, 0, objects_data.sizeID);

			if (cubemap && skybox_cubemap)
			{
				//glDepthFunc(GL_LESS);
				glDepthMask(GL_TRUE);
			}

			vao.unbind();
			shader.unuse();
		}

		/**
		 * @brief Set the Cubemap object
		 * 
		 * @param paths faces of cubemap
		 */
		void SetCubemap(std::vector<std::string> paths) {
			cubemap = true;
			
			shader.use();
			vao.bind();

			cubemap_texture.bind(paths);

			vao.unbind();
			shader.unuse();
		}

		/**
		 * @brief Set the Custom Renderer Data objects
		 * 
		 * @param m_data custom data
		 */
		void SetRendererData(const RenderedData& m_data) {
			data = m_data;
			objects_data.count = 0;
			objects_data.sizeID = 0;
			objects_data.dataID.clear();
			objects_data.axis_helper.clear();
			objects_data.dataID.clear();
			objects_data.textureID.clear();
			objects_data.moved_vertices.clear();

			objects_data.moved_vertices.push_back(data.vertices[data.vertices.size() - 1]);
			objects_data.moved_vertices.push_back(data.vertices[data.vertices.size() - 2]);
			objects_data.moved_vertices.push_back(data.vertices[data.vertices.size() - 3]);

			std::move(data.vertices.begin(), data.vertices.end() - 3, std::back_inserter(objects_data.moved_vertices));

			objects_data.data += data;
			objects_data.sizeID = data.vertices.size() / 3;
			objects_data.axis_helper.push_back(AxisHelper(0.0f, 1.0f, 0.0f));

			for (int i = 0; i < objects_data.sizeID; i++) {
				objects_data.textureID.push_back(0.0f);
			}

			objects_data.dataID.push_back(objects_data.count);

			objects_data.count++;

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);
			normals_buf.bind(BuffType::general, objects_data.data.normals, 4, 3);

			vao.unbind();
		}

		/**
		 * @brief Adds one object in batch
		 * 
		 */
		void AddObject() {
			objects_data.data += data;

			objects_data.moved_vertices.push_back(data.vertices[data.vertices.size() - 1]);
			objects_data.moved_vertices.push_back(data.vertices[data.vertices.size() - 2]);
			objects_data.moved_vertices.push_back(data.vertices[data.vertices.size() - 3]);

			std::move(data.vertices.begin(), data.vertices.end() - 3, std::back_inserter(objects_data.moved_vertices));

			objects_data.axis_helper.push_back(AxisHelper(0.0f, 1.0f, 0.0f));

			objects_data.dataID.push_back(objects_data.count);

			objects_data.count++;

			for (int i = objects_data.count * objects_data.sizeID; i < objects_data.count * objects_data.sizeID + objects_data.sizeID; i++) {
				objects_data.textureID.push_back(0.0f);
			}

			vao.bind();

			vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);
			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);
			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);
			normals_buf.bind(BuffType::general, objects_data.data.normals, 4, 3);

			vao.unbind();
		}

		/**
		 * @brief Set the Position By ID of object
		 * 
		 * @param ID object ID in batch
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void SetPositionByID(unsigned int ID, Vector position) {
			if (objects_data.axis_helper[ID].px != position.x || objects_data.axis_helper[ID].py != position.y || objects_data.axis_helper[ID].pz != position.z)
			{
				objects_data.axis_helper[ID].px = position.x;
				objects_data.axis_helper[ID].py = position.y;
				objects_data.axis_helper[ID].pz = position.z;

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

		/**
		 * @brief Set the Scale By ID object
		 * 
		 * @param ID object ID in batch
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void SetScaleByID(unsigned int ID, Vector scale) {
			if (objects_data.axis_helper[ID].sx != scale.x || objects_data.axis_helper[ID].sy != scale.y || objects_data.axis_helper[ID].sz != scale.z)
			{
				objects_data.axis_helper[ID].sx = scale.x;
				objects_data.axis_helper[ID].sy = scale.y;
				objects_data.axis_helper[ID].sz = scale.z;

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

		/**
		 * @brief Set the Rotation By ID object
		 * 
		 * @param ID object ID in batch
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void SetRotationByID(unsigned int ID, Vector rotation) {
			if (objects_data.axis_helper[ID].rx != rotation.x || objects_data.axis_helper[ID].ry != rotation.y || objects_data.axis_helper[ID].rz != rotation.z)
			{
				objects_data.axis_helper[ID].rx = rotation.x;
				objects_data.axis_helper[ID].ry = rotation.y;
				objects_data.axis_helper[ID].rz = rotation.z;

				Vector rot_cart = CartToSphere(Radians(rotation.x), Radians(rotation.y), Radians(rotation.z));
				Vector rot = SphereToCart(rot_cart.x, rot_cart.y, rot_cart.z);

				for (size_t i = 0; i < objects_data.sizeID; i++)
				{
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3 + 0)] = data.vertices[i * 3 + 0] * objects_data.axis_helper[ID].sx + objects_data.axis_helper[ID].px + (rot.x * objects_data.moved_vertices[i * 3 + 0]);
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3 + 1)] = data.vertices[i * 3 + 1] * objects_data.axis_helper[ID].sy + objects_data.axis_helper[ID].py + (rot.y * objects_data.moved_vertices[i * 3 + 1]);
					objects_data.data.vertices[ID * objects_data.sizeID + (i * 3 + 2)] = data.vertices[i * 3 + 2] * objects_data.axis_helper[ID].sz + objects_data.axis_helper[ID].pz + (rot.z * objects_data.moved_vertices[i * 3 + 2]);
				}

				vao.bind();

				vertices_buf.bind(BuffType::general, objects_data.data.vertices, 0, 3);

				vao.unbind();
			}
		}

		/**
		 * @brief Adds texture to Renderer
		 * 
		 * @param name path to texture file
		 */
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

		/**
		 * @brief Change texture by ID
		 * 
		 * @param textureID ID of changed texture
		 * @param name path to texture file
		 */
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

		/**
		 * @brief Set the Texture By ID of object
		 * 
		 * @param ID ID of object to set the texture
		 * @param textureID ID of texture to set
		 */
		void SetTextureByID(unsigned int ID, float textureID) {
			vao.bind();

			for (int i = ID * objects_data.sizeID; i < ID * objects_data.sizeID + objects_data.sizeID; i++) {
				objects_data.textureID[i] = (float)textureID;
			}

			texture_id_buf.bind(BuffType::general, objects_data.textureID, 3, 1);

			vao.unbind();
		}

		/**
		 * @brief Set UV map in by ID of object
		 * 
		 * @param ID ID of object in batch
		 * @param value value to multiply
		 */
		void SetUVMapByID(const unsigned int ID, const float value) {
			vao.bind();

			for (int i = ID * objects_data.sizeID; i < ID * objects_data.sizeID + objects_data.sizeID; i++) {
				objects_data.data.texture_coordinates[i * 2] = data.texture_coordinates[i * 2] * value;
				objects_data.data.texture_coordinates[i * 2 + 1] = data.texture_coordinates[i * 2 + 1] * value;
			}

			texture_coords_buf.bind(BuffType::general, objects_data.data.texture_coordinates, 2, 2);

			vao.unbind();
		}

		/**
		 * @brief Set the Position object
		 * 
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void SetPosition(Vector position) {
			psr[0][0] = position.x;
			psr[0][1] = position.y;
			psr[0][2] = position.z;

			transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
			transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
		}

		/**
		 * @brief Set the Scale object
		 * 
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void SetScale(Vector scale) {
			psr[1][0] = scale.x;
			psr[1][1] = scale.y;
			psr[1][2] = scale.z;

			transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
			transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
		}

		/**
		 * @brief Set the Rotation object
		 * 
		 * @param x 
		 * @param y 
		 * @param z 
		 */
		void SetRotation(Vector rotation) {
			psr[2][0] = rotation.x;
			psr[2][1] = rotation.y;
			psr[2][2] = rotation.z;

			transform = glm::translate(glm::mat4(1.0), glm::vec3(psr[0][0], psr[0][1], psr[0][2]));
			transform = glm::rotate(transform, glm::radians(psr[2][0]), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][1]), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(psr[2][2]), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(psr[1][0], psr[1][1], psr[1][2]));
		}

		/**
		 * @brief Set the Color By ID object
		 * 
		 * @param ID ID of object in batch
		 * @param r 
		 * @param g 
		 * @param b 
		 * @param a 
		 */
		void SetColorByID(unsigned int ID, Vector color) {
			//if (objects_data.data.color[ID * objects_data.sizeID] != r && objects_data.data.color[ID * objects_data.sizeID + 1] != g && objects_data.data.color[ID * objects_data.sizeID + 2] != b && objects_data.data.color[ID * objects_data.sizeID + 3] != a)
			//{
				for (size_t i = 0; i < objects_data.sizeID; i++)
				{
					objects_data.data.color[ID * objects_data.sizeID + (i * 4)] = color.x;
					objects_data.data.color[ID * objects_data.sizeID + (i * 4 + 1)] = color.y;
					objects_data.data.color[ID * objects_data.sizeID + (i * 4 + 2)] = color.z;
					objects_data.data.color[ID * objects_data.sizeID + (i * 4 + 3)] = color.w;
				}

				vao.bind();

				color_buf.bind(BuffType::general, objects_data.data.color, 1, 4);

				vao.unbind();
			//}
		}

		/**
		 * @brief Set the Int 1 uniform
		 * 
		 * @param _name 
		 * @param _value 
		 */
		void SetInt1(const std::string _name, int _value) {
			shader.use();

			glUniform1i(glGetUniformLocation(shader.ID, _name.c_str()), _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Int 2 uniform
		 * 
		 * @param _name 
		 * @param _value1 
		 * @param _value2 
		 */
		void SetInt2(const std::string _name, int _value1, int _value2) {
			shader.use();

			glUniform2i(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2);

			shader.unuse();
		}

		/**
		 * @brief Set the Int 3 uniform
		 * 
		 * @param _name 
		 * @param _value1 
		 * @param _value2 
		 * @param _value3 
		 */
		void SetInt3(const std::string _name, int _value1, int _value2, int _value3) {
			shader.use();

			glUniform3i(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2, _value3);

			shader.unuse();
		}

		/**
		 * @brief Set the Int 4 uniform
		 * 
		 * @param _name 
		 * @param _value1 
		 * @param _value2 
		 * @param _value3 
		 * @param _value4 
		 */
		void SetInt4(const std::string _name, int _value1, int _value2, int _value3, int _value4) {
			shader.use();

			glUniform4i(glGetUniformLocation(shader.ID, _name.c_str()), _value1, _value2, _value3, _value4);

			shader.unuse();
		}

		/**
		 * @brief Set the Int 1 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetInt1v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform1iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Int 2 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetInt2v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform2iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Int 3 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetInt3v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform3iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Int 4 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetInt4v(const std::string _name, unsigned int _count, int* _value) {
			shader.use();

			glUniform4iv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 1 uniform
		 * 
		 * @param _name 
		 * @param _value 
		 */
		void SetFloat1(const std::string _name, float _value) {
			shader.use();

			glUniform1f(glGetUniformLocation(shader.ID, _name.c_str()), _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 2 uniform
		 * 
		 * @param _name 
		 * @param _value1 
		 * @param _value2 
		 */
		void SetFloat2(const std::string _name, Vector _value) {
			shader.use();

			glUniform2f(glGetUniformLocation(shader.ID, _name.c_str()), _value.x, _value.z);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 3 uniform
		 * 
		 * @param _name 
		 * @param _value1 
		 * @param _value2 
		 * @param _value3 
		 */
		void SetFloat3(const std::string _name, Vector _value) {
			shader.use();

			glUniform3f(glGetUniformLocation(shader.ID, _name.c_str()), _value.x, _value.y, _value.z);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 4 uniform
		 * 
		 * @param _name 
		 * @param _value1 
		 * @param _value2 
		 * @param _value3 
		 * @param _value4 
		 */
		void SetFloat4(const std::string _name, Vector _value) {
			shader.use();

			glUniform4f(glGetUniformLocation(shader.ID, _name.c_str()), _value.x, _value.y, _value.z, _value.w);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 1 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetFloat1v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform1fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 2 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetFloat2v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform2fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 3 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetFloat3v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform3fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float 4 pointer uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 */
		void SetFloat4v(const std::string _name, unsigned int _count, float* _value) {
			shader.use();

			glUniform4fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float Mat 2 uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 * @param _transpose 
		 */
		void SetFloatMat2(const std::string _name, unsigned int _count, float* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix2fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float Mat 3 uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 * @param _transpose 
		 */
		void SetFloatMat3(const std::string _name, unsigned int _count, float* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix3fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float Mat 4 uniform
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 * @param _transpose 
		 */
		void SetFloatMat4(const std::string _name, unsigned int _count, float* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, _value);

			shader.unuse();
		}

		/**
		 * @brief Set the Float Mat 2 by glm::mat2
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 * @param _transpose 
		 */
		void SetFloatMat2g(const std::string _name, unsigned int _count, glm::mat2* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix2fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, glm::value_ptr(*_value));

			shader.unuse();
		}

		/**
		 * @brief Set the Float Mat 3 by glm::mat3
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 * @param _transpose 
		 */
		void SetFloatMat3g(const std::string _name, unsigned int _count, glm::mat3* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix3fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, glm::value_ptr(*_value));

			shader.unuse();
		}

		/**
		 * @brief Set the Float Mat 4 by glm::mat4
		 * 
		 * @param _name 
		 * @param _count 
		 * @param _value 
		 * @param _transpose 
		 */
		void SetFloatMat4g(const std::string _name, unsigned int _count, glm::mat4* _value, GLboolean _transpose = GL_FALSE) {
			shader.use();

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, _name.c_str()), _count, _transpose, glm::value_ptr(*_value));

			shader.unuse();
		}

		/**
		 * @brief Debugging values 
		 * 
		 */
		void DebugValues() {
			for (int i = 0; i < objects_data.count * objects_data.sizeID; i++)
			{
				std::cout << objects_data.data.vertices[i * 3] << ' ' << objects_data.data.vertices[i * 3 + 1] << ' ' << objects_data.data.vertices[i * 3 + 2] << "\t\t" <<
					objects_data.textureID[i] << '\n';
			}
		}

		/**
		 * @brief Delete Renderer
		 * 
		 */
		void Terminate() {
			shader.terminate();
			vao.terminate();
			vertices_buf.terminate();
			color_buf.terminate();
			texture_coords_buf.terminate();

			if (cubemap)
			{
				cubemap_texture.terminate();
			}

			for (int i = 0; i < 32; i++)
			{
				texture[i].terminate();
			}
		}

		/**
		 * @brief Get the Object Axis Helper By ID object
		 * 
		 * @param ID ID of object in batch
		 * @return AxisHelper 
		 */
		AxisHelper GetObjectByID(unsigned int ID) {
			return objects_data.axis_helper[ID];
		}

		/**
		 * @brief Check collision on object with coordinates
		 * 
		 * @param ID ID of object in batch
		 * @param _position position of object
		 * @param _scale scale of object
		 * @return true 
		 * @return false 
		 */
		bool GetAABBTriggerByID(unsigned int ID, glm::vec3 _position, glm::vec3 _scale) {
			return CheckAABBCollision(_position, _scale, glm::vec3(psr[0][0] + objects_data.axis_helper[ID].px, psr[0][1] + objects_data.axis_helper[ID].py, psr[0][2] + objects_data.axis_helper[ID].pz), glm::vec3(psr[1][0] * objects_data.axis_helper[ID].sx, psr[1][1] * objects_data.axis_helper[ID].sy, psr[1][2] * objects_data.axis_helper[ID].sz));
		}

		/**
		 * @brief Get the Texture ID By ID
		 * 
		 * @param ID ID of object in batch
		 * @return unsigned int 
		 */
		unsigned int GetTextureIDByID(unsigned int ID) {
			return objects_data.textureID[ID * objects_data.sizeID];
		}

		/**
		 * @brief Get the One Object Size object
		 * 
		 * @return unsigned int 
		 */
		unsigned int GetObjectSize() {
			return objects_data.sizeID;
		}

		/**
		 * @brief Get the Objects Count object
		 * 
		 * @return unsigned int 
		 */
		unsigned int GetObjectsCount() {
			return objects_data.count;
		}

		/**
		 * @brief Get the Textures Count object
		 * 
		 * @return unsigned int 
		 */
		unsigned int GetTexturesCount() {
			return objects_data.textureCount;
		}

		~Aws_Renderer() {
			shader.~Aws_Shader();
			vao.~Aws_Array();
			vertices_buf.~Aws_Buffer();
			color_buf.~Aws_Buffer();
			texture_coords_buf.~Aws_Buffer();

			if (cubemap)
			{
				cubemap_texture.~Aws_Cubemap();
			}

			for (int i = 0; i < 32; i++)
			{
				texture[i].~Aws_Texture();
			}
		}
	};

	typedef Aws_Renderer Renderer;
};