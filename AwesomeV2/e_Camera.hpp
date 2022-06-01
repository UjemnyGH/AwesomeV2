#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <algorithm>
#include "e_Core.hpp"

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
		void SetCameraPosition(math::Vector pos) {
			x = pos.x;
			y = pos.y;
			z = pos.z;
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
		 * @return Vector
		 */
		math::Vector GetCameraPosition() { return { x, y, z }; }

		/**
		 * @brief Get the Camera Position object
		 *
		 * @return glm::vec3
		 */
		glm::vec3 GetCameraPositionV3() { return { x, y, z }; }

		/**
		 * @brief Get the Camera Rotation object
		 * 
		 * @param camera_get_mode mode of returned values
		 * @return glm::vec3 
		 */
		math::Vector GetCameraRotation(const CameraGetMode& camera_get_mode = CameraGetMode::Rotation) { 
			if (camera_get_mode == CameraGetMode::Rotation)
				return { rx, ry, rz };
			else if (camera_get_mode == CameraGetMode::Normalized)
				return math::Vector(glm::normalize(glm::vec3(rx, ry, rz)).x, glm::normalize(glm::vec3(rx, ry, rz)).y, glm::normalize(glm::vec3(rx, ry, rz)).z);
			else if (camera_get_mode == CameraGetMode::Crossed)
				return math::Vector(glm::normalize(glm::cross(glm::normalize(glm::vec3(rx, ry, rz)), glm::vec3(0.0f, 1.0f, 0.0f))).x, glm::normalize(glm::cross(glm::normalize(glm::vec3(rx, ry, rz)), glm::vec3(0.0f, 1.0f, 0.0f))).y, glm::normalize(glm::cross(glm::normalize(glm::vec3(rx, ry, rz)), glm::vec3(0.0f, 1.0f, 0.0f))).z);
			else
				return { rx, ry, rz };
		}
	};

	typedef Aws_Camera Camera;
}