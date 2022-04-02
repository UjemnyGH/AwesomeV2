#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <algorithm>
#include "Core.hpp"

namespace aws
{
	class Aws_Camera
	{
	private:
		float x, y, z;
		float rx, ry, rz;

		float lrx, lry, lrz;

	public:
		void SetCameraPosition(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		void SetCameraRotation(float value, float value2, Axis axis)
		{
			if (axis == Axis::xy)
			{
				rx = cos(value) * cos(value2);
				ry = sin(value2);
				rz = sin(value) * cos(value2);
			}
			else if (axis == Axis::y)
			{
				rx = sin(value2);
				ry = cos(value) * cos(value2);
				rz = sin(value) * cos(value2);
			}
			else if (axis == Axis::z)
			{
				rx = 1 * lrz;
				ry = cos(x) - sin(x) * lry;
				rz = cos(x) + sin(x) * lrx;
			}

			lrx = rx;
			lry = ry;
			lrz = rz;
		}

		glm::vec3 GetCameraPosition() { return glm::vec3(x, y, z); }
		glm::vec3 GetCameraRotation() { return glm::vec3(rx, ry, rz); }
	};

	typedef Aws_Camera Camera;
}