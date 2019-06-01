#pragma once

#include <GL/glew.h>

class ModelTexture
{
public:
	ModelTexture(GLuint TEX);
	void setShine(float shineDamp, float reflectivity);
	float getShineDamp();
	float getReflectivity();
	GLuint getTEX();
private:
	GLuint TEX;
	float shineDamp;
	float reflectivity;
};

