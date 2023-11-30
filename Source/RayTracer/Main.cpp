#include <iostream>

#include "Renderer.h"
#include "Material.h"
#include "Canvas.h"
#include "Random.h"
#include "Scene.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;

	seedRandom(static_cast<unsigned int>(time(nullptr)));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("GAT350-RayTracing", 400, 300);

	Canvas canvas = Canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float) canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 70.0f, aspectRatio);

	Scene scene; // Sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// Create material
	std::shared_ptr<Lambertian> material = std::make_shared<Lambertian>(color3_t(1, 0, 0));

	bool quit = false;
	while(!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
				}
				break;
		}

		canvas.Clear(color4_t(0, 0, 0, 1));
		scene.Render(canvas);
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}