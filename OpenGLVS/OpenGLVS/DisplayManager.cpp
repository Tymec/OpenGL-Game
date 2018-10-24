#include "DisplayManager.h"



DisplayManager::DisplayManager(int width, int height, const char* title)
{	
	if (!glfwInit()) 
	{
		return;
	}
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	setHints();
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);
	glfwSwapInterval(0);
	if (!glewInit()) 
	{
		return;
	}
	glewExperimental = GL_TRUE;
}

bool DisplayManager::shouldClose() 
{
	return glfwWindowShouldClose(window); 
}

void DisplayManager::terminate() 
{
	glfwTerminate();
}

void DisplayManager::setHints() 
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void DisplayManager::updateDelta() 
{
	double currentTime = glfwGetTime() * 1000.0f;
	this->delta = (currentTime - this->delta_lastTime) / 1000.0f;
	this->delta_lastTime = currentTime;
}

double DisplayManager::getDelta() { return this->delta; }

void DisplayManager::displayFPS() 
{
	float currentTime = glfwGetTime();
	nbFrames++;
	if ((currentTime - fps_lastTime) > 1.0) 
	{
		float fps = nbFrames;
		float ms = 1000 / nbFrames;
		char title[50];
		sprintf_s(title, 50, "%.0f fps | %.0f ms - OpenGLVS", fps, ms);
		glfwSetWindowTitle(window, title);
		nbFrames = 0;
		fps_lastTime += 1.0;
	}
}

void DisplayManager::pollEvents() 
{
	glfwPollEvents();
}

void DisplayManager::update() 
{
	displayFPS();
	updateDelta();
	glfwSwapBuffers(window);
}