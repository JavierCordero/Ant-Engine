#include "Viewport.h"
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
Viewport::Viewport(GLsizei _width, GLsizei _height) : width(_width), height(_height)
{
	SetSize(width, height);
}

void Viewport::SetSize(GLsizei aw, GLsizei ah)
{
	width = aw;
	height = ah;

	set();
}
//-------------------------------------------------------------------------

void Viewport::set()
{
	glViewport(x, y, width, height);
}

void Viewport::Move(int _x, int _y) {
    x = _x; y = _y;
    set();
}