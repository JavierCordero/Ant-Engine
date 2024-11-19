//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <freeglut.h>
#include <vector>
#include "..\..\Logic\Camera\Camera.h"
#include "..\..\EngineCore\LogicEngine\Entity.h"
#include "Light.h"

class Map;
class Interface;
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
	void RenderInterface();
	virtual void Update(float _elapsedTime);
	virtual void HandleInput(unsigned char _key);

	void EraseSceneEntity(Entity* _erasedEntity);

	std::vector<Entity*>& GetSceneObjects() { return m_SceneObjects; };
	std::vector<Interface*>& GetInterfaceObjects() { return m_InterfaceObjects; };

protected:
	Map* m_SceneMap = nullptr;

	Light m_Light;

private:
	Camera* m_SceneCamera = nullptr;

	std::vector<Entity*> m_SceneObjects;
	std::vector<Interface*> m_InterfaceObjects;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

