#pragma once
#include "Core.hpp"

namespace aws
{
	class Aws_CollisionHandler
	{
	private:

	public:
		bool AABBToMesh(Vector _aabb_pos, Vector _aabb_scale, std::vector<float> _mesh, Vector _mesh_pos, Vector _mesh_scale) {
			float x_index = ClosestMatch(_mesh.data(), _mesh.size(), _aabb_pos.x);
			float y_index = ClosestMatch(_mesh.data(), _mesh.size(), _aabb_pos.y);
			float z_index = ClosestMatch(_mesh.data(), _mesh.size(), _aabb_pos.z);

			unsigned int x_match_index = Search(0, _mesh.size(), _mesh, x_index);
			unsigned int y_match_index = Search(0, _mesh.size(), _mesh, y_index);
			unsigned int z_match_index = Search(0, _mesh.size(), _mesh, z_index);

			if (_mesh[x_match_index] == x_index && _mesh[z_match_index] == z_index && x_match_index + 2 == z_match_index)
			{
				Vector fix_pos = _aabb_pos - _aabb_scale;
				Vector fix_scale = _aabb_scale * to_vec(2.0f);

				Vector fix_mesh_pos = _mesh_pos - _mesh_scale;
				Vector fix_mesh_scale = _mesh_scale * to_vec(2.0f);

				bool collisionX = fix_pos.x + fix_scale.x >= x_index + fix_mesh_pos.x && (x_index + fix_mesh_pos.x) + fix_mesh_scale.x >= fix_pos.x;
				bool collisionY = fix_pos.y + fix_scale.y >= y_index + fix_mesh_pos.y && (y_index + fix_mesh_pos.y) + fix_mesh_scale.y >= fix_pos.y;
				bool collisionZ = fix_pos.z + fix_scale.z >= z_index + fix_mesh_pos.z && (z_index + fix_mesh_pos.z) + fix_mesh_scale.z >= fix_pos.z;

				if (true)
				{
					std::cout << "Collision: " << (bool)(collisionX && collisionY && collisionZ) << "\tClosest matches: " << x_index << ' ' << y_index << ' ' << z_index << "\tAABB: " << fix_pos.x << ' ' << fix_pos.y << ' ' << fix_pos.z << '\n';
				}

				return collisionX && collisionY && collisionZ;
			}

			return AABBToMesh(_aabb_pos, _aabb_scale, _mesh, _mesh_pos, _mesh_scale);
		}
	};

	typedef Aws_CollisionHandler CollisionHandler;
}