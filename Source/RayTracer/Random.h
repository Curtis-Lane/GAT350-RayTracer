#pragma once

#include <cstdlib>
#include <utility>

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