#pragma once

#include <memory>
#include <vector>

#include "Object.h"
#include "Camera.h"
#include "Color.h"

class Scene {
	public:
		Scene(int depth = 5) {this->depth = depth;}
		Scene(int depth, const color3_t& topColor, const color3_t& bottomColor) {
			this->depth = depth;
			this->topColor = topColor;
			this->bottomColor = bottomColor;
		}

		void Render(class Canvas& canvas, int numSamples);
		color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);
		void AddObject(std::unique_ptr<Object> object) {this->objects.push_back(std::move(object));}

		void SetCamera(std::shared_ptr<Camera> camera) {this->camera = camera;}

	private:
		std::vector<std::unique_ptr<Object>> objects;
		std::shared_ptr<Camera> camera;

		int depth = 5;
		color3_t topColor = color3_t(1);
		color3_t bottomColor = color3_t(0);
};