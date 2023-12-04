#include "Material.h"

#include "MathUtils.h"
#include "Random.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const {
	glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
	glm::vec3 direction = glm::normalize(target - hit.point);

	scattered = ray_t(hit.point, direction);
	color = this->albedo;

	return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const {
	glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

	// Set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
	// A mirror has a fuzz value of 0 and a diffused metal surface has a higher value
	scattered = ray_t(hit.point, reflected + randomInUnitSphere() * fuzz);
	color = this->albedo;

	// Make sure that reflected ray is going away from surface normal (dot product > 0, angle between vectors < 90 degrees)
	return (dot(scattered.direction, hit.normal) > 0);
}