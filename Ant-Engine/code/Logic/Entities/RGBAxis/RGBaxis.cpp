#include "RGBaxis.h"

#ifdef _DEBUG
#include "..\..\..\EngineCore\checkML.h"
#endif // _DEBUG

RGBaxis::RGBaxis(GLdouble _size, Object* _objectReference) : Mesh(_objectReference)
{
	CreateAxis(_size);
}

Mesh* RGBaxis::CreateAxis(GLdouble _size) {
	
	m_Type = GL_LINES;
	m_NumVertices = 6;

	m_Vertices = new glm::dvec3[m_NumVertices];
	m_Vertices[0] = glm::dvec3(0.0, 0.0, 0.0);
	m_Vertices[1] = glm::dvec3(_size, 0.0, 0);
	m_Vertices[2] = glm::dvec3(0, 0.0, 0.0);
	m_Vertices[3] = glm::dvec3(0.0, _size, 0.0);
	m_Vertices[4] = glm::dvec3(0.0, 0.0, 0.0);
	m_Vertices[5] = glm::dvec3(0.0, 0.0, _size);

	m_Colors = new glm::dvec4[m_NumVertices];
	m_Colors[0] = glm::dvec4(1.0, 0.0, 0.0, 1.0);
	m_Colors[1] = glm::dvec4(1.0, 0.0, 0.0, 1.0);
	m_Colors[2] = glm::dvec4(0.0, 1.0, 0.0, 1.0);
	m_Colors[3] = glm::dvec4(0.0, 1.0, 0.0, 1.0);
	m_Colors[4] = glm::dvec4(0.0, 0.0, 1.0, 1.0);
	m_Colors[5] = glm::dvec4(0.0, 0.0, 1.0, 1.0);

	return this;
}

void RGBaxis::Render(glm::dmat4 const& modelViewMat) {
	Draw(modelViewMat);
}

RGBaxis::~RGBaxis() {
	delete m_Vertices;
	m_Vertices = nullptr;

	delete m_Colors;
	m_Colors = nullptr;
}