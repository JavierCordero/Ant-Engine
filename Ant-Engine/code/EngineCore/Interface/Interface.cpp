#include "Interface.h"
#include <gl/GL.h>
#include "../Texture/Texture.h"
#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

Interface::Interface(const char* _spriteImageName, float _width, float _height, float _x, float _y) 
	: Sprite(_spriteImageName, _width, _height, _x, _y, 0.f)
{
}

Interface::Interface(Texture _texture, float _width, float _height, float _x, float _y)
	: Sprite(_texture, _width, _height, _x, _y, 0.f)
{
}

void Interface::Render(glm::dmat4 const& modelViewMat)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture.GetTextureID());

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(GetX(), GetY(), 0);
	glTexCoord2f(0, 1); glVertex3f(GetX(), GetY() + GetHeight(), 0);
	glTexCoord2f(1, 1); glVertex3f(GetX() + GetWidth(), GetY() + GetHeight(), 0);
	glTexCoord2f(1, 0); glVertex3f(GetX() + GetWidth(), GetY(), 0);
	glEnd();

	//glDisable(GL_TEXTURE_2D);
}