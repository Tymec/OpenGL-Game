#pragma once

#include "TerrainShader.h"
#include "Terrain.h"
#include "TerrainTexturePack.h"
#include <iostream>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader* shader);
	void render(std::list<Terrain*> terrains);
private:
	TerrainShader* shader;
	void prepareTerrain(Terrain* terrain);
	void unbindTexturedModel();
	glm::mat4 createModelMatrix(Terrain* terrain);
	void loadModelMatrix(glm::mat4 modelMatrix);
	void bindTextures(Terrain* terrain);
};

