#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Entity.h"
#include "TexturedModel.h"
#include "Terrain.h"
#include <glm/glm.hpp>

class Player : public Entity
{
public:
	Player(TexturedModel* texturedModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void movePlayer(double delta);
private:
	GLFWwindow* window;
	float currentSpeed;
	float currentTurnSpeed;
	float upwardSpeed;
	void checkForInput();
	bool isGrounded;
	struct Information {
		int MOVE_SPEED = 20;
		int TURN_SPEED = 160;
		int JUMP_FORCE = 30;
		int GRAVITY = -50;
		int TERRAIN_HEIGHT = 0;
	};
	Information* info;
};

