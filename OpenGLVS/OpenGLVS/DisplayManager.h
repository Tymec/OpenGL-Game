#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class DisplayManager
{
public:
	DisplayManager(int width, int height, const char* title);
	bool shouldClose();
	double getDelta();
	void update();
	void pollEvents();
	void terminate();
private:
	GLFWwindow* window;
	int nbFrames;
	float fps_lastTime = 0;
	double delta_lastTime = 0;
	double delta = 0.0f;
	void setHints();
	void displayFPS();
	void updateDelta();
};

