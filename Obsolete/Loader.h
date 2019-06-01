#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <GL/glew.h>
#include "Model.h"
#include <SOIL2/SOIL2.h>

class Loader
{
public:
	Loader();
	Model* load(std::vector<float> verticesArray, std::vector<float> UVsArray, std::vector<float> normalsArray, std::vector<uint32_t> indicesArray);
	GLuint setupTextures(const char* texture_name);
	void clean();

private:
	std::list<GLuint> vaoList;
	std::list<GLuint> vboList;
	std::list<GLuint> texList;

	GLuint createVAO();
	void unbindVAO();
	void bindIndices(std::vector<uint32_t> data);
	void storeData(int index, int size, std::vector<float> data);
};

