#include "RGBaxis.h"
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
RGBaxis::RGBaxis(GLdouble _size, Object* _objectReference) : Mesh(_objectReference)
{
	CreateAxis(_size);
}

Mesh* RGBaxis::CreateAxis(GLdouble _size) {
	
	type = GL_LINES;
	numVertices = 6;

	vertices = new glm::dvec3[numVertices];
	vertices[0] = glm::dvec3(0.0, 0.0, 0.0);
	vertices[1] = glm::dvec3(_size, 0.0, 0);
	vertices[2] = glm::dvec3(0, 0.0, 0.0);
	vertices[3] = glm::dvec3(0.0, _size, 0.0);
	vertices[4] = glm::dvec3(0.0, 0.0, 0.0);
	vertices[5] = glm::dvec3(0.0, 0.0, _size);

	colors = new glm::dvec4[numVertices];
	colors[0] = glm::dvec4(1.0, 0.0, 0.0, 1.0);
	colors[1] = glm::dvec4(1.0, 0.0, 0.0, 1.0);
	colors[2] = glm::dvec4(0.0, 1.0, 0.0, 1.0);
	colors[3] = glm::dvec4(0.0, 1.0, 0.0, 1.0);
	colors[4] = glm::dvec4(0.0, 0.0, 1.0, 1.0);
	colors[5] = glm::dvec4(0.0, 0.0, 1.0, 1.0);

	return this;
}

void RGBaxis::Render(glm::dmat4 const& modelViewMat) {
	Draw(modelViewMat);
}

RGBaxis::~RGBaxis() {
	delete vertices;
	vertices = nullptr;

	delete colors;
	colors = nullptr;
}