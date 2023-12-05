#pragma once

#include "Object.h"

class Plane : public Object {
	public:
		Plane() = default;
		Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) :
			Object(material) {
			this->center = center;
			this->normal = normal;
		}

		bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

	private:
		glm::vec3 center;
		glm::vec3 normal;
};