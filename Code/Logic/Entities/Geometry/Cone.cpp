#include "Cone.h"
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
Cone::Cone(double _baseRadious, float _height, Object* _objectReference) : Mesh(_objectReference)
{
	CreateCone(_baseRadious, _height, _objectReference);

	//textura.load("..\\Bmps\\container.bmp"); // cargamos la imagen
	//textura2.load("..\\Bmps\\chuches.bmp"); // cargamos la imagen
	//meshR = Mesh::generateRectangleTex(w, h, 0, 0);
	//modelMat = scale(modelMat, dvec3(1.2, 1.2, 1.2));
	//modelMat = translate(modelMat, dvec3(x_, y_, z_));
	//modelMat = rotate(modelMat, radians(90.0), dvec3(0, 1, 0));
}

Cone::Cone(double _baseRadious, float _height, glm::vec4 _color, Object* _objectReference) : Mesh(_objectReference)
{
	CreateCone(_baseRadious, _height, _objectReference, _color);
}

Mesh* Cone::CreateCone(double _baseRadious, float _height, Object* _objectReference, glm::vec4 _color) {

	Primitives::CreateConeOutline(_baseRadious, _height, _color, _objectReference, this);

	return this;
}

void Cone::Render(glm::dmat4 const& modelViewMat) {

	if (drawDebug) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_CULL_FACE);

	Mesh::Draw(modelViewMat);
}

void Cone::UpdateConePosition(glm::dvec3 _position)
{
	//position = _position;
}
