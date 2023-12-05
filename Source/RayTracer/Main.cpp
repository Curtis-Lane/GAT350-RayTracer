#include <iostream>

#include "Renderer.h"
#include "Material.h"
#include "Canvas.h"
#include "Random.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Scene.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;

	seedRandom(static_cast<unsigned int>(time(nullptr)));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("GAT350-RayTracing", 400, 300);

	Canvas canvas = Canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float) canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0, 1, 8), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 70.0f, aspectRatio);

	Scene scene(20); // Sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// Create material
	std::shared_ptr<Lambertian> lambertian = std::make_shared<Lambertian>(color3_t(0, 0, 1));
	std::shared_ptr<Metal> metal = std::make_shared<Metal>(color3_t(1, 1, 1), 0.0f);

	{
		auto material = std::make_shared<Lambertian>(color3_t(0.2f));
		auto plane = std::make_unique<Plane>(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), material);
		scene.AddObject(std::move(plane));
	}

	/*
	// Create objects -> add to scene
	for(int i = 0; i < 10; i++) {
		auto material = (rand() % 2 == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(glm::vec3(random(0, 2), random(0, 2), random(0, 5)), random(0.25f, 1), material);
		scene.AddObject(std::move(sphere));
	}
	*/
				
	{
		auto material = std::make_shared<Lambertian>(color3_t(1, 0, 0));
		auto triangle = std::make_unique<Triangle>(glm::vec3(-3, 0, 2), glm::vec3(3, 0, 2), glm::vec3(0, 4, 2), material);
		scene.AddObject(std::move(triangle));
	}
	
	// Render scene
	canvas.Clear(color4_t(0, 0, 0, 1));
	scene.Render(canvas, 50);
	canvas.Update();

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

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}