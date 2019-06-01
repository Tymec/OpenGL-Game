#pragma once

#include <GL/glew.h>

class TerrainTexture
{
public:
	TerrainTexture(GLuint TEX);
	GLuint getTEX();
private:
	GLuint TEX;
};

