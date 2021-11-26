#include "VisionCone.h"
#include "MeshComponent.h"
#include "Cone.h"
#include "Food.h"
#include <iostream>
#include "LogicLib.h"
#include "Ant.h"
#include "AntFarm.h"

#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
VisionCone::VisionCone(glm::vec3 _position, double _baseRadious, float _height, glm::vec4 _color, Ant* _antReference) : antReference(_antReference), Entity(_position, glm::vec3(_baseRadious, _height, _baseRadious))
{

	MeshComponent* cone = new MeshComponent(new Cone(_baseRadious, _height, _color, this), this);
	cone->canMove = false;
	entityComponents.push_back(cone);

	collision = new CollisionComponent(this, _position, glm::vec3(_baseRadious, _height, _baseRadious));
	collision->checkCollision = true;
	collision->isTrigger = true;
	entityComponents.push_back(collision);
	collisionLayer = 1;
}

void VisionCone::Render(glm::dmat4 const& _modelViewMat)
{
	Entity::Render(_modelViewMat);

}

void VisionCone::Update(double elapsedTime)
{
	Entity::Update(elapsedTime);
}

void VisionCone::OnTriggerEnter(Object* _otherObject)
{
	Entity::OnTriggerEnter(_otherObject);

	if (antReference->thisAntState == Ant::AntState::SEARCHING_FOOD) {
		Food* food = dynamic_cast<Food*>(_otherObject);

		if (food) {
			LogicLib::Destroy(food);
			antReference->CreateTrail(food->GetPosition(), glm::dvec4(1.0f, 0.5f, 0.5f, 1.0f), Ant::AntState::MOVING_FOOD_TO_FARM, 25.0f);
			antReference->thisAntState = Ant::AntState::MOVING_FOOD_TO_FARM;
			//antReference->meshComponent->GetMesh()->ChangeColor(glm::dvec4(1.0f, 0.5f, 0.5f, 1.0f));
			antReference->knownPath = 0;
		}
	}

}