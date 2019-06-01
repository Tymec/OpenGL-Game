#pragma once

#include "TexturedModel.h"
#include <glm/glm.hpp>

class Entity
{
public:
	Entity(TexturedModel* texturedModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void move(float dx, float dy, float dz);
	void rotate(float rx, float ry, float rz);
	void rescale(float sx, float sy, float sz);
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	void setPositionY(float dy);
	TexturedModel* getTexturedModel();
private:
	TexturedModel* texturedModel;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

