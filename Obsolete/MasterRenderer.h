#pragma once

#include "StaticShader.h"
#include "EntityRenderer.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"
#include "TexturedModel.h"
#include "TerrainTexture.h"
#include "TerrainTexturePack.h"
#include "Loader.h"
#include "Entity.h"
#include "Terrain.h"
#include "OBJLoader.h"
#include <iostream>
#include <map>
#include <glm/glm.hpp>

class MasterRenderer
{
public:
	MasterRenderer();
	void render(Light* light, Camera* camera);
	void processEntity(Entity* entity);
	void processTerrain(Terrain* terrain);
	void clean();
	//Temp
	std::list<Entity*> genEntities();
	std::list<Terrain*> genTerrains();
	TexturedModel* genTexturedModel(const char* name);
private:
	StaticShader* staticShader;
	TerrainShader* terrainShader;
	Loader* loader = new Loader();
	EntityRenderer* entityRenderer;
	TerrainRenderer* terrainRenderer;
	std::map<TexturedModel*, std::list<Entity*>> Entities;
	std::list<Terrain*> Terrains;
	glm::vec3 skyColor;
	void prepare();
};

