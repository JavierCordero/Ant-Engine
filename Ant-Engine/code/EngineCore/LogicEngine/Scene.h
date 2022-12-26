//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <vector>
#include "..\..\Logic\Camera\Camera.h"
#include "..\..\EngineCore\LogicEngine\Entity.h"

class Map;
//-------------------------------------------------------------------------

class Scene
{

public:
	Scene();
	virtual ~Scene();

	void Init();
	Camera* GetCamera() { return camera; };
	Camera* SetCamera(Camera* _camera) { camera = _camera; }

	void EraseSceneEntity(Entity* _erasedEntity);

	std::vector<Entity*>& GetSceneObjects() { return m_SceneObjects; };

protected:
	Map* m_SceneMap = nullptr;

private:
	Camera* camera = nullptr;

	std::vector<Entity*> m_SceneObjects;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

