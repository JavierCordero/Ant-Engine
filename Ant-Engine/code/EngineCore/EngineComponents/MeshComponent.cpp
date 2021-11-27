#include "MeshComponent.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

#include <iostream>
void MeshComponent::Render(glm::dmat4 const& modelViewMat)
{
	if (isVisible) {
		mesh->Render(modelViewMat);
	}
}

void MeshComponent::Update(double _elapsedTime)
{
	if (canMove) {
		//mesh->speed = componentObjectReference->speed;
		//mesh->UpdateMeshPosition(componentObjectReference->speed);
	}
}
