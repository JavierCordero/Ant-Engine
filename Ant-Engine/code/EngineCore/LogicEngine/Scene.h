//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <freeglut.h>
#include <vector>
#include "..\..\Logic\Camera\Camera.h"
#include "..\..\EngineCore\LogicEngine\Entity.h"
#include "Light.h"

class Map;
//-------------------------------------------------------------------------

class Scene
{

public:
	Scene();
	virtual ~Scene();

	void Init();
	Camera* GetCamera() { return m_SceneCamera; };
	Camera* SetCamera(Camera* _camera) { m_SceneCamera = _camera; }

	void Render();

	void EraseSceneEntity(Entity* _erasedEntity);

	std::vector<Entity*>& GetSceneObjects() { return m_SceneObjects; };

protected:
	Map* m_SceneMap = nullptr;

	Light m_Light;

private:
	Camera* m_SceneCamera = nullptr;

	std::vector<Entity*> m_SceneObjects;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

