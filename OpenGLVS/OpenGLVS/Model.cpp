#include "Model.h"

Model::Model(GLuint VAO, int vertexCount)
{
	this->vertexCount = vertexCount;
	this->VAO = VAO;
}

int Model::getVertexCount() { return this->vertexCount; }

void Model::setHeight(float height) { this->height = height; }

float Model::getHeight() { return this->height; }

GLuint Model::getVAO() { return this->VAO; }

void Model::setBounds(glm::vec3 min, glm::vec3 max) 
{
	bnds.setBounds(min, max);
	this->genBoundBox();
}

void Model::genBoundBox()
{
	std::vector<glm::vec3> vertexVectors = 
	{
		glm::vec3(bnds.min.x, bnds.max.y, bnds.min.z),
		glm::vec3(bnds.max.x, bnds.max.y, bnds.min.z),
		bnds.min,
		glm::vec3(bnds.max.x, bnds.min.y, bnds.min.z),

		glm::vec3(bnds.min.x, bnds.max.y, bnds.max.z),
		bnds.max,
		glm::vec3(bnds.min.x, bnds.min.y, bnds.max.z),
		glm::vec3(bnds.max.x, bnds.min.y, bnds.max.z),
	};

	std::vector<uint32_t> indices =
	{
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> uvs = {
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	for (glm::vec3 vertex : vertexVectors)
	{
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);

		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
	}
	bnds.boundVertices = vertices;
	bnds.boundIndices = indices;
	bnds.boundNormals = normals;
	bnds.boundUVs = uvs;
}

std::vector<float> Model::getBoundVertices() { return bnds.boundVertices; }

std::vector<float> Model::getBoundNormals() { return bnds.boundNormals; }

std::vector<float> Model::getBoundUVs() { return bnds.boundUVs; }

std::vector<uint32_t> Model::getBoundIndices() { return bnds.boundIndices; }