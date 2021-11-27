#pragma once
#include "..\LogicEngine\Component.h"
#include "..\LogicEngine\Object.h"
#include "..\LogicEngine\Mesh.h"

class MeshComponent : public Component
{
public:
	MeshComponent(Mesh* _mesh, Object* _componentObjectReference) : Component(_componentObjectReference), mesh(_mesh) {};
	virtual ~MeshComponent() { delete mesh; mesh = nullptr; };

	virtual void Render(glm::dmat4 const& modelViewMat);
	virtual void Update(double elapsedTime);
	virtual void PostUpdate(double elapsedTime) {};

	inline Mesh* GetMesh() { return mesh; };

	bool canMove = true;
	bool isVisible = true;

private:
	Mesh* mesh = nullptr;
};

