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
			color3_t color = Trace(ray);

			// Draw color to canvas point (pixel)
			canvas.DrawPoint(pixel, color4_t(color, 1));
		}
	}
}

color3_t Scene::Trace(const ray_t& ray) {
	glm::vec3 direction = glm::normalize(ray.direction);

	// Set scene sky color
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	color3_t color = lerp(this->bottomColor, this->topColor, t);

	return color;
}