#pragma once
#include "Entity.h"
#include "Primitives.h"

class Cone : public Mesh
{
public:
	Cone(double _baseRadious, float _height, Object* _objectReference);
	Cone(double _baseRadious, float _height, glm::vec4 _color, Object* _objectReference);
	virtual ~Cone() {}

	void Render(glm::dmat4 const& modelViewMat);
	void UpdateConePosition(glm::dvec3 _newPosition);

	Mesh* CreateCone(double _baseRadious, float _height, Object* _objectReference, glm::vec4 _color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
};

