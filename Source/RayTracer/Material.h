#pragma once

#include "Color.h"
#include "Ray.h"

class Material {
	public:
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const = 0;
		virtual color3_t GetEmissive() const {return color3_t(0);}
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

class Dielectric : public Material {
	public:
		Dielectric(const glm::vec3& albedo, float index) {this->albedo = albedo; this->index = index;}
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const override;

	protected:
		glm::vec3 albedo = glm::vec3(1);
		float index = 1.0f; // Refraction index
};

class Emissive : public Material {
	public:
		Emissive(const color3_t& albedo, float intensity = 1.0f) {this->albedo = albedo; this->intensity = intensity;}

		bool Scatter(const ray_t& ray, const raycastHit_t& hit, color3_t& color, ray_t& scattered) const override {return false;}
		color3_t GetEmissive() const override {return this->albedo * this->intensity;}

	private:
		color3_t albedo = color3_t(1);
		float intensity = 1.0f;
};