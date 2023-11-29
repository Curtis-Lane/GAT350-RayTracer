#pragma once

#include <memory>

#include "Camera.h"
#include "Color.h"

class Scene {
	public:
		Scene() = default;
		Scene(const color3_t& topColor, const color3_t& bottomColor) {
			this->topColor = topColor;
			this->bottomColor = bottomColor;
		}

		void Render(class Canvas& canvas);
		color3_t Trace(const ray_t& ray);

		void SetCamera(std::shared_ptr<Camera> camera) {this->camera = camera;}

	private:
		std::shared_ptr<Camera> camera;

		color3_t topColor = color3_t(0);
		color3_t bottomColor = color3_t(1);
};