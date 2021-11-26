#include "Trail.h"
#include "Cube.h"

#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
Trail::Trail(glm::vec3 _position, glm::vec3 _size, glm::vec4 _antColor) : Entity(_position, _size) {
	meshComponent = new MeshComponent(new Cube(_size, _antColor, this), this);
	entityComponents.push_back(meshComponent);
}

void Trail::Render(glm::dmat4 const& _modelViewMat)
{

	Entity::Render(_modelViewMat);

	//Cube::Render(modelViewMat);
	//Render(modelViewMat);
}

void Trail::Update(double elapsedTime)
{
	//Cube::Update(elapsedTime);

	//std::cout << elapsedTime << std::endl;

	Entity::Update(elapsedTime);
}