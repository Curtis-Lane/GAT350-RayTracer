#include "Plane.h"

#include "MathUtils.h"

bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
	// Check dot product of ray direction and plane normal, if result is 0 then ray direction if parallel to plane
	// The dot product is 0 if the two vectors are perpendicular (90 degrees)
	float denominator = dot(ray.direction, this->normal);
	if(approximately(denominator, 0)) {
		return false; // Ray direction and plane parallel, no intersection
	}

	// Get t (distance) along ray direction to hit point
	float t = dot(this->center - ray.origin, this->normal) / denominator;
	if(t < 0) {
		return false; // Plane behind ray's origin, no intersection
	}

	// Check if t is outside min and max distance
	if(t <= minDistance || t >= maxDistance) {
		return false;
	}

	// Set raycast hit
	raycastHit.distance = t;
	raycastHit.point = ray.GetPoint(t);
	raycastHit.normal = glm::normalize(this->normal);
	raycastHit.material = GetMaterial();

	return true;
}
