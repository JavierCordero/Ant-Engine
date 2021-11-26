#pragma once

#include "..\..\..\EngineCore\LogicEngine\Entity.h"
#include "..\..\..\EngineCore\RenderEngine\Primitives.h"

class Cube : public Mesh
{
public:
	Cube(glm::vec3 _size, Object* _objectReference);
	Cube(glm::vec3 _size, glm::vec3 _color, Object* _objectReference);
	virtual ~Cube();

	void Render(glm::dmat4 const& modelViewMat);
	void UpdateCubePosition(glm::dvec3 _newPosition);
	
	Mesh* CreateCube(glm::vec3 _size, Object* _objectReference, glm::vec3 _color = glm::vec3(0, 0, 0));

private:
	Mesh* auxMesh = nullptr;

protected:
	//void Render(glm::dmat4 const& modelViewMat);
};

