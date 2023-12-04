#pragma once

#include "MathUtils.h"
#include "Random.h"
#include "Color.h"
#include "Ray.h"

class Material {
	public:
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const = 0;
};

class Lambertian : public Material {
	public:
		Lambertian(const color3_t& albedo) {this->albedo = albedo;}
		bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const override {
			//glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
			//glm::vec3 direction = glm::normalize(target - hit.point);
			//scattered = ray_t(hit.point, direction);
			color = this->albedo;
			return true;
		}

	protected:
		color3_t albedo;
};
/*
class Metal : public Material {
	public:
		Metal(const color3_t& albedo, float fuzz) {this->albedo = albedo; this->fuzz = fuzz;}
		bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const override {
			//

			//scattered = ray_t();
			color = this->albedo;

			return (dot(scattered.direction, hit.normal) > 0);
		}

	protected:
		color3_t albedo;
		float fuzz = 0.0f;
};
*/