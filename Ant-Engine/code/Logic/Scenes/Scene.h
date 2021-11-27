//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <vector>
#include "..\Camera\Camera.h"
#include "..\..\EngineCore\LogicEngine\Entity.h"

class Map;
//-------------------------------------------------------------------------

class Scene
{

public:
	Scene() {};
	virtual ~Scene();

	void Init();
	Camera* GetCamera() { return camera; };
	Camera* SetCamera(Camera* _camera) { camera = _camera; }

	std::vector<Entity*> sceneObjects;	

private:

	Camera* camera = nullptr;
	Map* gameMap = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

