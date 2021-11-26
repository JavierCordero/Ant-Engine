#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/constants.hpp>
#include <gtc/type_ptr.hpp>

class Light
{
public:
	Light();
	~Light();
	virtual void load() {
		glMatrixMode(GL_MODELVIEW);
		//glLoadMatrixd(value_ptr(modelViewMat));
		glLightfv(id, GL_POSITION, value_ptr(posDir));
		glLightfv(id, GL_AMBIENT, value_ptr(ambient));
		glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(id, GL_SPECULAR, value_ptr(specular));
	};
	void setAmb(glm::fvec4 amb);
	void setPos(glm::fvec3 pos) { posDir = glm::fvec4(pos, 1.0); };
	void setDir(glm::fvec3 dir) { posDir = glm::fvec4(dir, 0.0); }; // -dir ?
	
private:
	glm::dmat4 const& modelViewMat;
	glm::fvec4 posDir = { 0, 0, 1, 0 }; // w=0 -> vector
	GLuint id = GL_MAX_LIGHTS; // GL_LIGHTi
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
};

