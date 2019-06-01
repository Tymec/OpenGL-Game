#pragma once

#include "TerrainTexture.h"

class TerrainTexturePack
{
public:
	TerrainTexturePack(TerrainTexture* bgTexture, TerrainTexture* rTexture, TerrainTexture* gTexture, TerrainTexture* bTexture);
	TerrainTexture* getBackgroundTexture();
	TerrainTexture* getRedTexture();
	TerrainTexture* getGreenTexture();
	TerrainTexture* getBlueTexture();
private:
	TerrainTexture* bgTexture;
	TerrainTexture* rTexture;
	TerrainTexture* gTexture;
	TerrainTexture* bTexture;
};

