#pragma once

#include "Object.h"

class Sphere : public Object {
	public:
		Sphere() = default;
		Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
			Object(material) {
			this->center = center;
			this->radius = radius;
		}

		bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

	private:
		glm::vec3 center = glm::vec3(0);
		float radius = 0.0f;
};