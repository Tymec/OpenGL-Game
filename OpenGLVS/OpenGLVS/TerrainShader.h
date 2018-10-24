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

class TerrainShader {
public:
	TerrainShader(const char* vShaderPath = "shaders\\terrain.vert", const char* fShaderPath = "shaders\\terrain.frag");
	void start();
	void stop();
	void loadViewMatrix(Camera* camera);
	void loadProjectionMatrix();
	void loadShine(float damp, float reflectivity);
	void loadLight(glm::vec3 position, glm::vec3 color);
	void loadSkyColor(glm::vec3 skyColor);
	void connectTextureUnits();
	std::map<const char*, GLuint> getUniformLocationDictionary();
private:
	GLuint Program;
	std::map<const char*, GLuint> uniformLocations;
	GLuint createProgram(const char* vShaderPath, const char* fShaderPath);
	std::map<const char*, GLuint> getAllUniformLocations();
	glm::mat4 createViewMatrix(Camera* camera);
	glm::mat4 createProjectionMatrix(float fov = 45.0f, float aspect = 16.0f / 9.0f, float near = 0.1f, float far = 1000.0f);
};