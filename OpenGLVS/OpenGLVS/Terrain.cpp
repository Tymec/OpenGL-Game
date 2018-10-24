#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader* loader, TerrainTexturePack* texturePack, TerrainTexture* blendMap)
{
	this->x = gridX * this->SIZE;
	this->z = gridZ * this->SIZE;
	this->texturePack = texturePack;
	this->blendMap = blendMap;
	this->model = generateTerrain(loader);
}

int Terrain::getX() { return this->x; }

int Terrain::getZ() { return this->z; }

TerrainTexturePack* Terrain::getTerrainTexturePack() { return this->texturePack; }

TerrainTexture* Terrain::getBlendMap() { return this->blendMap; }

Model* Terrain::getModel() { return this->model; }

Model* Terrain::generateTerrain(Loader* loader)
{
	int count = this->VERTEX_COUNT * this->VERTEX_COUNT;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> uvs(count * 2);
	std::vector<uint32_t> indices(6 * (this->VERTEX_COUNT - 1)*(this->VERTEX_COUNT - 1));
	int vertexPointer = 0;
	for (int i = 0; i < this->VERTEX_COUNT; i++)
	{
		for (int j = 0; j < this->VERTEX_COUNT; j++) 
		{
			vertices[vertexPointer * 3 + 0] = (float)j / ((float)this->VERTEX_COUNT - 1) * this->SIZE;
			vertices[vertexPointer * 3 + 1] = rand() % 2; /*TEMP*/
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)this->VERTEX_COUNT - 1) * this->SIZE;
			normals[vertexPointer * 3 + 0] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			uvs[vertexPointer * 2 + 0] = (float)j / (float)(this->VERTEX_COUNT - 1);
			uvs[vertexPointer * 2 + 1] = (float)i / (float)(this->VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < this->VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < this->VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz*this->VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz+1)*this->VERTEX_COUNT)+gx;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	Model* model = loader->load(vertices, uvs, normals, indices);
	return model;
}
