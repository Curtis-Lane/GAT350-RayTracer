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
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const override {
			color = this->albedo;
			return true;
		}

	protected:
		color3_t albedo;
};