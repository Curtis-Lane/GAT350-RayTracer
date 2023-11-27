#include "Renderer.h"

#include <iostream>

bool Renderer::Initialize() {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown() {
	if(this->window != nullptr) {
		SDL_DestroyWindow(this->window);
	}
	if(this->renderer != nullptr) {
		SDL_DestroyRenderer(this->renderer);
	}

	SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height) {
	this->window = SDL_CreateWindow(title.c_str(), 50, 50, width, height, SDL_WINDOW_OPENGL);
	if(this->window == nullptr) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(this->renderer == nullptr) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	
	return true;
}
