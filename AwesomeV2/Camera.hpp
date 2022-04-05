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
		/**
		 * @brief Set the Camera Position object
		 * 
		 * @param _x 
		 * @param _y 
		 * @param _z 
		 */
		void SetCameraPosition(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		/**
		 * @brief Set the Camera Rotation object
		 * 
		 * @param value 
		 * @param value2 
		 * @param axis 
		 */
		void SetCameraRotation(float value, float value2, Axis axis) {
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

		/**
		 * @brief Get the Camera Position object
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 GetCameraPosition() { return glm::vec3(x, y, z); }

		/**
		 * @brief Get the Camera Rotation object
		 * 
		 * @param camera_get_mode mode of returned values
		 * @return glm::vec3 
		 */
		glm::vec3 GetCameraRotation(const CameraGetMode& camera_get_mode = CameraGetMode::Rotation) { 
			if (camera_get_mode == CameraGetMode::Rotation)
				return glm::vec3(rx, ry, rz); 
			else if (camera_get_mode == CameraGetMode::Normalized)
				return glm::normalize(glm::vec3(rx, ry, rz));
			else if (camera_get_mode == CameraGetMode::Crossed)
				return glm::normalize(glm::cross(glm::vec3(rx, ry, rz), glm::vec3(0.0f, 1.0f, 0.0f)));
			else
				return glm::vec3(rx, ry, rz);
		}
	};

	typedef Aws_Camera Camera;
}