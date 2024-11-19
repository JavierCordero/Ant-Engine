#include "Scene.h"
#include <iostream>
#include "..\..\EngineCore\RenderEngine\RenderLib.h"
#include "../../EngineCore/Interface/Interface.h"
#include "Map.h"
#include "../../../include/glm/gtc/matrix_transform.hpp"

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
	m_SceneCamera = new Camera(0, 0, RenderLib::GetWindowWidth(), RenderLib::GetWindowHeight());
	m_SceneCamera->Set2D();

	GetSceneObjects().push_back(m_SceneCamera);

	if (m_SceneMap != nullptr)
	{
		m_SceneMap->InitializeMap();
	}
}
//-------------------------------------------------------------------------

Scene::~Scene()
{
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

void Scene::Render()
{
	for each (Entity * it in GetSceneObjects())
	{
		it->Render(m_SceneCamera->getViewMat());
	}
}

void Scene::RenderInterface()
{
	glm::mat4 projection = glm::ortho(0, RenderLib::GetWindowWidth(), RenderLib::GetWindowHeight(), 0);
	for each (Interface * inter in GetInterfaceObjects())
	{
		inter->Render(projection);
	}
}

void Scene::Update(float _elapsedTime)
{
	for (int i = 0; i < GetSceneObjects().size(); ++i) {
		GetSceneObjects()[i]->Update(_elapsedTime);
	}
}

void Scene::HandleInput(unsigned char _key)
{
	for (int i = 0; i < GetSceneObjects().size(); ++i) {
		GetSceneObjects()[i]->RecieveInput(_key);
	}
}