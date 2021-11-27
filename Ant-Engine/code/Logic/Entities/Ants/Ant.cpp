#include "Ant.h"
#include "..\..\..\EngineCore\EngineComponents\CollisionComponent.h"
#include "..\..\..\EngineCore\EngineComponents\MeshComponent.h"
#include "..\..\..\EngineCore\MathLib\MathLib.h"
#include <iostream>
#include <math.h>
#include "..\AntFarm\AntFarm.h"
#include "Trail.h"

#ifdef _DEBUG
#include "..\..\..\EngineCore\checkML.h"
#endif // _DEBUG

Ant::Ant(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor, AntFarm* _antFarmReference) : antFarmReference(_antFarmReference), Entity(_position, _size) {

	collision = new CollisionComponent(this, _position, _size);
	collision->checkCollision = true;
	entityComponents.push_back(collision);

	meshComponent = new MeshComponent(new Cube(_size, _antColor, this), this);
	entityComponents.push_back(meshComponent);

	antFarmPosition = _position;
}

void Ant::Init() {
	if (useVisionCone) {
		visionCone = new VisionCone(GetPosition(), 10.0, 20.0f, glm::vec4(0.5f, 0.8f, 0.0f, 1.0f), this);
		visionCone->isVisible = true;
		EngineCore::GetScene()->sceneObjects.push_back(visionCone);
	}

	if (useTrail) {
		for (int i = 0; i < maxTrail; ++i) {
			Trail* c = new Trail(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::dvec4(1.0f, 0.5f, 0.5f, 1.0f));
			c->isVisible = false;
			trail[i] = c;
			EngineCore::GetScene()->sceneObjects.push_back(c);
		}

	}

	GetRandomDirection(dirX, dirY, 1);
}

Ant::~Ant() {
	//for (Trail* t : trail)
	//{
	//	if(t)
	//	LogicLib::Destroy(t);
	//}
}

void Ant::OnCollision(Object* _otherObject)
{
	Entity::OnCollision(_otherObject);

	auchTime = 0;

	if (rand() % 2 == 0) {
		inverseDirX *= -1;
	}
	if (rand() % 2 == 0) {
		inverseDirY *= -1;
	}
}

void Ant::Render(glm::dmat4 const& _modelViewMat)
{
	Entity::Render(_modelViewMat);
}

bool Ant::CheckClosestTrail(Trail* _trailToCheck, AntState _stateToCheck, Trail* _target, float& _distance)
{
	if (_trailToCheck->enabled && _trailToCheck->trailState == _stateToCheck) {
		float auxDistance = MathLib::Distance(_trailToCheck->GetPosition(), GetPosition());

		if (auxDistance < pheromoneDistance && auxDistance < _distance) {
			if (!_target) {
				//_distance = auxDistance;
				return true;
			}
			else if (_stateToCheck == AntState::MOVING_FOOD_TO_FARM) {
				if (MathLib::Distance(_trailToCheck->GetPosition(), antFarmPosition) > MathLib::Distance(_target->GetPosition(), antFarmPosition)) {
					if (_target->strenght < _trailToCheck->strenght) {
						_target = _trailToCheck;
						//_distance = auxDistance;
						return true;
					}

					return false;
				}
			}

			else if (_stateToCheck == AntState::SEARCHING_FOOD) {
				if (MathLib::Distance(_trailToCheck->GetPosition(), antFarmPosition) < MathLib::Distance(_target->GetPosition(), antFarmPosition)) {
					if (_target->strenght < _trailToCheck->strenght) {
						_target = _trailToCheck;
						//_distance = auxDistance;
						return true;
					}

					return false;
				}
			}


			return false;

		}

		return false;
	}

	return false;
}

void Ant::Update(double elapsedTime)
{
	Entity::Update(elapsedTime);

	auchTime += elapsedTime;

	//Si hace ya un rato que me choque, me voy a serenar que ya no estoy aturdido
	if (auchTime > maxAuchTime) {
		inverseDirX = 1.0f; inverseDirY = 1.0f;
	}
}

void Ant::GetRandomDirection(float& _X_, float& _Y_, double elapsedTime) {

	glm::vec3 randomVector = MathLib::RandomVectorInsideSphere(1);
	randomVector.z = 0;

	//PheromoneSteering();

	desiredDirection = glm::normalize(desiredDirection + randomVector * 0.2f);
	glm::vec3 desiredVelocity = desiredDirection * antSpeed;
	glm::vec3 desiredSteeringForce = (desiredVelocity - velocity) * 2.0f;
	glm::vec3 acceleration = MathLib::ClampMagnitude(desiredSteeringForce, 2) / 1.0f;

	velocity = MathLib::ClampMagnitude(velocity + acceleration * (float)elapsedTime, 2);
	_X_ = velocity.x;
	_Y_ = velocity.y;
}
void Ant::CreateTrail(glm::vec3 _position, glm::vec4 _color, AntState _state, float _strenght)
{
	if (useTrail) {
		trail[trailIndex]->isVisible = true;
		trail[trailIndex]->SetPosition(_position);
		trail[trailIndex]->meshComponent->GetMesh()->ChangeColor(_color);
		trail[trailIndex]->trailState = _state;
		trail[trailIndex]->enabled = true;
		trail[trailIndex]->strenght = _strenght;
		trailIndex++;

		if (trailIndex % maxTrail == 0) {
			trailIndex = 0;
		}
	}
	//trail[trailIndex]->componentObjectReference->
}
