//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include "Object.h"
#include "Mesh.h"
#include <freeglut.h>
#include <glm.hpp>
#include "..\Texture\Texture.h"
#include "..\Texture\Material.h"
#include <list>
#include "Component.h"

//-------------------------------------------------------------------------

class Entity : public Object
{

public:
	Entity(glm::vec3 _position, glm::vec3 _size);
	virtual ~Entity();

	virtual void Render(glm::dmat4 const& modelViewMat);
	virtual void Update(double timeElapsed);
	virtual void PostUpdate(double elapsedTime);
	virtual void Destroy();

	void OnCollision(Object* _otherObject) { Object::OnCollision(_otherObject); };
	void OnTriggerEnter(Object* _otherObject) { Object::OnTriggerEnter(_otherObject); };

	void SetMaterial(Material const& _material) { m_Material = _material; }
	void SetTexture(Texture const& _texture) { m_Texture = _texture; };

	const std::list<Component*>& GetEntityComponents() { return m_EntityComponents; };

	bool isVisible = true;

protected:
	Material m_Material;
	Texture m_Texture;
	Mesh* m_Mesh;

private:
	std::list<Component*> m_EntityComponents;
};

#endif //_H_Entities_H_