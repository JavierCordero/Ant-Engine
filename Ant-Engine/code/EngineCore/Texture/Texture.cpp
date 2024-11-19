#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "../EngineCore.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

Texture::Texture()
{
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID); // activa la textura
									  // la función de mezcla de colores no queda guardada en el objeto
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// GL_MODULATE / GL_ADD …
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Init()
{
	glGenTextures(1, &m_TextureID); // genera un identificador para una nueva textura
	glBindTexture(GL_TEXTURE_2D, m_TextureID); // Filters and clamping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::Load(const char* _newTextureName)
{
	Init();

	strcpy_s(m_TextureFolder, EngineCore::GetResourceFolder());
	strcat_s(m_TextureFolder, "textures\\");

	strcpy_s(m_TextureFilename, _newTextureName);

	char filename[MAX_PATH];
	strcpy_s(filename, m_TextureFolder);
	strcat_s(filename, m_TextureFilename);

	GLuint texture;
	SDL_Surface* surface;
	surface = IMG_Load(filename);


	if (!surface)
	{
		std::cout << "Unable to load image " << m_TextureFilename << " from route: " << filename << "\n";
		return;
	}

	CreateFromSurface(surface);
	SDL_FreeSurface(surface);
}

void Texture::CreateFromSurface(SDL_Surface* _surface)
{
	GLint nColors;
	GLenum textureFormat = GL_RGB;

	//get number of channels in the SDL surface
	nColors = _surface->format->BytesPerPixel;

	//contains an alpha channel
	if (nColors == 4)
	{
		if (_surface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGBA;
	}
	else if (nColors == 3) //no alpha channel
	{
		if (_surface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGB;
	}
	else
	{
		std::cout << "Error en el formato de la imagen.\n ";
		return;
	}

	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, _surface->w, _surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, _surface->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}