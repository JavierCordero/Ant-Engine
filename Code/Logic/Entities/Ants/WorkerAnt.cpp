#include "WorkerAnt.h"
#include "..\..\..\EngineCore\MathLib\MathLib.h"
#include "..\..\..\EngineCore\PhysicEngine\PhysicLib.h"

#ifdef _DEBUG
#include "..\..\..\EngineCore\checkML.h"
#endif // _DEBUG

WorkerAnt::WorkerAnt(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor, AntFarm* _antFarmReference) : Ant(_position, _size, _antColor, _antFarmReference){
	Init();
	collisionLayer = (int)PhysicLayer::WorkerAnts;
}

WorkerAnt::~WorkerAnt() {

}

void WorkerAnt::Render(glm::dmat4 const& _modelViewMat)
{
	Ant::Render(_modelViewMat);
}

void WorkerAnt::Update(double elapsedTime)
{
	Ant::Update(elapsedTime);

	currentWalkingTimeForTrail -= elapsedTime;

	for each (Trail * t in trail) {
		t->strenght -= elapsedTime;
		if (t->strenght < 0) {
			t->strenght = 0;
			t->enabled = false;
			t->isVisible = false;
		}
	}

	//std::cout << currentWalkingTimeForTrail << std::endl;

	if (thisAntState == AntState::SEARCHING_FOOD) {
		float distance = std::numeric_limits<float>::max();

		Trail* targetPos = nullptr;

		//Otra curiosidad, solo mira las hormigas del hormiguero mío, no vaya a ser...
		for each (Ant * ant in antFarmReference->workerAnts)
		{
			for each (Trail * trail in ant->trail) {
				if (CheckClosestTrail(trail, AntState::MOVING_FOOD_TO_FARM, targetPos, distance)) {
					targetPos = trail;
				}
			}
		}

		if (targetPos != nullptr) {

			//Para no quedarme atrapado como un lerdo
			if (MathLib::Distance(targetPos->GetPosition(), GetPosition()) < 0.5f) {
				GetRandomDirection(dirX, dirY, elapsedTime);
			}

			else {
				glm::vec2 dir = glm::normalize(glm::vec2(targetPos->GetX() - GetX(), targetPos->GetY() - GetY()));
				dirX = dir.x * antSpeed;
				dirY = dir.y * antSpeed;
			}

		}

		else {
			GetRandomDirection(dirX, dirY, elapsedTime);
		}
	}

	else if (thisAntState == AntState::MOVING_FOOD_TO_FARM) {

		float distance = std::numeric_limits<float>::max();

		Trail* targetPos = nullptr;

		for each (Ant * ant in antFarmReference->workerAnts)
		{
			for each (Trail * trail in ant->trail) {
				if (CheckClosestTrail(trail, AntState::SEARCHING_FOOD, targetPos, distance)) {
					targetPos = trail;
				}
			}

			if (CheckClosestTrail(antFarmReference->farmTrail, AntState::SEARCHING_FOOD, targetPos, distance)) {
				targetPos = antFarmReference->farmTrail;
			}

		}

		if (targetPos != nullptr) {
			glm::vec2 dir = glm::normalize(glm::vec2(targetPos->GetX() - GetX(), targetPos->GetY() - GetY()));
			dirX = dir.x * antSpeed;
			dirY = dir.y * antSpeed;
		}

		else {
			GetRandomDirection(dirX, dirY, elapsedTime);
		}

	}

	double angle = atan2((float)dirX * inverseDirX, (float)dirY * inverseDirY) * 180 / PI;

	if (abs(angle) > 1) {

		angle = 270 - angle - 90;
		glm::vec3 vector = glm::vec3(90.0, angle, 0.0);
		visionCone->SetDirection(vector);
	}

	visionCone->SetPosition(GetPosition());

	if (currentWalkingTimeForTrail <= 0) {
		currentWalkingTimeForTrail = maxWalkingTimeForTrail;

		if (thisAntState == AntState::SEARCHING_FOOD) {
			//std::cout << "CreatingPath\n";
			knownPath++;
			if (knownPath < maxTrail) {
				CreateTrail(glm::vec3(GetX(), GetY(), -10), glm::dvec4(0.0f, 0.5f, 1.0f, 1.0f), AntState::SEARCHING_FOOD, 20.0f);
			}
		}

		else if (thisAntState == AntState::MOVING_FOOD_TO_FARM) {
			knownPath++;

			if (knownPath < Ant::maxTrail) {
				CreateTrail(glm::vec3(GetX(), GetY(), -10), glm::dvec4(1.0f, 0.5f, 0.5f, 1.0f), AntState::MOVING_FOOD_TO_FARM, 20.0f);
			}
		}
	}

	speed = glm::dvec3(dirX * inverseDirX, dirY * inverseDirY, 0) * elapsedTime;

}
