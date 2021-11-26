#pragma once
#include "Entity.h"
#include "Cube.h"


class Wall : public Entity
{
public:
	Wall(glm::vec3 _position, glm::vec3 _size ,glm::vec3 _color = glm::vec3(0, 0, 0));
	virtual ~Wall();

protected:
	void Update(float _elapsedTime) { Entity::Update(_elapsedTime); }
	void Render(glm::dmat4 const& _modelViewMat) { Entity::Render(_modelViewMat); }
};

