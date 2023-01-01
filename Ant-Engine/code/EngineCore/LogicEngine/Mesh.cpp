#define _CRT_SECURE_NO_DEPRECATE
#include "Mesh.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include <string>

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

using namespace glm;

//-------------------------------------------------------------------------

Mesh::~Mesh(void)
{
	delete[] m_Vertices;
	delete[] m_Colors;
	delete[] m_TexCoords;
}
//-------------------------------------------------------------------------

void Mesh::Draw(glm::dmat4 const& modelViewMat)
{
	if (m_ParentReference) {
		glm::dmat4 aMat = modelViewMat * glm::dmat4(1.0);

		aMat = glm::translate(aMat, glm::dvec3(m_ParentReference->GetPosition()));
		glLoadMatrixd(value_ptr(aMat));

		aMat = glm::rotate(aMat, glm::radians((double)m_ParentReference->GetDirection().x), glm::dvec3(1.0, 0.0, 0.0));
		aMat = glm::rotate(aMat, glm::radians((double)m_ParentReference->GetDirection().y), glm::dvec3(0.0, 1.0, 0.0));
		aMat = glm::rotate(aMat, glm::radians((double)m_ParentReference->GetDirection().z), glm::dvec3(0.0, 0.0, 1.0));

		glLoadMatrixd(value_ptr(aMat));
	}
	FinalDraw();

	//Restauramos la matriz original
	glLoadMatrixd(value_ptr(modelViewMat * glm::dmat4(1.0)));
}

void Mesh::FinalDraw() {
	if (m_Vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, m_Vertices);  // number of coordinates per vertex, type of each coordinate 
		if (m_Colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, m_Colors);   // number of coordinates per color, type of each coordinate 
			if (m_TexCoords != nullptr) {
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_DOUBLE, 0, m_TexCoords);
			}
		}

		glDrawArrays(m_Type, 0, m_NumVertices);   // kind of primitives, first, count

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}

void Mesh::UpdateMeshPosition(glm::dvec3 _direction) {

	for (int i = 0; i < m_NumVertices; ++i)
	{
		m_Vertices[i] = m_Vertices[i] + _direction;
	}
}

//-------------------------------------------------------------------------

RectangleMesh::RectangleMesh(Object* _objectReference, float _width, float _height) : Mesh(_objectReference)
{
	m_Type = GL_TRIANGLE_STRIP;
	m_NumVertices = 4;
	int lados = 4;

	m_Vertices = new dvec3[m_NumVertices];
	m_Vertices[0] = dvec3(-_width / 2, _height / 2, 0);
	m_Vertices[1] = dvec3(-_width / 2, -_height / 2, 0);
	m_Vertices[2] = dvec3(_width / 2, _height / 2, 0);
	m_Vertices[3] = dvec3(_width / 2, -_height / 2, 0);

	m_Colors = new dvec4[m_NumVertices];
	m_Colors[0] = dvec4(0.0, 0.0, 0.0, 1.0);
	m_Colors[1] = dvec4(0.0, 0.0, 0.0, 1.0);
	m_Colors[2] = dvec4(0.0, 0.0, 0.0, 1.0);
	m_Colors[3] = dvec4(0.0, 0.0, 0.0, 1.0);

	m_TexCoords = new dvec2[m_NumVertices];
	m_TexCoords[0] = dvec2(0, 0);
	m_TexCoords[1] = dvec2(0, 1);
	m_TexCoords[2] = dvec2(1, 0);
	m_TexCoords[3] = dvec2(1, 1);
}