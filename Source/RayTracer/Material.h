#pragma once

#include "Color.h"
#include "Ray.h"

class Material {
	public:
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const = 0;
};

class Lambertian : public Material {
	public:
		Lambertian(const color3_t& albedo) {this->albedo = albedo;}
		bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const override;

	protected:
		color3_t albedo;
};

class Metal : public Material {
	public:
		Metal(const color3_t& albedo, float fuzz) {this->albedo = albedo; this->fuzz = fuzz;}
		bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const override;

	protected:
		color3_t albedo = color3_t(0);
		float fuzz = 0.0f;
};