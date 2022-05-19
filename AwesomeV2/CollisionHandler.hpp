#pragma once
#include "Core.hpp"

namespace aws
{
	class Aws_CollisionHandler
	{
	private:

	public:
		bool AABBToMesh(Vector _aabb_pos, Vector _aabb_scale, std::vector<float> _mesh, Vector _mesh_pos, Vector _mesh_scale) {
			float x_match = ClosestMatch(_mesh, _aabb_pos.x);
			float y_match = ClosestMatch(_mesh, _aabb_pos.y);
			float z_match = ClosestMatch(_mesh, _aabb_pos.z);

			size_t x_index = basicSearch(0, _mesh.size() - 1, _mesh, x_match);
			size_t y_index = basicSearch(0, _mesh.size() - 1, _mesh, y_match);
			size_t z_index = basicSearch(0, _mesh.size() - 1, _mesh, z_match);

			Vector aabb_pos = _aabb_pos - _aabb_scale;
			Vector aabb_scale = _aabb_scale * Vector(2.0f, 2.0f, 2.0f);

			Vector mesh_pos = _mesh_pos - _mesh_scale;
			Vector mesh_scale = _mesh_scale * Vector(2.0f, 2.0f, 2.0f);

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

		bool BoxCollision(Vector _position1, Vector _scale1, Vector _rotation1, Vector _position2, Vector _scale2, Vector _rotation2) {
			return false;
		}
	};

	typedef Aws_CollisionHandler CollisionHandler;
}