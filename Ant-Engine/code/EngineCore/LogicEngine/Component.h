#pragma once

#include "Object.h"

class Component
{
public:
	Component(Object* _componentObjectReference) : componentObjectReference(_componentObjectReference){};
	virtual ~Component() {};

	virtual void Render(glm::dmat4 const& modelViewMat) = 0;
	virtual void Update(double elapsedTime) = 0;
	virtual void PostUpdate(double elapsedTime) = 0;

	Object* componentObjectReference;
};

