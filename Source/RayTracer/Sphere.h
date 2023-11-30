#pragma once

#include "Ray.h"

class Sphere {
	public:
		bool Hit(const ray_t& ray, float tmin, float tmax);

		glm::vec3 center;
		float radius;
};