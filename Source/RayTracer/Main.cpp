#include <iostream>

#include "Renderer.h"
#include "Material.h"
#include "Canvas.h"
#include "Random.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Scene.h"

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitSceneCornell(Scene& scene, const Canvas& canvas);

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;

	seedRandom(static_cast<unsigned int>(time(nullptr)));

	const int width = 400;
	const int height = 300;
	const int samples = 500;
	const int depth = 6;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("GAT350-RayTracing", width, height);

	Canvas canvas = Canvas(width, height, renderer);
	Scene scene = Scene(glm::vec3(1), glm::vec3(0.5f, 0.7f, 1.0f)); // Sky color could be set with the top and bottom color

	InitScene01(scene, canvas);
	
	// Render scene
	canvas.Clear(color4_t(0, 0, 0, 1));
	scene.Render(canvas, samples, depth);
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

void InitScene01(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / (float) canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0, 2, 10), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// Create objects -> add to scene
	for(int x = -10; x < 10; x++) {
		for(int z = -10; z < 10; z++) {
			std::shared_ptr<Material> material;

			// Create random material
			float r = random01();
			if(r < 0.3f) {
				material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3(random(0, 360), 1, 1)));
			} else if(r < 0.6f) {
				material = std::make_shared<Metal>(color3_t(random(0.5, 1.0f)), random(0, 0.5f));
			} else if(r < 0.9f) {
				material = std::make_shared<Dielectric>(color3_t(1), random(1.1f, 2.0f));
			} else {
				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3(random(0, 360), 1, 1)), 5.0f);
			}

			// Set random sphere radius
			float radius = random(0.2f, 0.3f);
			// Create sphere using random radius and material
			std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(glm::vec3(x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f)), radius, material);
			// Add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto mesh = std::make_unique<Mesh>(std::make_unique<Emissive>(color3_t(1), 5.0f));
	mesh->Load("Models/cube.obj", glm::vec3(0, 2.5f, -2.25f), glm::vec3(45, 45, 0));
	scene.AddObject(std::move(mesh));

	auto plane = std::make_unique<Plane>(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), std::make_shared<Lambertian>(color3_t(0.2f)));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / (float) canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0, 2, 10), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 2, 0), std::make_shared<Lambertian>(color3_t(0.2f)));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), std::make_shared<Lambertian>(color3_t(0.2f)));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_unique<Lambertian>(color3_t(0, 0, 1)));
	mesh->Load("Models/cube.obj", glm::vec3(0, 0.5f, 0), glm::vec3(0, 45, 0));
	scene.AddObject(std::move(mesh));
}

void InitSceneCornell(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / (float) canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0, 2, 10), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0), 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto whiteMaterial = std::make_shared<Lambertian>(color3_t(1));

	auto backWall = std::make_unique<Mesh>(whiteMaterial);
	backWall->Load("Models/quad.obj", glm::vec3(0, 2, 6.2));
	scene.AddObject(std::move(backWall));

	auto leftWall = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t(1, 0, 0)));
	leftWall->Load("Models/quad.obj", glm::vec3(-0.5, 2, 7.2), glm::vec3(0, 90, 0), glm::vec3(2, 1, 1));
	scene.AddObject(std::move(leftWall));

	auto rightWall = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t(0, 1, 0)));
	rightWall->Load("Models/quad.obj", glm::vec3(0.5, 2, 7.2), glm::vec3(0, -90, 0), glm::vec3(2, 1, 1));
	scene.AddObject(std::move(rightWall));

	auto floor = std::make_unique<Mesh>(whiteMaterial);
	floor->Load("Models/quad.obj", glm::vec3(0, 1.5, 6.7), glm::vec3(-90, 0, 0));
	scene.AddObject(std::move(floor));

	auto ceiling = std::make_unique<Mesh>(whiteMaterial);
	ceiling->Load("Models/quad.obj", glm::vec3(0, 2.5, 6.7), glm::vec3(90, 0, 0));
	scene.AddObject(std::move(ceiling));

	auto light = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t(1)));
	light->Load("Models/quad.obj", glm::vec3(0, 2.5, 6.7), glm::vec3(90, 0, 0), glm::vec3(0.25, 0.25, 1));
	scene.AddObject(std::move(light));

	auto cube = std::make_unique<Mesh>(whiteMaterial);
	cube->Load("Models/cube.obj", glm::vec3(0.2, 1.62, 7), glm::vec3(0, 60, 0), glm::vec3(0.25));
	scene.AddObject(std::move(cube));

	auto tallCube = std::make_unique<Mesh>(whiteMaterial);
	tallCube->Load("Models/cube.obj", glm::vec3(-0.2, 1.62, 6.8), glm::vec3(0, 30, 0), glm::vec3(0.25, 0.75, 0.25));
	scene.AddObject(std::move(tallCube));
}