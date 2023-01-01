#include "PhysicLib.h"
#include "..\MathLib\MathLib.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

std::vector<CollisionComponent*> PhysicLib::colliders; //WOW! 
Quad* PhysicLib::quadTree;

void PhysicLib::Init() {
	quadTree = new Quad(Point(-1000, -1000), Point(1000, 1000));
}

void PhysicLib::Destroy() {
	delete quadTree;
	quadTree = nullptr;
}

bool PhysicLib::CheckCollision(CollisionComponent* _objectToCheck)
{
	if (!_objectToCheck->componentObjectReference->IsObjectMarkedForDestroy() && !_objectToCheck->isStatic) {
		for each (CollisionComponent * collider in colliders)
		{
			if (collider->isStatic) {
				//Aquí hay que comprobar si está en el quadtree en el que se encuentra la entidad o no
				if (quadTree->search(_objectToCheck->componentObjectReference) && FinalCheck(collider, _objectToCheck)) {
					return true;
				}
			}

			else {
				if (FinalCheck(collider, _objectToCheck)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool PhysicLib::FinalCheck(CollisionComponent* _collider, CollisionComponent* _objectToCheck) {
	if (_collider->componentObjectReference != _objectToCheck->componentObjectReference && _collider->componentObjectReference->GetObjectCollisionLayer() != _objectToCheck->componentObjectReference->GetObjectCollisionLayer()
		&& !_collider->componentObjectReference->IsObjectMarkedForDestroy() && !_objectToCheck->componentObjectReference->IsObjectMarkedForDestroy()) {

		if (MathLib::OverlappingCubes(_objectToCheck->position, _objectToCheck->size, _collider->position, _collider->size)) {

			if (_objectToCheck->isTrigger) {
				_objectToCheck->componentObjectReference->OnTriggerEnter(_collider->componentObjectReference);
			}

			else if (!_collider->isTrigger) {
				_objectToCheck->componentObjectReference->SetPosition(_objectToCheck->componentObjectReference->GetPrevPosition());
				_objectToCheck->componentObjectReference->SetObjectSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
				_objectToCheck->componentObjectReference->OnCollision(_collider->componentObjectReference);
				return true;
			}
		}

		return false;
	}

	return false;
}