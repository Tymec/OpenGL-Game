#pragma once

#include <glm/glm.hpp>
#include "InputManager.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"
#include "Light.h"
#include "Camera.h"
#include "Player.h"

class Game
{
public:
	Game();
	void loop();
	Player* getPlayer();
	Camera* getCamera();
	DisplayManager* getDisplay();
private:
	Camera* camera;
	Light* light;
	Player* player;
	DisplayManager* display;
	InputManager* input;
	MasterRenderer* renderer;
	std::list<Entity*> entities;
	std::list<Terrain*> terrains;
	void setup();
};

