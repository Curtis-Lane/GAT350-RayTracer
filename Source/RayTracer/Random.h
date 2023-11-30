#pragma once

#include <cstdlib>
#include <utility>

#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>

inline void seedRandom(unsigned int seed) {
	std::srand(seed);
}

inline float random01() {
	return std::rand() / (float) RAND_MAX;
}

inline float random(float min, float max) {
	if(min > max) {
		std::swap(min, max);
	}

	return (random01() * (max - min)) + min;
}

inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max) {
	return glm::vec3(
		random(min.x, max.x),
		random(min.y, max.y),
		random(min.z, max.z)
	);
}

inline glm::vec3 randomInUnitSphere() {
	glm::vec3 v = glm::vec3(1);
	while(glm::length2(v) >= 1.0f) {
		v = random(glm::vec3(-1), glm::vec3(1));
	}

	return v;
}