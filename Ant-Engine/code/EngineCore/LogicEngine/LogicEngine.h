#pragma once

#include "..\RenderEngine\RenderLib.h"
#include "..\..\Logic\Camera\Camera.h"
#include "..\..\Logic\Scenes\Scene.h"
#include "Entity.h"
#include <vector>
#include <string>

struct Text3D {
	glm::vec3 position;
	glm::vec3 color;
	std::string text;
};

static class LogicLib
{
public:

	static void Init();
	static void Update(double elapsedTime);
	static void PostUpdate(double elapsedTime);

	static void Spawn(Entity* _ent) { spawnEntities.push_back(_ent); }
	static void Destroy(Entity* _ent);

	static std::vector<Text3D> text3D;
	static std::vector<Entity*> destroyEntities;
	static std::vector<Entity*> spawnEntities;

};

