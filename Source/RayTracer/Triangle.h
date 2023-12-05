#pragma once

#include "Object.h"

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
class Triangle : public Object {
	public:
		Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, std::shared_ptr<Material> material) :
			Object(material) {
			this->v1 = v1;
			this->v2 = v2;
			this->v3 = v3;
		}

		bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

	private:
		glm::vec3 v1;	
		glm::vec3 v2;
		glm::vec3 v3;
};