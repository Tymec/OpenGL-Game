#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

struct Bounds
{
	glm::vec3 min;
	glm::vec3 max;
	std::vector<float> boundVertices;
	std::vector<float> boundNormals;
	std::vector<float> boundUVs;
	std::vector<uint32_t> boundIndices;

	void setBounds(glm::vec3 min, glm::vec3 max)
	{
		this->min = min;
		this->max = max;
	}
};

class Model
{
public:
	Model(GLuint VAO, int vertexCount);
	GLuint getVAO();
	int getVertexCount();
	void setHeight(float height);
	float getHeight();
	void setBounds(glm::vec3 min, glm::vec3 max);
	std::vector<float> getBoundVertices();
	std::vector<float> getBoundNormals();
	std::vector<float> getBoundUVs();
	std::vector<uint32_t> getBoundIndices();
private:
	GLuint VAO;
	int vertexCount;
	float height;
	struct Bounds bounds;
	Bounds bnds;
	void genBoundBox();
};
