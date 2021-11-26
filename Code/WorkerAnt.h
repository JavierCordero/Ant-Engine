#pragma once
#include "Ant.h"
#include "AntFarm.h"
#include "Trail.h"

class WorkerAnt : public Ant
{
public:
	WorkerAnt(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor, AntFarm* _antFarmReference);
	~WorkerAnt();

protected:
	void Render(glm::dmat4 const& modelViewMat);
	void Update(double elapsedTime);
};

