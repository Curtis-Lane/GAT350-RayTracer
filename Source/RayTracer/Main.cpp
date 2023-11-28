#include <iostream>

#include "Renderer.h"
#include "Random.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;

	seedRandom(static_cast<unsigned int>(time(nullptr)));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("GAT350-RayTracing", 400, 300);

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				quit = true;
				break;
		}
	}

	renderer.Shutdown();

	return 0;
}