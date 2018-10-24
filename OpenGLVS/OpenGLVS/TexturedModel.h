#pragma once

#include "Model.h"
#include "ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(Model* model, ModelTexture* texture);

	Model* getModel();
	ModelTexture* getTexture();
	void hasTransparency(bool has);
	bool hasTransparency();
	void useFakeLightning(bool use);
	bool useFakeLightning();
private:
	Model* model;
	ModelTexture* texture;
	float shineDamp;
	float reflectivity;
	bool _hasTransparency;
	bool _useFakeLightning;
};

