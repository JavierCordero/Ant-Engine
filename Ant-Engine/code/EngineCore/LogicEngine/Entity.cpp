#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "..\EngineCore.h"
#include "ObjectLoader.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG
//-------------------------------------------------------------------------

Entity::Entity(glm::vec3 _position, glm::vec3 _size)
	: Object(_position, _size)
{
	//m_Mesh = nullptr;
}

Entity::Entity(glm::vec3 _position, glm::vec3 _size, const char* _meshName) 
	: Object(_position, _size)
{
	ObjectLoader::LoadOBJFile(_meshName, this, m_Meshes);

	for (Mesh* m : m_Meshes)
	{
		m->SetScale(_size);
		m->SetColors(glm::vec4(0, 0, 0, 1));
	}
}

Entity::~Entity()
{
	for (auto& item : m_EntityComponents)
		delete[] item;

	m_EntityComponents.clear();
}

void Entity::Render(glm::dmat4 const& modelViewMat)
{ 
	if (isVisible) {
		for each (Component * component in m_EntityComponents)
		{
			component->Render(modelViewMat);
		}

		SetModelViewMat(modelViewMat);
	}

	for (Mesh* m : m_Meshes)
	{
		if (m != nullptr)
		{
			if (m_Texture.GetTextureID() != 0)
			{
				glEnable(GL_REPEAT);
				m_Texture.Bind();
			}

			glLineWidth(2);
			m->Draw(modelViewMat);
			glLineWidth(1);

			if (m_Texture.GetTextureID() != 0)
			{
				m_Texture.Unbind();
				glDisable(GL_REPEAT);
			}
		}
	}
}

void Entity::Update(double timeElapsed) 
{
	Object::Update(timeElapsed);

	for each (Component* component in m_EntityComponents)
	{
		component->Update(timeElapsed);
	}
}


void Entity::PostUpdate(double elapsedTime) {
	Object::PostUpdate(elapsedTime);

	for each (Component * component in m_EntityComponents)
	{
		component->PostUpdate(elapsedTime);
	}
}

void Entity::Destroy() {
	EngineCore::GetScene()->EraseSceneEntity(this);
}