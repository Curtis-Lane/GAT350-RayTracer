#include "Canvas.h"

#include <SDL.h>

#include "Renderer.h"

Canvas::Canvas(int width, int height, const Renderer& renderer) {
	this->size = glm::ivec2(width, height);
	this->texture = SDL_CreateTexture(renderer.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	this->buffer.resize(width * height);
}

Canvas::~Canvas() {
	if(this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}
}

void Canvas::Update() {
	SDL_UpdateTexture(this->texture, NULL, this->buffer.data(), this->size.x * sizeof(rgba_t));
}

void Canvas::Clear(const color4_t& color) {
	rgba_t rgba = ColorToRGBA(color);

	std::fill(this->buffer.begin(), this->buffer.end(), rgba);
}

void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color) {
	if((point.x < 0 || point.x >= size.x) || (point.y < 0 || point.y >= size.y)) {
		return;
	}
	this->buffer[point.x + (point.y * this->size.x)] = ColorToRGBA(color);
}
