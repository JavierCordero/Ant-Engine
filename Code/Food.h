#pragma once
#include "Entity.h"


class Food : public Entity
{
public:
	Food(glm::vec3 _position, glm::vec3 _size, glm::vec3 _antColor);
	virtual ~Food();

	
};

