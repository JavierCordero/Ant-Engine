#pragma once

#include "Scene.h"
class Map
{
public:

	Map(Scene* _mainScene);
	virtual ~Map();

	void InitNormalMap();
	void InitLifeGenerationMap();

private:
	Scene* mainScene;
	Entity* antHomeWalls[100][100];
};

