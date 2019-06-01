#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <GL/glew.h>
#include "TexturedModel.h"
#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

class StaticShader {
public:
	StaticShader(const char* vShaderPath = "shaders\\core.vert", const char* fShaderPath = "shaders\\core.frag");
	void start();
	void stop();
	void loadViewMatrix(Camera* camera);
	void loadProjectionMatrix();
	void loadShine(float shineDamp, float reflectivity);
	void loadLight(glm::vec3 position, glm::vec3 color);
	void loadSkyColor(glm::vec3 skyColor);
	std::map<const char*, GLuint> getUniformLocationDictionary();
private:
	GLuint Program;
	std::map<const char*, GLuint> uniformLocations;
	GLuint createProgram(const char* vShaderPath, const char* fShaderPath);
	std::map<const char*, GLuint> getAllUniformLocations();

	glm::mat4 createViewMatrix(Camera* camera);
	glm::mat4 createProjectionMatrix(float fov = 45.0f, float aspect = 16.0f / 9.0f, float near = 0.1f, float far = 1000.0f);
};