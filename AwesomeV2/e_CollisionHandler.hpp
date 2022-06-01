#pragma once
#include "e_Core.hpp"

namespace aws
{
	class Aws_CollisionHandler
	{
	private:

	public:
		bool AABBToMesh(math::Vector _aabb_pos, math::Vector _aabb_scale, std::vector<float> _mesh, math::Vector _mesh_pos, math::Vector _mesh_scale) {
			float x_match = math::ClosestMatch(_mesh, _aabb_pos.x);
			float y_match = math::ClosestMatch(_mesh, _aabb_pos.y);
			float z_match = math::ClosestMatch(_mesh, _aabb_pos.z);

			size_t x_index = math::basicSearch(0, _mesh.size() - 1, _mesh, x_match);
			size_t y_index = math::basicSearch(0, _mesh.size() - 1, _mesh, y_match);
			size_t z_index = math::basicSearch(0, _mesh.size() - 1, _mesh, z_match);

			math::Vector aabb_pos = _aabb_pos - _aabb_scale;
			math::Vector aabb_scale = _aabb_scale * math::Vector(2.0f, 2.0f, 2.0f);

			math::Vector mesh_pos = _mesh_pos - _mesh_scale;
			math::Vector mesh_scale = _mesh_scale * math::Vector(2.0f, 2.0f, 2.0f);

			if (_mesh[x_index] * mesh_scale.x + mesh_pos.x >= aabb_pos.x && aabb_pos.x + aabb_scale.x >= _mesh[x_index] + mesh_pos.x &&
				_mesh[x_index + 1] * mesh_scale.y + mesh_pos.y >= aabb_pos.y && aabb_pos.y + aabb_scale.y >= _mesh[x_index + 1] + mesh_pos.y &&
				_mesh[x_index + 2] * mesh_scale.z + mesh_pos.z >= aabb_pos.z && aabb_pos.z + aabb_scale.z >= _mesh[x_index + 2] + mesh_pos.z)
			{
				return true;
			}

			if (_mesh[y_index - 1] * mesh_scale.x + mesh_pos.x >= aabb_pos.x && aabb_pos.x + aabb_scale.x >= _mesh[y_index - 1] + mesh_pos.x &&
				_mesh[y_index] * mesh_scale.y + mesh_pos.y >= aabb_pos.y && aabb_pos.y + aabb_scale.y >= _mesh[y_index] + mesh_pos.y &&
				_mesh[y_index + 1] * mesh_scale.z + mesh_pos.z >= aabb_pos.z && aabb_pos.z + aabb_scale.z >= _mesh[y_index + 1] + mesh_pos.z)
			{
				return true;
			}

			if (_mesh[z_index - 2] * mesh_scale.x + mesh_pos.x >= aabb_pos.x && aabb_pos.x + aabb_scale.x >= _mesh[z_index - 2] + mesh_pos.x &&
				_mesh[z_index - 1] * mesh_scale.y + mesh_pos.y >= aabb_pos.y && aabb_pos.y + aabb_scale.y >= _mesh[z_index - 1] + mesh_pos.y &&
				_mesh[z_index] * mesh_scale.z + mesh_pos.z >= aabb_pos.z && aabb_pos.z + aabb_scale.z >= _mesh[z_index] + mesh_pos.z)
			{
				return true;
			}

			return false;
			//return AABBToMesh(_aabb_pos, _aabb_scale, _mesh, _mesh_pos, _mesh_scale);
		}

		bool BoxCollision(math::Vector _position1, math::Vector _scale1, math::Vector _rotation1, math::Vector _position2, math::Vector _scale2, math::Vector _rotation2) {
			return false;
		}
	};

	namespace physics
	{
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
	};
	

	typedef Aws_CollisionHandler CollisionHandler;
}