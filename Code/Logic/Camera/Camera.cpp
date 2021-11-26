#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#ifdef _DEBUG
#include "..\..\EngineCore\checkML.h"
#endif // _DEBUG
void Camera::setAZ() 
{
  eye= glm::dvec3(0, 0, 500);
  look= glm::dvec3(0, 0, 0);
  up= glm::dvec3(0, 1, 0);


  front = -normalize(eye - look);
  right = normalize(cross(up, -front));

  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
  eye= glm::dvec3(1000, 1000, 1000);
  look= glm::dvec3(0, 0, 0);
  up= glm::dvec3(0, 1000, 0);

  front = -normalize(eye - look);
  right = normalize(cross(up, -front));
  up = cross(-front, right);

  //Actualizamos el pitch y yaw
  pitchMov = glm::degrees(asin(front.y));
  GLdouble tmp = front.x / cos(glm::radians(pitchMov));
  yawMov = glm::degrees(asin(tmp));

  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
  rotatePY(a, 0);
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
  rotatePY(0, a);
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}
//-------------------------------------------------------------------------

void Camera::SetSize(GLdouble aw, GLdouble ah)
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{

	//Para cambiar entre orto y pers
	if (orto) {
		glMatrixMode(GL_PROJECTION);
		projMat = glm::ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
	else {
		nearVal = yTop;
		glMatrixMode(GL_PROJECTION);
		projMat = glm::frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
}
//-------------------------------------------------------------------------


Camera::Camera(GLint _x, GLint _y, GLsizei _cameraWidth, GLsizei _cameraHeight) : Viewport(_cameraWidth, _cameraHeight), viewMat(1.0), projMat(1.0),
xRight(getW() / 2.0), xLeft(-xRight), yTop(getH() / 2.0), yBot(-yTop)
{
	SetSize(_cameraWidth, _cameraHeight);
}

void Camera::moveFB(GLdouble cs) {

	eye = eye + (front * cs);

	viewMat = lookAt(eye, eye + front, up);
	
}

void Camera::moveUD(GLdouble cs) {

	eye = eye + (up * cs);

	viewMat = lookAt(eye, eye + front, up);

}

void Camera::moveLR(GLdouble cs) {
	eye = eye + (right * cs);

	viewMat = lookAt(eye, eye + front, up);
	
}

void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw) {

	pitchMov += incrPitch; yawMov += incrYaw; // Actualizar los ángulos
	if (pitchMov > 89.5) pitchMov = 89.5; // Limitar los ángulos

	else if (yawMov > 360) yawMov = 360; // Limitar angulo

		// Actualizar la dirección de vista
	front.x = sin(glm::radians(yawMov)) * cos(glm::radians(pitchMov));
	front.y = sin(glm::radians(pitchMov));
	front.z = -cos(glm::radians(yawMov)) * cos(glm::radians(pitchMov));
	front = glm::normalize(front);

	right = normalize(cross(up, -front));
	right = glm::normalize(right);

	viewMat = lookAt(eye, eye + front, up);
}
