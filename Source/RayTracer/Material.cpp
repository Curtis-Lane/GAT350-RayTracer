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

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const {
	glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);
	glm::vec3 refracted;

	glm::vec3 outNormal;
	float ni_over_nt;
	float cosine;

	// Ray hits inside of surface (ray -> | -> normal)
	// Ray is going out of object (ray direction is facing in the same direction of the surface normal)
	if(dot(ray.direction, hit.normal) > 0) {
		outNormal = -hit.normal;
		ni_over_nt = this->index;
		cosine = this->index * dot(ray.direction, hit.normal) / ray.direction.length();
	} else {
		// Ray hits outside of surface (ray -> | <- normal)
		// Ray is going into object (ray direction is facing in the opposite direction of the surface normal)
		outNormal = hit.normal;
		ni_over_nt = 1.0f / this->index;
		cosine = -dot(ray.direction, hit.normal) / ray.direction.length();
	}

	// Set the probability of the ray being reflected or refracted
	float reflectProbability = 1.0f;
	if(refract(ray.direction, outNormal, ni_over_nt, refracted)) {
		// Use schlick and cosine (angle) to determine if ray is reflected or refracted
		reflectProbability = schlick(cosine, this->index);
	}

	// Create reflected or refracted ray
	scattered = (random01() < reflectProbability) ? ray_t(hit.point, reflected) : ray_t(hit.point, refracted);
	color = this->albedo;

	return true;
}
