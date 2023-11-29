#include "Camera.h"

#include "MathUtils.h"

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	this->eye = eye;

	// Set the camera axis vectors (forward, right, up)
	// Foward vector (eye <- target)
	this->forward = glm::normalize(eye - target);

	// Use cross product to create vectors
	// Right = up X forward
	this->right = glm::normalize(cross(up, forward));

	// Up = forward X right
	this->up = cross(forward, right);

	CalculateViewPlane();
}

void Camera::CalculateViewPlane() {
	// Convert fov angle (degress) to radians
	float theta = glm::radians(this->fov);

	// Calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = halfHeight * 2;
	float width = height * this->aspectRatio;

	// Calculate horizontal vector (right vector * width)
	this->horizontal = right * width;
	// Calculate vertical vector (up vector * height)
	this->vertical = up * height;
	// Calculate lower left location (origin)
	this->lowerLeft = this->eye - (horizontal * 0.5f) - (vertical * 0.5f) - this->forward;
}

ray_t Camera::GetRay(const glm::vec2& point) const {
	ray_t ray;

	// The ray origin is the camera eye
	ray.origin = this->eye;
	// Calculate direction from point
	ray.direction = this->lowerLeft + (horizontal * point.x) + (vertical * point.y) - this->eye;

	return ray;
}
