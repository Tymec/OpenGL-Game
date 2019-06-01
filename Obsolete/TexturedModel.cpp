#include "TexturedModel.h"

TexturedModel::TexturedModel(Model* model, ModelTexture* texture)
{
	this->model = model;
	this->texture = texture;
	this->_hasTransparency = false;
	this->_useFakeLightning = false;
}

Model * TexturedModel::getModel()
{
	return this->model;
}

ModelTexture * TexturedModel::getTexture()
{
	return this->texture;
}

void TexturedModel::hasTransparency(bool has) 
{
	this->_hasTransparency = has;
}

bool TexturedModel::hasTransparency()
{
	return this->_hasTransparency;
}

void TexturedModel::useFakeLightning(bool use)
{
	this->_useFakeLightning = use;
}

bool TexturedModel::useFakeLightning() 
{
	return this->_useFakeLightning;
}