#include "Scene.h"
#include <iostream>
#include "..\..\EngineCore\RenderEngine\RenderLib.h"

#include "Map.h"

#ifdef _DEBUG
#include "..\..\EngineCore\checkML.h"
#endif // _DEBUG

Scene::Scene()
{
}

//-------------------------------------------------------------------------

void Scene::Init()
{
	// Camera position, view volume and projection
	camera = new Camera(0, 0, RenderLib::GetWindowWidth(), RenderLib::GetWindowHeight());
	camera->Set2D();

	m_SceneMap->InitializeMap();
}
//-------------------------------------------------------------------------

Scene::~Scene()
{
	delete camera;
	camera = nullptr;

	for (auto entity : m_SceneObjects) {
		if (entity != nullptr) {
			delete entity;
			entity = nullptr;
		}
	}

	if (m_SceneMap != nullptr)
		delete m_SceneMap;

	m_SceneObjects.clear();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Scene::EraseSceneEntity(Entity* _erasedEntity)
{
	auto it = std::find(m_SceneObjects.begin(), m_SceneObjects.end(), _erasedEntity);

	if (it != m_SceneObjects.end()) {
		int index = it - m_SceneObjects.begin();
		m_SceneObjects.erase(m_SceneObjects.begin() + index);
	}
}
