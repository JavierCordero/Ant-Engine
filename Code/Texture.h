#pragma once
#include "Pixmap32RGBA.h"
#include <GL/freeglut.h>
#include <glm.hpp>

class Texture
{
public:
	Texture() : w(0), h(0), id(0) {};
	virtual ~Texture() { if (id != 0) glDeleteTextures(1, &id); };
	bool load(const std::string & BMP_Name, GLubyte alpha = 255);
	bool load(const std::string & BMP_Name, glm::ivec3 color, GLubyte alpha);
	// cargar y transferir a openGL
	void bind();
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
	void save(const std::string & BMP_Name);
	void loadColorBuffer(GLsizei width, GLsizei height);
	void wrap(GLuint wp = GL_CLAMP); //Por defecto lo creamos Clamp y no repeat

protected:
	GLuint w, h; // dimensiones de la imagen
	GLuint id; // identificador interno (GPU) de la textura
	void init();
};

