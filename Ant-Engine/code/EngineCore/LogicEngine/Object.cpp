#include "Object.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

void Object::SetModelViewMat(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat * m_ModelMat));
}

void Object::Update(double elapsedTime) {
	SetPrevPosition(GetPosition());
	SetPosition(GetPosition() + m_ObjectSpeed);
	
}

void Object::PostUpdate(double elapsedTime) {
	//SetPosition(GetPrevPosition());
}