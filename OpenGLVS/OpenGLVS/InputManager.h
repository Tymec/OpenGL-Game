#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DisplayManager.h"
#include "Player.h"
#include "Camera.h"

class Game;

class InputManager
{
public:
	InputManager(Game* game);
	struct Information {
		bool wireframe = false;
		float prevMouseX = 0;
		float prevMouseY = 0;
	};
	Information* info;
private:
	Game* game;
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};