#include "WarriorAnt.h"
#include "..\..\..\EngineCore\MathLib\MathLib.h"
#include "..\..\..\EngineCore\PhysicEngine\PhysicLib.h"

#ifdef _DEBUG
#include "..\..\..\EngineCore\checkML.h"
#endif // _DEBUG

WarriorAnt::WarriorAnt(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor, AntFarm* _antFarmReference) : Ant(_position, _size, _antColor, _antFarmReference) {
	useTrail = false;
	useVisionCone = false;
	collision->isTrigger = false;
	collisionLayer = (int)PhysicLayer::WarriorAnts;

	Init();
}

WarriorAnt::~WarriorAnt() {

}

void WarriorAnt::Render(glm::dmat4 const& _modelViewMat)
{
	Ant::Render(_modelViewMat);
}

void WarriorAnt::Update(double elapsedTime)
{
	Ant::Update(elapsedTime);

	currentWalkingTimeForTrail -= elapsedTime;

	GetRandomDirection(dirX, dirY, elapsedTime);

	speed = glm::dvec3(dirX * inverseDirX, dirY * inverseDirY, 0) * elapsedTime;

}

void WarriorAnt::OnCollision(Object* _otherObject)
{
	Ant::OnCollision(_otherObject);

	Ant* otherAnt = dynamic_cast<Ant*>(_otherObject);

	if (otherAnt && otherAnt->antFarmReference != antFarmReference) {
		LogicLib::Destroy(otherAnt);
		antFarmReference->numKilledAnts++;
		if (dynamic_cast<WarriorAnt*>(otherAnt)) {
			auto it = std::find(otherAnt->antFarmReference->warriorAnts.begin(), otherAnt->antFarmReference->warriorAnts.end(), otherAnt);

			if (it != otherAnt->antFarmReference->warriorAnts.end()) {
				int index = it - otherAnt->antFarmReference->warriorAnts.begin();
				otherAnt->antFarmReference->warriorAnts.erase(otherAnt->antFarmReference->warriorAnts.begin() + index);
			}
		}

		else {
			auto it = std::find(otherAnt->antFarmReference->workerAnts.begin(), otherAnt->antFarmReference->workerAnts.end(), otherAnt);

			if (it != otherAnt->antFarmReference->workerAnts.end()) {
				int index = it - otherAnt->antFarmReference->workerAnts.begin();
				otherAnt->antFarmReference->workerAnts.erase(otherAnt->antFarmReference->workerAnts.begin() + index);
			}
		}
		
	}
}