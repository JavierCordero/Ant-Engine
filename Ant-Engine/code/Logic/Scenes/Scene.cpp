#include "Scene.h"
#include "..\Entities\AntFarm\AntFarm.h"
#include "..\Entities\Food\Food.h"
#include "..\Entities\RGBAxis\RGBaxisEntity.h"
#include <iostream>
#include "..\..\EngineCore\RenderEngine\RenderLib.h"

#include "..\Entities\Map\Map.h"

#ifdef _DEBUG
#include "..\..\EngineCore\checkML.h"
#endif // _DEBUG


//-------------------------------------------------------------------------

void Scene::Init()
{
	// Camera position, view volume and projection
	camera = new Camera(0, 0, RenderLib::GetWindowWidth(), RenderLib::GetWindowHeight());
	camera->setAZ();
	//camera->set3D();

	//RGBAxisEntity* rgbaxisentity = new RGBAxisEntity(glm::vec3(0.0f, 0.0f, 0.0f), 500.0);
	//sceneObjects.push_back(rgbaxisentity);

	gameMap = new Map(this);
	gameMap->InitLifeGenerationMap();
	////gameMap->InitNormalMap();


	int numFoodPlaces = 10;
	int numFoodPerPlace = 200;

	for (int i = 0; i < numFoodPlaces; ++i) {

		glm::vec3 foodPlace = glm::vec3(-400 + rand() % 800, -400 + rand() % 800, 0);

		for (int j = 0; j < numFoodPerPlace; ++j) {
			sceneObjects.push_back(new Food(glm::vec3(foodPlace.x + -20 + rand() % 40, foodPlace.y + -20 + rand() % 40, 0), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(0.2f, 0.8, 0.2f)));
		}
	}

	AntFarm* antFarm = new AntFarm(glm::vec3(200, -175, 0), glm::vec3(140.0f, 140.0f, 140.0f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f), glm::vec3(550.0f, 00.0f, 100.0f));
	sceneObjects.push_back(antFarm);
	antFarm->Init(this);

	antFarm = new AntFarm(glm::vec3(-200, 10, 0), glm::vec3(140.0f, 140.0f, 140.0f), glm::vec4(0.5f, 0.0f, 0.5f, 1.0f), glm::vec3(550.0f, -100.0f, 100.0f));
	sceneObjects.push_back(antFarm);
	antFarm->Init(this);

	antFarm = new AntFarm(glm::vec3(0, 300, 0), glm::vec3(140.0f, 140.0f, 140.0f), glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), glm::vec3(550.0f, -200.0f, 100.0f));
	sceneObjects.push_back(antFarm);
	antFarm->Init(this);
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 

	delete camera;
	camera = nullptr;

	for (auto entity : sceneObjects) {
		if (entity != nullptr) {
			delete entity;
			entity = nullptr;
		}
	}

	if (gameMap != nullptr)
		delete gameMap;

	sceneObjects.clear();

	/*delete [] sceneObjects;

	for (int i = 0; i < sceneObjects.size(); i++) {

		std::cout << i << std::endl;

		if (sceneObjects[i] != nullptr) {
			delete sceneObjects[i];
			sceneObjects[i] = nullptr;
		}
	}*/

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
