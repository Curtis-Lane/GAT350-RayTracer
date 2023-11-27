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