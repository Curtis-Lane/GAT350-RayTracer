#pragma once

#include <vector>

#include "Color.h"

class Canvas {
	public:
		Canvas(int width, int height, const class Renderer& renderer);
		~Canvas();

		void Update();

		void Clear(const color4_t& color);
		void DrawPoint(const glm::ivec2& point, const color4_t& color);

		const glm::ivec2& GetSize() const {return size;}

		friend class Renderer;

	private:
		struct SDL_Texture* texture = nullptr;
		std::vector<rgba_t> buffer;

		glm::ivec2 size = glm::ivec2(0);
};