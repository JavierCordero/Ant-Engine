#include "Primitives.h"
#include "..\MathLib\MathLib.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG


Mesh* Primitives::CreateCubeOutline(double _width, glm::vec3 _color, Object* _objectReference, Mesh* _targetMesh) {

	_targetMesh->SetObjectReference(_objectReference);
	_targetMesh->SetType(GL_QUADS);
	_targetMesh->SetNumVertices(24);
	
	float halfSize = _width / 2;

	_targetMesh->SetVertices(new glm::dvec3[_targetMesh->GetNumVertices()]);

	glm::dvec3* vertices = _targetMesh->GetVertices();

	//front face
	vertices[0] = glm::dvec3(-halfSize, halfSize, halfSize);
	vertices[1] = glm::dvec3(halfSize, halfSize, halfSize);
	vertices[2] = glm::dvec3(halfSize, -halfSize, halfSize);
	vertices[3] = glm::dvec3(-halfSize, -halfSize, halfSize);

	//back face
	vertices[4] = glm::dvec3(-halfSize, halfSize, -halfSize);
	vertices[5] = glm::dvec3(halfSize, halfSize, -halfSize);
	vertices[6] = glm::dvec3(halfSize, -halfSize, -halfSize);
	vertices[7] = glm::dvec3(-halfSize, -halfSize, -halfSize);

	//left face
	vertices[8] = vertices[0];
	vertices[9] = vertices[4];
	vertices[10] = vertices[7];
	vertices[11] = vertices[3];

	//right face
	vertices[12] = vertices[1];
	vertices[13] = vertices[5];
	vertices[14] = vertices[6];
	vertices[15] = vertices[2];

	//top face
	vertices[16] = vertices[0];
	vertices[17] = vertices[4];
	vertices[18] = vertices[5];
	vertices[19] = vertices[1];

	//bottom face
	vertices[20] = vertices[3];
	vertices[21] = vertices[7];
	vertices[22] = vertices[6];
	vertices[23] = vertices[2];

	_targetMesh->SetColors(new glm::dvec4[_targetMesh->GetNumVertices()]);

	glm::dvec4* colors = _targetMesh->GetColors();
	for (int i = 0; i < _targetMesh->GetNumVertices(); ++i) {
		colors[i] = glm::dvec4(_color.r, _color.g, _color.b, 1.0);
	}

	return _targetMesh;
}


Mesh* Primitives::CreateRectangleOutline(glm::vec3 _size, glm::vec3 _color, Object* _objectReference, Mesh* _targetMesh) {

	_targetMesh->SetObjectReference(_objectReference);
	_targetMesh->SetType(GL_QUADS);
	_targetMesh->SetNumVertices(24);

	float halfSizeX = _size.x / 2;
	float halfSizeY = _size.y / 2;
	float halfSizeZ = _size.z / 2;

	_targetMesh->SetVertices(new glm::dvec3[_targetMesh->GetNumVertices()]);

	glm::dvec3* vertices = _targetMesh->GetVertices();

	//front face
	vertices[0] = glm::dvec3(-halfSizeX, halfSizeY, halfSizeZ);
	vertices[1] = glm::dvec3(halfSizeX, halfSizeY, halfSizeZ);
	vertices[2] = glm::dvec3(halfSizeX, -halfSizeY, halfSizeZ);
	vertices[3] = glm::dvec3(-halfSizeX, -halfSizeY, halfSizeZ);

	//back face
	vertices[4] = glm::dvec3(-halfSizeX, halfSizeY, -halfSizeZ);
	vertices[5] = glm::dvec3(halfSizeX, halfSizeY, -halfSizeZ);
	vertices[6] = glm::dvec3(halfSizeX, -halfSizeY, -halfSizeZ);
	vertices[7] = glm::dvec3(-halfSizeX, -halfSizeY, -halfSizeZ);

	//left face
	vertices[8] = vertices[0];
	vertices[9] = vertices[4];
	vertices[10] = vertices[7];
	vertices[11] = vertices[3];

	//right face
	vertices[12] = vertices[1];
	vertices[13] = vertices[5];
	vertices[14] = vertices[6];
	vertices[15] = vertices[2];

	//top face
	vertices[16] = vertices[0];
	vertices[17] = vertices[4];
	vertices[18] = vertices[5];
	vertices[19] = vertices[1];

	//bottom face
	vertices[20] = vertices[3];
	vertices[21] = vertices[7];
	vertices[22] = vertices[6];
	vertices[23] = vertices[2];

	_targetMesh->SetColors(new glm::dvec4[_targetMesh->GetNumVertices()]);

	glm::dvec4* colors = _targetMesh->GetColors();

	for (int i = 0; i < _targetMesh->GetNumVertices(); ++i) {
		colors[i] = glm::dvec4(_color.r, _color.g, _color.b, 1.0);
	}

	return _targetMesh;
}

Mesh* Primitives::CreateConeOutline(float _baseRadious, float _height, glm::vec4 _color, Object* _objectReference, Mesh* _targetMesh)
{
	return CreateCircle(_baseRadious, _color, _objectReference, _targetMesh, _height);
}

Mesh* Primitives::CreateCircle(float _radious, glm::vec4 _color, Object* _objectReference, Mesh* _targetMesh, float _height)
{

	_targetMesh->SetObjectReference(_objectReference);
	_targetMesh->SetType(GL_TRIANGLE_STRIP);
	_targetMesh->SetNumVertices(720 + 1);
	_targetMesh->SetColors(new glm::dvec4[_targetMesh->GetNumVertices()]);

	_targetMesh->SetVertices(new glm::dvec3[_targetMesh->GetNumVertices()]);

	for (int i = 0; i < _targetMesh->GetNumVertices() / 2 + 1; i += 2)
	{
		_targetMesh->GetVertices()[i] = glm::vec3(0.0f, 0.0f, 0.0f);
		_targetMesh->GetColors()[i] = _color;

		float angle = PI * 2 * ((float)i / (float)360);
		float s = sin(angle) * _radious;
		float c = cos(angle) * _radious;
		_targetMesh->GetVertices()[i + 1] = glm::vec3(c, s, 0.f) + (glm::vec3(0.0f, 0.0f, 1.0f) * _height);
				
		_targetMesh->GetColors()[i + 1] = _color;
	}

	return _targetMesh;
}
