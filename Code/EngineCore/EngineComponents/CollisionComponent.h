#pragma once
#include "Component.h"
#include "Object.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(Object* _componentObjectReference, glm::vec3 _position, glm::vec3 _size, bool _isStatic = false) ;
	virtual ~CollisionComponent();

	bool checkCollision = false;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 size = glm::vec3(0.0f, 0.0f, 0.0f);

	bool isTrigger = false;
	bool isStatic = false;

protected:

	void Render(glm::dmat4 const& modelViewMat);
	void Update(double elapsedTime);
	void PostUpdate(double elapsedTime);
};

