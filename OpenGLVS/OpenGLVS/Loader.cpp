#include "Loader.h"

Loader::Loader()
{

}

Model* Loader::load(std::vector<float> verticesArray, std::vector<float> UVsArray, std::vector<float> normalsArray, std::vector<uint32_t> indicesArray)
{
	GLuint VAO_ID = createVAO();
	bindIndices(indicesArray);
	storeData(0, 3, verticesArray);
	storeData(1, 2, UVsArray);
	storeData(2, 3, normalsArray);
	unbindVAO();
	return new Model(VAO_ID, indicesArray.size());
}

void Loader::bindIndices(std::vector<uint32_t> data)
{
	GLuint EBO_ID;
	glGenBuffers(1, &EBO_ID);
	vboList.push_back(EBO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), &data[0], GL_STATIC_DRAW);
}

void Loader::storeData(int index, int size, std::vector<float> data)
{
	GLuint VBO_ID;
	glGenBuffers(1, &VBO_ID);
	vboList.push_back(VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Loader::setupTextures(const char* texture_name)
{
	GLuint TEX_ID = SOIL_load_OGL_texture(texture_name, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS /*| SOIL_FLAG_MIPMAPS*/);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	texList.push_back(TEX_ID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->getSize(), texture->getSize(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->getData());
	return TEX_ID;
}

GLuint Loader::createVAO() 
{
	GLuint VAO_ID;
	glGenVertexArrays(1, &VAO_ID);
	vaoList.push_back(VAO_ID);
	glBindVertexArray(VAO_ID);
	return VAO_ID;
}

void Loader::clean() 
{
	for(GLuint vao:vaoList) 
	{
		glDeleteVertexArrays(1, &vao);
	}
	for (GLuint vbo : vboList) 
	{
		glDeleteBuffers(1, &vbo);
	}
	for (GLuint tex : texList) 
	{
		glDeleteTextures(1, &tex);
	}
}

void Loader::unbindVAO() 
{
	glBindVertexArray(0);
}
