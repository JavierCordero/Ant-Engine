#pragma once

#include "..\RenderEngine\RenderLib.h"
#include "..\..\Logic\Camera\Camera.h"
#include "..\LogicEngine\Scene.h"
#include "Entity.h"
#include <vector>
#include <string>

class ObjectLoader;

struct Text3D {
	glm::vec3 position;
	glm::vec3 color;
	std::string text;
};

static class LogicLib
{
public:

	static void Init();
	static void Update(double _elapsedTime);
	static void PostUpdate(double _elapsedTime);

	static void Spawn(Entity* _entity) { spawnEntities.push_back(_entity); }
	static void Destroy(Entity* _entity);

	static std::vector<Text3D> text3D;
	static std::vector<Entity*> destroyEntities;
	static std::vector<Entity*> spawnEntities;
};

