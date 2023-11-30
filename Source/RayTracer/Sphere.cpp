#include "Sphere.h"

#include "MathUtils.h"

bool Sphere::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
	glm::vec3 oc = ray.origin - this->center;
	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.direction, oc);
	float c = dot(oc, oc) - (this->radius * this->radius);

	// b^2 - 4ac
	float discriminant = (b * b) - (4 * a * c);

	// 0 = 1 hit
	// 1 = 2 hit

	if(discriminant >= 0) {
		float t = (-b - sqrt(discriminant)) / (2 * a);
		if(t > minDistance && t < maxDistance) {
			raycastHit.distance = t;
			raycastHit.point = ray.GetPoint(t);
			raycastHit.normal = (raycastHit.point - this->center) / this->radius;

			raycastHit.material = GetMaterial();

			return true;
		}
		t = (-b + sqrt(discriminant)) / (2 * a);
		if(t > minDistance && t < maxDistance) {
			raycastHit.distance = t;
			raycastHit.point = ray.GetPoint(t);
			raycastHit.normal = (raycastHit.point - this->center) / this->radius;

			raycastHit.material = GetMaterial();

			return true;
		}
	}

	return false;
}
