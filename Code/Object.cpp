#include "Object.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
void Object::SetModelViewMat(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat * modelMat));
}

void Object::Update(double elapsedTime) {
	SetPrevPosition(GetPosition());
	SetPosition(GetPosition() + speed);
	
}

void Object::PostUpdate(double elapsedTime) {
	//SetPosition(GetPrevPosition());
}