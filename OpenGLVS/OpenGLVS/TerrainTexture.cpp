#include "TerrainTexture.h"

TerrainTexture::TerrainTexture(GLuint TEX)
{
	this->TEX = TEX;
}

GLuint TerrainTexture::getTEX() { return this->TEX; }