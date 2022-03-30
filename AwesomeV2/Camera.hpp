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

		void SetCameraRotation(float value, Axis axis)
		{
			if (axis == Axis::z)
			{
				rx = (cos(value) - sin(value)) * lrx;
				ry = (cos(value) + sin(value)) * lry;
				rz = 1 * lrz;
			}
			else if (axis == Axis::x)
			{
				rx = 1 * lrx;
				ry = (cos(value) - sin(value)) * lry;
				rz = (cos(value) + sin(value)) * lrz;
			}
			else if (axis == Axis::y)
			{
				rx = (cos(value) + sin(value)) * lrx;
				ry = 1 * lry;
				rz = (cos(value) - sin(value)) * lrz;
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