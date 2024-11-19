#pragma once
#include <vector>
#include <freeglut.h>
#include <ft2build.h>
#include <string>
#include <glm.hpp>
#include <map>

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/GL.h>

#include FT_FREETYPE_H  
class Texture;
class SDL_Color;

static class TextRenderer
{
public:

	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};


	static void RenderText(const char* _message);

	static bool InitTextRenderer();
	static void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
	static void GetALlFilesInFolderWithExtension(const char* _root, const char* _ext, std::vector<std::string>& _outVector_);
	static void StoreCharacters(FT_Face _face);
	static void LoadFont(const char* _fontPath);

	static std::map<char, Character> Characters;
	
	static char m_TextureFolder[MAX_PATH];

	static Texture FontTexture;
	static TTF_Font* m_FontPointer;
};

