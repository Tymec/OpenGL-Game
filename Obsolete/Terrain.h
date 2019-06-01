#pragma once

#include <iostream>
#include <vector>
#include "Model.h"
#include "TerrainTexturePack.h"
#include "TerrainTexture.h"
#include "Loader.h"

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader* loader, TerrainTexturePack* texturePack, TerrainTexture* blendMap);
	int getX();
	int getZ();
	TerrainTexturePack* getTerrainTexturePack();
	TerrainTexture* getBlendMap();
	Model* getModel();
private:
	static const int SIZE = 800;
	static const int VERTEX_COUNT = 128;
	int x;
	int z;
	Model* model;
	TerrainTexturePack* texturePack;
	TerrainTexture* blendMap;
	Model* generateTerrain(Loader* loader);
};

