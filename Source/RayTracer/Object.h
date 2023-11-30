#pragma once

#include <memory>

#include "Material.h"
#include "Ray.h"

class Object {
	public:
		Object() = default;
		Object(std::shared_ptr<Material> material) {this->material = material;}

		virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;

		Material* GetMaterial() {return this->material.get();}

	protected:
		std::shared_ptr<Material> material;
};