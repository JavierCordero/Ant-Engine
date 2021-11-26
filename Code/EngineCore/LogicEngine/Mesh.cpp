#include "Mesh.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
using namespace glm;

//-------------------------------------------------------------------------

Mesh::~Mesh(void)
{
	delete[] vertices;
	delete[] colors;
	delete[] texCoords;
}
//-------------------------------------------------------------------------

void Mesh::Draw(glm::dmat4 const& modelViewMat)
{
	if (objectReference) {
		glm::dmat4 aMat = modelViewMat * glm::dmat4(1.0);

		aMat = glm::translate(aMat, glm::dvec3(objectReference->GetPosition()));
		glLoadMatrixd(value_ptr(aMat));

		aMat = glm::rotate(aMat, glm::radians((double)objectReference->GetDirection().x), glm::dvec3(1.0, 0.0, 0.0));
		aMat = glm::rotate(aMat, glm::radians((double)objectReference->GetDirection().y), glm::dvec3(0.0, 1.0, 0.0));
		aMat = glm::rotate(aMat, glm::radians((double)objectReference->GetDirection().z), glm::dvec3(0.0, 0.0, 1.0));

		glLoadMatrixd(value_ptr(aMat));
	}
	FinalDraw();

	//Restauramos la matriz original
	glLoadMatrixd(value_ptr(modelViewMat * glm::dmat4(1.0)));
}

void Mesh::FinalDraw() {
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
			if (texCoords != nullptr) {
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
			}
		}

		glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}

void Mesh::UpdateMeshPosition(glm::dvec3 _direction) {

	for (int i = 0; i < numVertices; ++i)
	{
		vertices[i] = vertices[i] + _direction;
	}

}
//-------------------------------------------------------------------------

//Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h) {
//	Mesh* m = new Mesh();
//	m->type = GL_TRIANGLE_STRIP;
//	m->numVertices = 4;
//	int lados = 4;
//
//	m->vertices = new dvec3[m->numVertices];
//	m->vertices[0] = dvec3(-w / 2, h / 2, 0);
//	m->vertices[1] = dvec3(-w / 2, -h / 2, 0);
//	m->vertices[2] = dvec3(w / 2, h / 2, 0);
//	m->vertices[3] = dvec3(w / 2, -h / 2, 0);
//
//	m->colors = new dvec4[m->numVertices];
//	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
//	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
//	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);
//	m->colors[3] = dvec4(0.0, 0.0, 0.0, 0.0);
//
//	return m;
//}
//
//static Mesh* generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble
//	incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) {
//
//}
//
///////////TEXTURAS\\\\\\\\\\\\\\\\\
//
//Mesh* Mesh::generateRectangleTex(GLdouble l, GLdouble h, GLint xRep, GLint  yRep) {
//	Mesh* m = generateRectangle(l,h);
//	
//	m->texCoords = new dvec2[m->numVertices];
//	m->texCoords[0] = dvec2(0, yRep + 1);
//	m->texCoords[1] = dvec2(0, 0);
//	m->texCoords[2] = dvec2(xRep + 1, yRep + 1);
//	m->texCoords[3] = dvec2(xRep + 1, 0);
//	
//	return m;
//}
