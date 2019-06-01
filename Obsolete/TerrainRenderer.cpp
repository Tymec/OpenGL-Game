#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader* shader)
{
	this->shader = shader;
	this->shader->start();
	this->shader->loadProjectionMatrix();
	this->shader->connectTextureUnits();
	this->shader->stop();
}

void TerrainRenderer::render(std::list<Terrain*> terrains)
{
	for (Terrain* terrain : terrains) 
	{
		prepareTerrain(terrain);
		glm::mat4 modelMatrix = createModelMatrix(terrain);
		loadModelMatrix(modelMatrix);
		glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrain(Terrain* terrain)
{
	Model* data = terrain->getModel();
	glBindVertexArray(data->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bindTextures(terrain);
	this->shader->loadShine(1, 0);
}

void TerrainRenderer::bindTextures(Terrain* terrain) 
{
	TerrainTexturePack* texturePack = terrain->getTerrainTexturePack();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePack->getBackgroundTexture()->getTEX());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePack->getRedTexture()->getTEX());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturePack->getGreenTexture()->getTEX());

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturePack->getBlueTexture()->getTEX());

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain->getBlendMap()->getTEX());
}

void TerrainRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

glm::mat4 TerrainRenderer::createModelMatrix(Terrain* terrain)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(terrain->getX(), 0, terrain->getZ()));
	return matrix;
}

void TerrainRenderer::loadModelMatrix(glm::mat4 modelMatrix)
{
	GLuint location = this->shader->getUniformLocationDictionary().find("modelMatrixLocation")->second;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

