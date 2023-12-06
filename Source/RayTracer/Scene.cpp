#include "Scene.h"

#include <iostream>
#include <iomanip>

#include "MathUtils.h"
#include "Random.h"
#include "Canvas.h"

void Scene::Render(Canvas& canvas, int numSamples, int depth) {
	// Cast ray for each point (pixel) on the canvas
	for(int y = 0; y < canvas.GetSize().y; y++) {
		for(int x = 0; x < canvas.GetSize().x; x++) {
			// Create vec2 pixel from canvas x, y
			glm::vec2 pixel = glm::vec2(x, y);

			// Set initial color
			color3_t color = color3_t(0);
			// Cast a ray for each sample, accumulate color value for each sample
			// Each ray will have a random offset
			for(int i = 0; i < numSamples; i++) {
				// Get normalized (0 - 1) point coordinates from pixel
				// Add random x and y offset (0-1) to each pixel
				glm::vec2 point = (pixel + glm::vec2(random01(), random01())) / (glm::vec2) canvas.GetSize();
				// Flip y
				point.y = 1.0f - point.y;

				// Create ray from camera
				ray_t ray = camera->GetRay(point);

				// Cast ray into scene
				// Add color value from trace
				raycastHit_t raycastHit;
				color += Trace(ray, 0, 100, raycastHit, depth);
			}

			// Draw color to canvas point (pixel)
			// Get average color (average = (color + color + color) / number of samples)
			color /= numSamples;
			canvas.DrawPoint(pixel, color4_t(color, 1));
		}
		std::cout << std::setprecision(2) << std::setw(5) << (((float) y / canvas.GetSize().y) * 100) << "%\n";
	}
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth) {
	bool rayHit = false;
	float closestDistance = maxDistance;

	// Check if scene objects are hit by ray
	for(auto& object : this->objects) {
		// When checking objects don't include objects farther than closest hit (starts at max distance)
		if(object->Hit(ray, minDistance, closestDistance, raycastHit)) {
			rayHit = true;
			// Set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;
		}
	}

	// If ray hit object, scatter (bounce) ray and check for next hit
	if(rayHit) {
		ray_t scattered;
		color3_t color;

		// Check if maximum depth (number of bounces) is reached, get color from material and scattered ray
		if(depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered)) {
			// Recursive function, call self and modulate (multiply) colors of depth bounces
			return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
		} else {
			// Reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
			return raycastHit.material->GetEmissive();
		}
	}
	
	// If ray didn't hit, return scene sky color
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	color3_t color = lerp(this->bottomColor, this->topColor, t);

	return color;
}