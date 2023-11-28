#include <iostream>

#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;

	seedRandom(static_cast<unsigned int>(time(nullptr)));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("GAT350-RayTracing", 400, 300);

	Canvas canvas = Canvas(400, 300, renderer);

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				quit = true;
				break;
		}

		canvas.Clear(color4_t(0, 0, 0, 1));
		for(int i = 0; i < 1000; i++) {
			canvas.DrawPoint(glm::ivec2((int) random(0, 400), (int) random(0, 300)), color4_t(random01(), random01(), random01(), random01()));
		}
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}