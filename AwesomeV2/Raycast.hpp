#pragma once
#include "Core.hpp"

namespace aws
{
	class Aws_Raycast
	{
	private:

	public:
		Vector GetPoint(Vector _position, Vector _direction, Aws_RenderedData _mesh) {
			Vector point;
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

				Vector vert1 = { _mesh.vertices[i * 9], _mesh.vertices[i * 9 + 1], _mesh.vertices[i * 9 + 2] };
				Vector vert2 = { _mesh.vertices[i * 9 + 3], _mesh.vertices[i * 9 + 4], _mesh.vertices[i * 9 + 5] };
				Vector vert3 = { _mesh.vertices[i * 9 + 6], _mesh.vertices[i * 9 + 7], _mesh.vertices[i * 9 + 8] };

				Vector nor1 = { _mesh.normals[i * 9], _mesh.normals[i * 9 + 1], _mesh.normals[i * 9 + 2] };
				Vector nor2 = { _mesh.normals[i * 9 + 3], _mesh.normals[i * 9 + 4], _mesh.normals[i * 9 + 5] };
				Vector nor3 = { _mesh.normals[i * 9 + 6], _mesh.normals[i * 9 + 7], _mesh.normals[i * 9 + 8] };

				Vector avg_nor = avgVector({ nor1, nor2, nor3 });
				Vector avg_vert = avgVector({ vert1, vert2, vert3 });
			}

			return point;
		}
	};

	typedef Aws_Raycast Raycast;
};