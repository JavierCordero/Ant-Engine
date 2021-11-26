#pragma once

#include "..\..\..\EngineCore\LogicEngine\Entity.h"
#include "..\..\..\EngineCore\EngineComponents\MeshComponent.h"

#include "Ant.h"

class Trail : public Entity
{

public:
	Trail(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor);
	virtual ~Trail() {};

	MeshComponent* meshComponent;

	Ant::AntState trailState = Ant::AntState::SEARCHING_FOOD;
	bool enabled = false;

	float strenght = 0.0f;

protected:
	void Render(glm::dmat4 const& modelViewMat);
	void Update(double elapsedTime);
};

