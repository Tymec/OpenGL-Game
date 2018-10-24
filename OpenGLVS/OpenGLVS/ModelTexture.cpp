#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint TEX)
{
	this->TEX = TEX;
}

void ModelTexture::setShine(float shineDamp, float reflectivity)
{
	this->shineDamp = shineDamp;
	this->reflectivity = reflectivity;
}

float ModelTexture::getShineDamp()
{
	return this->shineDamp;
}

float ModelTexture::getReflectivity()
{
	return this->reflectivity;
}

GLuint ModelTexture::getTEX() 
{
	return this->TEX;
}
