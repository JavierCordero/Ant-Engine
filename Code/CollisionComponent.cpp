#include "CollisionComponent.h"
#include "PhysicLib.h"
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
CollisionComponent::CollisionComponent(Object* _componentObjectReference, glm::vec3 _position, glm::vec3 _size, bool _isStatic) : isStatic(_isStatic), Component(_componentObjectReference),
	position(_position), size(_size)
{
	PhysicLib::colliders.push_back(this);
	if (isStatic) {
		PhysicLib::quadTree->insert(_componentObjectReference);
	}
}

CollisionComponent::~CollisionComponent()
{
	auto it = std::find(PhysicLib::colliders.begin(), PhysicLib::colliders.end(), this);

	if (it != PhysicLib::colliders.end()) {		
		int index = it - PhysicLib::colliders.begin();
		PhysicLib::colliders.erase(PhysicLib::colliders.begin() + index);
	}
}

void CollisionComponent::Render(glm::dmat4 const& modelViewMat)
{
}

void CollisionComponent::Update(double elapsedTime)
{
	position = componentObjectReference->GetPosition();
	size = componentObjectReference->GetSize();
}

void CollisionComponent::PostUpdate(double elapsedTime) {
	if (checkCollision && !isStatic) {
		PhysicLib::CheckCollision(this);
	}
}
