#pragma once
#include "Entity.h"
#include "Mesh.h"

class RGBaxis : public Mesh
{
public:
	RGBaxis(GLdouble _size, Object* _objectReference);
	virtual ~RGBaxis();

	void Render(glm::dmat4 const& modelViewMat);
private:
	Mesh* CreateAxis(GLdouble _size);
};

