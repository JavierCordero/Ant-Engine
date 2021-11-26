#pragma once
#include "Entity.h"
#include "Cube.h"
#include <list>
#include "LogicLib.h"
#include "Cone.h"
#include "MeshComponent.h"
#include "VisionCone.h"

class AntFarm;
class Trail;

class Ant : public Entity
{
public:

	enum class AntState { SEARCHING_FOOD = 0, MOVING_FOOD_TO_FARM = 1 };

	Ant(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor, AntFarm* _antFarmReference);
	virtual ~Ant();
	
	void Init();

	void OnCollision(Object* _otherObject);

	float antSpeed = 30.0f;
	
	bool useTrail = true, useVisionCone = true;

	AntState thisAntState = AntState::SEARCHING_FOOD;

	AntFarm* antFarmReference;

	void CreateTrail(glm::vec3 _position, glm::vec4 _color, AntState _state, float _strenght);

	int knownPath = 0;

	MeshComponent* meshComponent;
	CollisionComponent* collision;

	void GetRandomDirection(float& _X, float& _y, double _elapsedTime);

	float dirX = 1, dirY = 0;

	glm::vec3 velocity = glm::vec3(0,0,0);
	glm::vec3 desiredDirection = glm::vec3(0, 0, 0);

	glm::vec3 antFarmPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	float maxWalkingTimeForTrail = 0.2f;
	float currentWalkingTimeForTrail = 0.2f;

	static const int16_t maxTrail = 150;
	float pheromoneDistance = 120;

	Trail* trail [maxTrail];
	uint16_t trailIndex = 0;

	VisionCone* visionCone = nullptr;

	float inverseDirX = 1.0f, inverseDirY = 1.0f;

	bool CheckClosestTrail(Trail* _trailToCheck, AntState _stateToCheck, Trail* _target, float & _distance);

	float auchTime = 0; float maxAuchTime = 2.0f;

protected:
	virtual void Render(glm::dmat4 const& modelViewMat);
	virtual void Update(double elapsedTime);
};

