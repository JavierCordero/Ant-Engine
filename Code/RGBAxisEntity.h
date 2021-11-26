#pragma once
#include "Entity.h"
#include "Mesh.h"


class RGBAxisEntity : public Entity
{
public:
	RGBAxisEntity(glm::vec3 _position, double _Size) ;
	virtual ~RGBAxisEntity() { delete rgbMesh; rgbMesh = nullptr; };

	void Render(glm::dmat4 const& modelViewMat);

private:
	Mesh* rgbMesh = nullptr;
};

