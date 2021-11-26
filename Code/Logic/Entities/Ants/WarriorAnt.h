#pragma once
#include "Ant.h"
#include "..\AntFarm\AntFarm.h"
#include "Trail.h"
class WarriorAnt : public Ant
{
public:
	WarriorAnt(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor, AntFarm* _antFarmReference);
	~WarriorAnt();

protected:
	void Render(glm::dmat4 const& modelViewMat);
	void Update(double elapsedTime);
	void OnCollision(Object* _otherObject);
};

