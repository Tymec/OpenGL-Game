#include "Entity.h"

Entity::Entity(TexturedModel* texturedModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->texturedModel = texturedModel;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void Entity::move(float dx, float dy, float dz) 
{
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void Entity::rotate(float rx, float ry, float rz) 
{
	this->rotation.x += rx;
	this->rotation.y += ry;
	this->rotation.z += rz;
}

void Entity::rescale(float sx, float sy, float sz) 
{
	this->scale.x += sx;
	this->scale.y += sy;
	this->scale.z += sz;
}

glm::vec3 Entity::getPosition()
{
	return this->position;
}

glm::vec3 Entity::getRotation()
{
	return this->rotation;
}

glm::vec3 Entity::getScale()
{
	return this->scale;
}

void Entity::setPositionY(float dy)
{
	this->position.y = dy;
}

TexturedModel* Entity::getTexturedModel() 
{ 
	return this->texturedModel; 
}