#pragma once

#include <glm/glm.hpp>

struct ray_t {
	ray_t() = default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) {
		this->origin = origin;
		this->direction = direction;
	}

	glm::vec3 GetPoint(float distance) const {return origin + (direction * distance);}

	glm::vec3 origin;
	glm::vec3 direction;
};

struct raycastHit_t {
	// Distance along the ray direction, from the origin to the hit point
	float distance = 0.0f;

	// World point of raycast hit
	glm::vec3 point = glm::vec3(0);
	// Surface normal of raycast hit
	glm::vec3 normal = glm::vec3(0);

	// Material attached to hit object
	class Material* material = nullptr;
};