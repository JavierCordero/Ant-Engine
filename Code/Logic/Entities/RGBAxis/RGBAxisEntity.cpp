#include "RGBAxisEntity.h"
#include "RGBaxis.h"
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
RGBAxisEntity::RGBAxisEntity(glm::vec3 _position, double _Size) : Entity(_position, glm::vec3(_Size, _Size, _Size))
{
	rgbMesh = new RGBaxis(_Size, this);
}

void RGBAxisEntity::Render(glm::dmat4 const& modelViewMat)
{
	Entity::Render(modelViewMat);
	rgbMesh->Render(modelViewMat);
}
