#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(StaticShader* shader)
{
	this->shader = shader;
	this->shader->start();
	this->shader->loadProjectionMatrix();
	this->shader->stop();
}

void EntityRenderer::render(std::map<TexturedModel*, std::list<Entity*>> entities)
{	
	std::vector<TexturedModel*> entityKeys = extract_keys(entities);
	for (TexturedModel* model : entityKeys) 
	{
		prepareTexturedModel(model);
		std::list<Entity*> batch = entities.find(model)->second;
		for (Entity* entity : batch) 
		{
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, model->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void EntityRenderer::prepareTexturedModel(TexturedModel* model)
{
	Model* data = model->getModel();
	glBindVertexArray(data->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture* texture = model->getTexture();
	if (model->hasTransparency()) {
		this->disableCulling();
	}
	this->loadFakeLightningBool(model->useFakeLightning());
	this->shader->loadShine(texture->getShineDamp(), texture->getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTEX());
}

void EntityRenderer::unbindTexturedModel()
{
	this->enableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity* entity)
{
	glm::mat4 modelMatrix = createModelMatrix(entity);
	loadModelMatrix(modelMatrix);
}

glm::mat4 EntityRenderer::createModelMatrix(Entity* entity) 
{
	glm::mat4 matrix = glm::mat4(1.0f);
	glm::vec3 entityPosition = entity->getPosition();
	glm::vec3 entityRotation = entity->getRotation();
	glm::vec3 entityScale = entity->getScale();
	matrix = glm::translate(matrix, entityPosition);
	matrix = glm::rotate(matrix, glm::radians(entityRotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(entityRotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(entityRotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, entityScale);
	return matrix;
}

void EntityRenderer::loadModelMatrix(glm::mat4 modelMatrix)
{
	GLuint location = this->shader->getUniformLocationDictionary().find("modelMatrixLocation")->second;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void EntityRenderer::enableCulling() 
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void EntityRenderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void EntityRenderer::loadFakeLightningBool(bool fakeLightning)
{	
	GLuint location = this->shader->getUniformLocationDictionary().find("fakeLightningLocation")->second;
	float value = 0.0f;
	if (fakeLightning) {
		value = 1.0f;
	}
	glUniform1f(location, value);
}

std::vector<TexturedModel*> EntityRenderer::extract_keys(std::map<TexturedModel*, std::list<Entity*>> const& input_map) 
{
	std::vector<TexturedModel*> retval;
	for (auto const& element : input_map) 
	{
		retval.push_back(element.first);
	}
	return retval;
}