#include "..\LogicEngine\LogicEngine.h"
#include <iostream>
#include <chrono>
#include "..\EngineCore.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

std::vector<Entity*> LogicLib::destroyEntities; //WOW! 
std::vector<Text3D> LogicLib::text3D;
std::vector<Entity*> LogicLib::spawnEntities;

void LogicLib::Init()
{
	std::cout << "Initializing Logic lib..." << '\n';
}

void LogicLib::Update(double elapsedTime)
{
	Scene* scene = EngineCore::GetScene();
	if (scene) {
		for (int i = 0; i < scene->sceneObjects.size(); ++i) {
			scene->sceneObjects[i]->Update(elapsedTime);
		}
	}
}

void LogicLib::PostUpdate(double elapsedTime)
{
	
	for (Entity* ent : destroyEntities) {
		ent->Destroy();
		delete ent;
		ent = nullptr;
	}
	destroyEntities.clear();
	
	
	Scene* scene = EngineCore::GetScene();

	if (scene) {
		for (Entity* ent : spawnEntities) {
			scene->sceneObjects.push_back(ent);
		}
	}

	if (scene) {
		for each (Entity * it in scene->sceneObjects)
		{
			it->PostUpdate(elapsedTime);
		}
		spawnEntities.clear();
	}
}

void LogicLib::Destroy(Entity* _ent)
{
	_ent->markedForDestroy = true;
	destroyEntities.push_back(_ent);
}
