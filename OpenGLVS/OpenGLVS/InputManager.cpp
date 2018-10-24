#include "InputManager.h"
#include "Game.h"

InputManager::InputManager(Game* game)
{
	this->game = game;
	this->info = new Information;
	GLFWwindow* window = glfwGetCurrentContext();
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
}

void InputManager::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	void* ptr = glfwGetWindowUserPointer(window);
	InputManager* input = static_cast<InputManager*>(ptr);
	switch (action) {
	case GLFW_PRESS:
		switch (key) 
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			case GLFW_KEY_F:
				if (input->info->wireframe) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					input->info->wireframe = false;
				}
				else 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					input->info->wireframe = true;
				}
				break;
		}
		break;
	}
}

void InputManager::cursorCallback(GLFWwindow * window, double xpos, double ypos)
{
	void* ptr = glfwGetWindowUserPointer(window);
	InputManager* input = static_cast<InputManager*>(ptr);
	input->game->getCamera()->angleOffsetX = xpos - input->info->prevMouseX;
	input->game->getCamera()->pitchOffsetY = ypos - input->info->prevMouseY;
	input->info->prevMouseX = xpos;
	input->info->prevMouseY = ypos;
}

void InputManager::mouseCallback(GLFWwindow * window, int button, int action, int mods)
{
	void* ptr = glfwGetWindowUserPointer(window);
	InputManager* input = static_cast<InputManager*>(ptr);
	switch(action)
	{
		case GLFW_PRESS:
			switch (button)
			{
				case GLFW_MOUSE_BUTTON_RIGHT:
				case GLFW_MOUSE_BUTTON_LEFT:
					input->game->getCamera()->mouseButtonPressed = button;
					break;
			}
			break;
		case GLFW_RELEASE:
			input->game->getCamera()->mouseButtonPressed = -1;
			break;
	}
}

void InputManager::scrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
	void* ptr = glfwGetWindowUserPointer(window);
	InputManager* input = static_cast<InputManager*>(ptr);

	input->game->getCamera()->zoomOffsetY = yoffset;
}