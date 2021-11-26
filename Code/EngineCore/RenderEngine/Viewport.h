#pragma once
#include <glm.hpp>
#include <GL/freeglut.h>

class Viewport {
public:
	Viewport(GLsizei _width, GLsizei _height);
	virtual ~Viewport() { };

	void SetSize(GLsizei _width, GLsizei _height);
	void Move(int _x, int _y);

	GLsizei getX() { return x; };
	GLsizei getY() { return y; };
	GLsizei getW() { return width; };
	GLsizei getH() { return height; };

protected:
	GLint x = 0, y = 0;
	GLsizei width, height;
	void set();

};