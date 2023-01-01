#pragma once
#include <freeglut.h>
#include <glm.hpp>
#include <gtc/constants.hpp>
class Material
{
public:
	Material();
	virtual ~Material();
	
	virtual void Load();
	
private:
	glm::fvec4 ambient, diffuse, specular; // coeficientes de reflexión
	GLfloat expF; // exponente especular
	GLuint face = GL_FRONT_AND_BACK; // ambos lados
	GLuint sh = GL_SMOOTH; // smooth shading
	
};
