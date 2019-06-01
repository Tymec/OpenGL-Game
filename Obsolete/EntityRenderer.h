#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include "StaticShader.h"
#include "Entity.h"
#include "TexturedModel.h"

class EntityRenderer
{
public:
	EntityRenderer(StaticShader* shader);
	void render(std::map<TexturedModel*, std::list<Entity*>> entities);
private:
	StaticShader* shader;
	void prepareTexturedModel(TexturedModel* model);
	void unbindTexturedModel();
	void prepareInstance(Entity* entity);
	glm::mat4 createModelMatrix(Entity* entity);
	void loadModelMatrix(glm::mat4 modelMatrix);
	void disableCulling();
	void enableCulling();
	void loadFakeLightningBool(bool fakeLightning);
	std::vector<TexturedModel*> extract_keys(std::map<TexturedModel*, std::list<Entity*>> const& input_map);
};

