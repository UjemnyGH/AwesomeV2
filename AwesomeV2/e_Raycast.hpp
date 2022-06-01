#pragma once
#include "e_Core.hpp"

namespace aws
{
	class Aws_Raycast
	{
	private:

	public:
		math::Vector GetPoint(math::Vector _position, math::Vector _direction, Aws_RenderedData _mesh) {
			math::Vector point;
			float closestLambda = FLT_MAX;

			for (uint32_t i = 0; i < _mesh.vertices.size() / 9; i++)
			{
				/*float lambda = (-dot3D({_mesh.normals[i * 9], _mesh.normals[i * 9 + 1], _mesh.normals[i * 9 + 2]}, avgVector(
					{
						{_mesh.vertices[i * 9], _mesh.vertices[i * 9 + 1], _mesh.vertices[i * 9 + 2]},
						{_mesh.vertices[i * 9 + 3], _mesh.vertices[i * 9 + 4], _mesh.vertices[i * 9 + 5]},
						{_mesh.vertices[i * 9 + 6], _mesh.vertices[i * 9 + 7], _mesh.vertices[i * 9 + 8]}
					}
				)) - dot3D({ _mesh.normals[i * 9], _mesh.normals[i * 9 + 1], _mesh.normals[i * 9 + 2] }, _position)) / dot3D({ _mesh.normals[i * 9], _mesh.normals[i * 9 + 1], _mesh.normals[i * 9 + 2] }, _direction);

				if (lambda < closestLambda && lambda > 0)
				{
					point = _position + (_direction * to_vec(lambda));
					closestLambda = lambda;
				}*/

				math::Vector vert1 = { _mesh.vertices[i * 9], _mesh.vertices[i * 9 + 1], _mesh.vertices[i * 9 + 2] };
				math::Vector vert2 = { _mesh.vertices[i * 9 + 3], _mesh.vertices[i * 9 + 4], _mesh.vertices[i * 9 + 5] };
				math::Vector vert3 = { _mesh.vertices[i * 9 + 6], _mesh.vertices[i * 9 + 7], _mesh.vertices[i * 9 + 8] };

				math::Vector nor1 = { _mesh.normals[i * 9], _mesh.normals[i * 9 + 1], _mesh.normals[i * 9 + 2] };
				math::Vector nor2 = { _mesh.normals[i * 9 + 3], _mesh.normals[i * 9 + 4], _mesh.normals[i * 9 + 5] };
				math::Vector nor3 = { _mesh.normals[i * 9 + 6], _mesh.normals[i * 9 + 7], _mesh.normals[i * 9 + 8] };

				math::Vector avg_nor = math::avgVector({ nor1, nor2, nor3 });
				math::Vector avg_vert = math::avgVector({ vert1, vert2, vert3 });
			}

			return point;
		}
	};

	typedef Aws_Raycast Raycast;
};