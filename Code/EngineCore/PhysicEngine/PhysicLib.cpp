#include "PhysicLib.h"

#ifdef _DEBUG
#include "checkML.h"
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
	if (!_objectToCheck->componentObjectReference->markedForDestroy && !_objectToCheck->isStatic) {
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
	if (_collider->componentObjectReference != _objectToCheck->componentObjectReference && _collider->componentObjectReference->collisionLayer != _objectToCheck->componentObjectReference->collisionLayer
		&& !_collider->componentObjectReference->markedForDestroy && !_objectToCheck->componentObjectReference->markedForDestroy) {

		if (OverlappingCubes(_objectToCheck, _collider)) {

			if (_objectToCheck->isTrigger) {
				_objectToCheck->componentObjectReference->OnTriggerEnter(_collider->componentObjectReference);
			}

			else if (!_collider->isTrigger) {
				_objectToCheck->componentObjectReference->SetPosition(_objectToCheck->componentObjectReference->GetPrevPosition());
				_objectToCheck->componentObjectReference->speed = glm::vec3(0.0f, 0.0f, 0.0f);
				_objectToCheck->componentObjectReference->OnCollision(_collider->componentObjectReference);
				return true;
			}
		}

		return false;
	}

	return false;
}

bool PhysicLib::IsPointInCube(glm::vec3 _point, CollisionComponent* _cube) {
	int minX = _cube->position.x - _cube->size.x;
	int maxX = _cube->position.x + _cube->size.x;

	int minY = _cube->position.y - _cube->size.y;
	int maxY = _cube->position.y + _cube->size.y;

	int minZ = _cube->position.z - _cube->size.z;
	int maxZ = _cube->position.z + _cube->size.z;

	if (minX <= _point.x && _point.x <= maxX && minY <= _point.y && _point.y <= maxY && minZ <= _point.z && _point.z <= maxZ)
		return true;
	return false;
}

bool PhysicLib::OverlappingCubes(CollisionComponent* _cubeA, CollisionComponent* _cubeB) {

	int minXA = _cubeA->position.x - _cubeA->size.x;
	int maxXA = _cubeA->position.x + _cubeA->size.x;

	int minYA = _cubeA->position.y - _cubeA->size.y;
	int maxYA = _cubeA->position.y + _cubeA->size.y;

	int minZA = _cubeA->position.z - _cubeA->size.z;
	int maxZA = _cubeA->position.z + _cubeA->size.z;

	int minXB = _cubeB->position.x - _cubeB->size.x;
	int maxXB = _cubeB->position.x + _cubeB->size.x;

	int minYB = _cubeB->position.y - _cubeB->size.y;
	int maxYB = _cubeB->position.y + _cubeB->size.y;

	int minZB = _cubeB->position.z - _cubeB->size.z;
	int maxZB = _cubeB->position.z + _cubeB->size.z;

	return (minXA <= maxXB && maxXA >= minXB) &&
		(minYA <= maxYB && maxYA >= minYB) &&
		(minZA <= maxZB && maxZA >= minZB);
}