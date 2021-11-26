#include "Cube.h"
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/constants.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
Cube::Cube(glm::vec3 _size, Object* _objectReference) : Mesh(_objectReference)
{
	CreateCube(_size, _objectReference);
	
	//textura.load("..\\Bmps\\container.bmp"); // cargamos la imagen
	//textura2.load("..\\Bmps\\chuches.bmp"); // cargamos la imagen
	//meshR = Mesh::generateRectangleTex(w, h, 0, 0);
	//modelMat = scale(modelMat, dvec3(1.2, 1.2, 1.2));
	//modelMat = translate(modelMat, dvec3(x_, y_, z_));
	//modelMat = rotate(modelMat, radians(90.0), dvec3(0, 1, 0));
}

Cube::Cube(glm::vec3 _size, glm::vec3 _color, Object* _objectReference) : Mesh(_objectReference)
{
	CreateCube(_size, _objectReference, _color );
}

Cube::~Cube()
{
	//delete auxMesh; auxMesh = nullptr;
}

Mesh* Cube::CreateCube(glm::vec3 _size, Object* _objectReference, glm::vec3 _color) {

	auxMesh = Primitives::CreateRectangleOutline(_size, _color, _objectReference, this);

	texCoords = new glm::dvec2[numVertices];
	//texCoords[0] = glm::dvec2(0, 0);
	//texCoords[1] = glm::dvec2(0, 1);
	//texCoords[2] = glm::dvec2(1, 0);
	//texCoords[3] = glm::dvec2(1, 1);
	//texCoords[4] = glm::dvec2(2, 0);
	//texCoords[5] = glm::dvec2(2, 1);
	//texCoords[6] = glm::dvec2(3, 0);
	//texCoords[7] = glm::dvec2(3, 1);
	//texCoords[8] = glm::dvec2(4, 0);
	//texCoords[9] = glm::dvec2(4, 1);

	return this;
}

void Cube::Render(glm::dmat4 const& modelViewMat) {

	if (drawDebug) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	
	glDisable(GL_CULL_FACE);

	Mesh::Draw(modelViewMat);
}

void Cube::UpdateCubePosition(glm::dvec3 _direction)
{
	Mesh::UpdateMeshPosition(_direction);
	//Entity::Update(elapsedTime);
}
