#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
{	
	this->staticShader = new StaticShader();
	this->terrainShader = new TerrainShader();

	this->entityRenderer = new EntityRenderer(this->staticShader);
	this->terrainRenderer = new TerrainRenderer(this->terrainShader);

	this->skyColor = glm::vec3(0.5, 0.75, 0.9);
}

void MasterRenderer::prepare() 
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClearColor(this->skyColor.x, this->skyColor.y, this->skyColor.z, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::render(Light* light, Camera* camera)
{
	this->prepare();

	this->staticShader->start();
	this->staticShader->loadLight(light->getPosition(), light->getColor());
	this->staticShader->loadViewMatrix(camera);
	this->staticShader->loadSkyColor(this->skyColor);
	this->entityRenderer->render(this->Entities);
	this->staticShader->stop();

	this->terrainShader->start();
	this->terrainShader->loadLight(light->getPosition(), light->getColor());
	this->terrainShader->loadViewMatrix(camera);
	this->terrainShader->loadSkyColor(this->skyColor);
	this->terrainRenderer->render(this->Terrains);
	this->terrainShader->stop();

	this->Entities.clear();
	this->Terrains.clear();
}

void MasterRenderer::processEntity(Entity* entity)
{
	TexturedModel* entityModel = entity->getTexturedModel();
	auto batch = this->Entities.find(entityModel);
	if (batch != this->Entities.end()) 
	{
		batch->second.push_back(entity);
	}
	else
	{
		std::list<Entity*> newBatch;
		newBatch.push_back(entity);
		std::pair<TexturedModel*, std::list<Entity*>> newPair(entityModel, newBatch);
		Entities.insert(newPair);
	}
}

void MasterRenderer::processTerrain(Terrain* terrain)
{
	this->Terrains.push_back(terrain);
}

void MasterRenderer::clean() 
{
	this->loader->clean();
}

std::list<Entity*> MasterRenderer::genEntities() 
{
	std::list<Entity*> entities;
	OBJLoader obj;

	Model* treeModel = obj.loadModel("tree", this->loader);
	ModelTexture* treeTexture = new ModelTexture(this->loader->setupTextures("res\\tree.png"));
	treeTexture->setShine(10, 0);
	TexturedModel* tree = new TexturedModel(treeModel, treeTexture);

	Model* fernModel = obj.loadModel("fern", this->loader);
	ModelTexture* fernTexture = new ModelTexture(this->loader->setupTextures("res\\fern.png"));
	fernTexture->setShine(10, 0);
	TexturedModel* fern = new TexturedModel(fernModel, fernTexture);
	fern->hasTransparency(true);

	Model* grassModel = obj.loadModel("grassModel", this->loader);
	ModelTexture* grassTexture = new ModelTexture(this->loader->setupTextures("res\\grassTexture.png"));
	grassTexture->setShine(10, 0);
	TexturedModel* grass = new TexturedModel(grassModel, grassTexture);
	grass->hasTransparency(true);
	grass->useFakeLightning(true);

	for (int i = 0; i < 100; i++) 
	{
		int x = rand() % 500;
		int z = rand() % 500;
		Entity* treeEntity = new Entity(
			tree,
			glm::vec3(x, 0, z),
			glm::vec3(0, 0, 0),
			glm::vec3(3, 3, 3)
		);
		entities.push_back(treeEntity);

		x = rand() % 500;
		z = rand() % 500;
		Entity* fernEntity = new Entity(
			fern,
			glm::vec3(x, 0, z),
			glm::vec3(0, 0, 0),
			glm::vec3(1, 1, 1)
		);
		entities.push_back(fernEntity);

		x = rand() % 500;
		z = rand() % 500;
		Entity* grassEntity = new Entity(
			grass,
			glm::vec3(x, 0, z),
			glm::vec3(0, 0, 0),
			glm::vec3(1, 1, 1)
		);
		entities.push_back(grassEntity);
	}
	return entities;
}

std::list<Terrain*> MasterRenderer::genTerrains() 
{
	std::list<Terrain*> terrains;
	TerrainTexture* bgTexture = new TerrainTexture(this->loader->setupTextures("res\\grassy2.png"));
	TerrainTexture* rTexture = new TerrainTexture(this->loader->setupTextures("res\\mud.png"));
	TerrainTexture* gTexture = new TerrainTexture(this->loader->setupTextures("res\\grassFlowers.png"));
	TerrainTexture* bTexture = new TerrainTexture(this->loader->setupTextures("res\\path.png"));
	TerrainTexture* blendMap = new TerrainTexture(this->loader->setupTextures("res\\blendMap2.png"));
	TerrainTexturePack* texturePack = new TerrainTexturePack(bgTexture, rTexture, gTexture, bTexture);
	Terrain* terrain = new Terrain(0, 0, this->loader, texturePack, blendMap);
	terrains.push_back(terrain);
	terrain = new Terrain(-1, 0, this->loader, texturePack, blendMap);
	//terrains.push_back(terrain);
	terrain = new Terrain(0, -1, this->loader, texturePack, blendMap);
	//terrains.push_back(terrain);
	terrain = new Terrain(-1, -1, this->loader, texturePack, blendMap);
	//terrains.push_back(terrain);
	return terrains;
}

TexturedModel* MasterRenderer::genTexturedModel(const char* name) {
	OBJLoader obj;
	char textureBuffer[50];
	sprintf_s(textureBuffer, 50, "res\\%s.png", name);
	ModelTexture* modelTexture = new ModelTexture(this->loader->setupTextures(textureBuffer));
	modelTexture->setShine(10, 0);
	Model* model = obj.loadModel(name, this->loader);
	return new TexturedModel(model, modelTexture);
}