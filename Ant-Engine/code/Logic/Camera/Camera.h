//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "..\..\EngineCore\RenderEngine\Viewport.h"

class Camera : public Viewport {
public:
  Camera(GLint _x, GLint _y, GLsizei _cameraWidth, GLsizei _cameraHeight);
  virtual ~Camera() {};

  GLint speed = 1;
  // view matrix
  glm::dmat4 const& getViewMat() { return viewMat; };

  void moveFB(GLdouble cs);
  void moveLR(GLdouble cs);
  void moveUD(GLdouble cs);

  void Set2D();  // lookAt(eye(0,0,500), look(0,0,0) up(0, 1, 0))
  void set3D();  // lookAt(eye(500,500,500), look(0,10,0) up(0, 1, 0))
    
  void pitch(GLdouble a); // rotates a degrees on the X axis
  void yaw(GLdouble a);   // rotates a degrees on the Y axis
  void roll(GLdouble a);  // rotates a degrees on the Z axis 

  // projection matrix
  glm::dmat4 const& getProjMat() { return projMat; };

  void SetSize(GLdouble aw, GLdouble ah);
  void scale(GLdouble s); 
 
  void rotatePY(GLdouble incrPitch, GLdouble incrYaw); // Para mover la cámara

  void  setPrj() { orto = !orto; setPM(); };

  glm::dvec3 eye = { 0.0, 0.0, 200 };
  glm::dvec3 look = { 0.0, 0.0, 0.0 };
  glm::dvec3 up = { 0.0, 1.0, 0.0 };
  glm::dmat4 viewMat;  // inverse


  glm::dvec3 front;
  glm::dvec3 right;

  GLdouble xRight, xLeft, yTop, yBot;
  GLdouble nearVal = 0.001;
  GLdouble farVal = 10000;
  GLdouble factScale = 1.53;
  glm::dmat4 projMat;

  void setVM();
  void setPM();  

  bool orto = true;

private:
	GLdouble pitchMov, yawMov;	
};

//-------------------------------------------------------------------------

#endif //_H_Camera_H_