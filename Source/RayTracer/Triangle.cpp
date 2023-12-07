#include "Triangle.h"

#include "MathUtils.h"

bool Triangle::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
	// Set edges of the triangle
	glm::vec3 edge1 = this->v2 - this->v1;
	glm::vec3 edge2 = this->v3 - this->v1;

	// Calculate triangle normal
	glm::vec3 normal = cross(edge1, edge2);
	glm::vec3 pvec = cross(ray.direction, edge2);
	float determinant = dot(pvec, edge1);

	// If determinant is less than 0 then ray is hitting back of triangle
	// If determinant is 0 then ray is parallel to triangle suface
	if(determinant < 0 || approximately(determinant, 0)) {
		return false;
	}

	float invDet = 1 / determinant;

	glm::vec3 tvec = ray.origin - this->v1;
	float u = dot(tvec, pvec) * invDet;
	if(u < 0 || u > 1) {
		return false;
	}

	glm::vec3 qvec = cross(tvec, edge1);
	float v = dot(qvec, ray.direction) * invDet;
	if(v < 0 || u + v > 1) {
		return false;
	}

	float t = dot(edge2, qvec) * invDet;
	if(t >= minDistance && t <= maxDistance) {
		// Set raycast hit
		raycastHit.distance = t;
		raycastHit.point = ray.GetPoint(t);
		raycastHit.normal = glm::normalize(normal);
		raycastHit.material = GetMaterial();

		return true;
	}

	return false;
}
