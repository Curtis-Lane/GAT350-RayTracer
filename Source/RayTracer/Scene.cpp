#include "Scene.h"

#include "MathUtils.h"
#include "Canvas.h"

void Scene::Render(Canvas& canvas) {
	// Cast ray for each point (pixel) on the canvas
	for(int y = 0; y < canvas.GetSize().y; y++) {
		for(int x = 0; x < canvas.GetSize().x; x++) {
			// Create vec2 pixel from canvas x, y
			glm::vec2 pixel = glm::vec2(x, y);
			// Get normalized (0 - 1) point coordinates from pixel
			glm::vec2 point = pixel / (glm::vec2) canvas.GetSize();
			// Flip y
			point.y = 1.0f - point.y;

			// Create ray from camera
			ray_t ray = camera->GetRay(point);

			// Cast ray into scene
			// Set color value from trace
			raycastHit_t raycastHit;
			color3_t color = Trace(ray, 0, 100, raycastHit);

			// Draw color to canvas point (pixel)
			canvas.DrawPoint(pixel, color4_t(color, 1));
		}
	}
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
	bool rayHit = false;
	float closestDistance = maxDistance;

	// Check if scene objects are hit by ray
	for(auto& object : this->objects) {
		// When checking objects don't include objects farther than closest hit (starts at max distance)
		if(object->Hit(ray, minDistance, maxDistance, raycastHit)) {
			rayHit = true;
			// Set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;
		}
	}

	// If ray hit object, scatter (bounce) ray and check for next hit
	if(rayHit) {
		ray_t scattered;
		color3_t color;

		if(raycastHit.material->Scatter(ray, raycastHit, color, scattered)) {
			return raycastHit.normal;
		} else {
			return color3_t(0);
		}
	}

	// If ray didn't hit, return scene sky color
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	color3_t color = lerp(this->bottomColor, this->topColor, t);

	return color;
}