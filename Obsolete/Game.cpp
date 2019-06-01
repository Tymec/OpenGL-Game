#include "Game.h"

Game::Game() 
{
	this->display = new DisplayManager(1280, 720, "OpenGLVS");
	this->renderer = new MasterRenderer();
	this->input = new InputManager(this);
}

void Game::loop() 
{
	this->terrains = this->renderer->genTerrains();
	setup();
	this->entities = this->renderer->genEntities();
	entities.push_back(this->player);

	while (!display->shouldClose()) 
	{
		this->display->pollEvents();
		this->player->movePlayer(display->getDelta());
		this->camera->move();
		for (Entity* entity : entities) 
		{
			this->renderer->processEntity(entity);
		}
		for (Terrain* terrain : terrains) 
		{
			this->renderer->processTerrain(terrain);
		}
		this->renderer->render(this->light, this->camera);
		this->camera->clear();
		this->display->update();
	}
	this->renderer->clean();
	this->display->terminate();
}

void Game::setup() 
{
	glm::vec3 lightPosition(20000, 20000, 20000);
	glm::vec3 lightColor(1, 1, 1);

	this->light = new Light(lightPosition, lightColor);
	this->player = new Player(
		renderer->genTexturedModel("bobo"),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0.5, 0.5, 0.5)
	);
	this->camera = new Camera(this->player);
}

Player* Game::getPlayer() { return this->player; }
Camera* Game::getCamera() { return this->camera; }
DisplayManager* Game::getDisplay() { return this->display; }