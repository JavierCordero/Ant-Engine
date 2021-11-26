#include "Primitives.h"
#include "MathLib.h"
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG

Mesh* Primitives::CreateCubeOutline(double _width, glm::vec3 _color, Object* _objectReference, Mesh* _targetMesh) {

	_targetMesh->SetObjectReference(_objectReference);
	_targetMesh->type = GL_QUADS;
	_targetMesh->numVertices = 24;
	
	float halfSize = _width / 2;

	_targetMesh->vertices = new glm::dvec3[_targetMesh->numVertices];

	//front face
	_targetMesh->vertices[0] = glm::dvec3(-halfSize, halfSize, halfSize);
	_targetMesh->vertices[1] = glm::dvec3(halfSize, halfSize, halfSize);
	_targetMesh->vertices[2] = glm::dvec3(halfSize, -halfSize, halfSize);
	_targetMesh->vertices[3] = glm::dvec3(-halfSize, -halfSize, halfSize);

	//back face
	_targetMesh->vertices[4] = glm::dvec3(-halfSize, halfSize, -halfSize);
	_targetMesh->vertices[5] = glm::dvec3(halfSize, halfSize, -halfSize);
	_targetMesh->vertices[6] = glm::dvec3(halfSize, -halfSize, -halfSize);
	_targetMesh->vertices[7] = glm::dvec3(-halfSize, -halfSize, -halfSize);

	//left face
	_targetMesh->vertices[8] = _targetMesh->vertices[0];
	_targetMesh->vertices[9] = _targetMesh->vertices[4];
	_targetMesh->vertices[10] = _targetMesh->vertices[7];
	_targetMesh->vertices[11] = _targetMesh->vertices[3];

	//right face
	_targetMesh->vertices[12] = _targetMesh->vertices[1];
	_targetMesh->vertices[13] = _targetMesh->vertices[5];
	_targetMesh->vertices[14] = _targetMesh->vertices[6];
	_targetMesh->vertices[15] = _targetMesh->vertices[2];

	//top face
	_targetMesh->vertices[16] = _targetMesh->vertices[0];
	_targetMesh->vertices[17] = _targetMesh->vertices[4];
	_targetMesh->vertices[18] = _targetMesh->vertices[5];
	_targetMesh->vertices[19] = _targetMesh->vertices[1];

	//bottom face
	_targetMesh->vertices[20] = _targetMesh->vertices[3];
	_targetMesh->vertices[21] = _targetMesh->vertices[7];
	_targetMesh->vertices[22] = _targetMesh->vertices[6];
	_targetMesh->vertices[23] = _targetMesh->vertices[2];

	_targetMesh->colors = new glm::dvec4[_targetMesh->numVertices];

	for (int i = 0; i < _targetMesh->numVertices; ++i) {
		_targetMesh->colors[i] = glm::dvec4(_color.r, _color.g, _color.b, 1.0);
	}

	return _targetMesh;
}


Mesh* Primitives::CreateRectangleOutline(glm::vec3 _size, glm::vec3 _color, Object* _objectReference, Mesh* _targetMesh) {

	_targetMesh->SetObjectReference(_objectReference);
	_targetMesh->type = GL_QUADS;
	_targetMesh->numVertices = 24;

	float halfSizeX = _size.x / 2;
	float halfSizeY = _size.y / 2;
	float halfSizeZ = _size.z / 2;

	_targetMesh->vertices = new glm::dvec3[_targetMesh->numVertices];

	//front face
	_targetMesh->vertices[0] = glm::dvec3(-halfSizeX, halfSizeY, halfSizeZ);
	_targetMesh->vertices[1] = glm::dvec3(halfSizeX, halfSizeY, halfSizeZ);
	_targetMesh->vertices[2] = glm::dvec3(halfSizeX, -halfSizeY, halfSizeZ);
	_targetMesh->vertices[3] = glm::dvec3(-halfSizeX, -halfSizeY, halfSizeZ);

	//back face
	_targetMesh->vertices[4] = glm::dvec3(-halfSizeX, halfSizeY, -halfSizeZ);
	_targetMesh->vertices[5] = glm::dvec3(halfSizeX, halfSizeY, -halfSizeZ);
	_targetMesh->vertices[6] = glm::dvec3(halfSizeX, -halfSizeY, -halfSizeZ);
	_targetMesh->vertices[7] = glm::dvec3(-halfSizeX, -halfSizeY, -halfSizeZ);

	//left face
	_targetMesh->vertices[8] = _targetMesh->vertices[0];
	_targetMesh->vertices[9] = _targetMesh->vertices[4];
	_targetMesh->vertices[10] = _targetMesh->vertices[7];
	_targetMesh->vertices[11] = _targetMesh->vertices[3];

	//right face
	_targetMesh->vertices[12] = _targetMesh->vertices[1];
	_targetMesh->vertices[13] = _targetMesh->vertices[5];
	_targetMesh->vertices[14] = _targetMesh->vertices[6];
	_targetMesh->vertices[15] = _targetMesh->vertices[2];

	//top face
	_targetMesh->vertices[16] = _targetMesh->vertices[0];
	_targetMesh->vertices[17] = _targetMesh->vertices[4];
	_targetMesh->vertices[18] = _targetMesh->vertices[5];
	_targetMesh->vertices[19] = _targetMesh->vertices[1];

	//bottom face
	_targetMesh->vertices[20] = _targetMesh->vertices[3];
	_targetMesh->vertices[21] = _targetMesh->vertices[7];
	_targetMesh->vertices[22] = _targetMesh->vertices[6];
	_targetMesh->vertices[23] = _targetMesh->vertices[2];

	_targetMesh->colors = new glm::dvec4[_targetMesh->numVertices];

	for (int i = 0; i < _targetMesh->numVertices; ++i) {
		_targetMesh->colors[i] = glm::dvec4(_color.r, _color.g, _color.b, 1.0);
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
	_targetMesh->type = GL_TRIANGLE_STRIP;
	_targetMesh->numVertices = 720 + 1;
	_targetMesh->colors = new glm::dvec4[_targetMesh->numVertices];

	_targetMesh->vertices = new glm::dvec3[_targetMesh->numVertices];

	for (int i = 0; i < _targetMesh->numVertices / 2 + 1; i += 2)
	{
		_targetMesh->vertices[i] = glm::vec3(0.0f, 0.0f, 0.0f);
		_targetMesh->colors[i] = _color;

		float angle = PI * 2 * ((float)i / (float)360);
		float s = sin(angle) * _radious;
		float c = cos(angle) * _radious;
		_targetMesh->vertices[i + 1] = glm::vec3(c, s, 0.f) + (glm::vec3(0.0f, 0.0f, 1.0f) * _height);
				
		_targetMesh->colors[i + 1] = _color;
	}

	return _targetMesh;
}
