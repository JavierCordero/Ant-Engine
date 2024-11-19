#pragma once
#include <freeglut.h>
#include <glm.hpp>
#include <ostream>

class SDL_Surface;

class Texture
{
public:
	Texture();
	inline virtual ~Texture() { if (m_TextureID != 0) glDeleteTextures(1, &m_TextureID); };
	
	void Load(const char* _newTextureName);
	void Init();
	void Bind();
	void Unbind();

	GLuint GetTextureID() { return m_TextureID; };
	void CreateFromSurface(SDL_Surface* _surface);

protected:
	GLuint m_TextureID; // identificador interno (GPU) de la textura

private:

	char m_TextureFolder[MAX_PATH];
	char m_TextureFilename[64];
};

