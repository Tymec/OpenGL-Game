#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(TerrainTexture* bgTexture, TerrainTexture* rTexture, TerrainTexture* gTexture, TerrainTexture* bTexture)
{
	this->bgTexture = bgTexture;
	this->rTexture = rTexture;
	this->gTexture = gTexture;
	this->bTexture = bTexture;
}

TerrainTexture* TerrainTexturePack::getBackgroundTexture()
{
	return this->bgTexture;
}

TerrainTexture* TerrainTexturePack::getRedTexture()
{
	return this->rTexture;
}

TerrainTexture* TerrainTexturePack::getGreenTexture()
{
	return this->gTexture;
}

TerrainTexture* TerrainTexturePack::getBlueTexture()
{
	return this->bTexture;
}
