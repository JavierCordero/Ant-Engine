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

bool Mesh::LoadObjFile(const char* _path)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	_path = "assets/models/cube.obj";

	FILE* file = fopen(_path, "r");
	if (file == NULL) {
		printf("Impossible to open the file!\n");
		return false;
	}

	int err = 0;

	while (1) {
		char lineHeader[128];

		// Lee la primera palabra de la línea
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File, es decir, el final del archivo. Se finaliza el ciclo.

		// else : analizar el lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			int err = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			err = fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			err = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	vertices = new glm::dvec3[vertexIndices.size()];

	// Para cada vértice de cada triángulo
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		vertices[i] = vertex;
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
