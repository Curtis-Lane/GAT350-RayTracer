#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

class Camera {
	public:
		Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) {
			this->fov = fov;
			this->aspectRatio = aspectRatio;
			LookAt(eye, target, up);
		}

		void LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);
		ray_t GetRay(const glm::vec2& point) const;

	private:
		void CalculateViewPlane();

	private:
		// Eye position
		glm::vec3 eye = glm::vec3(0);

		// Camera Axis
		glm::vec3 right = glm::vec3(0);
		glm::vec3 up = glm::vec3(0);
		glm::vec3 forward = glm::vec3(0);

		// View plane origin and horizontal and vertical axis
		glm::vec3 lowerLeft = glm::vec3(0);
		glm::vec3 horizontal = glm::vec3(0);
		glm::vec3 vertical = glm::vec3(0);

		float fov = 0.0f; // Field of view (angle is in degrees)
		float aspectRatio = 0.0f; // Screen width / screen height (800 / 600 = 1.333)
};