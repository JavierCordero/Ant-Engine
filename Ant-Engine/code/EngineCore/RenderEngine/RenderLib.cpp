#include "RenderLib.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#include <freeglut.h>
#include <SDL.h>
#include <SDL_image.h>
#include "TextRenderer.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

int RenderLib::window = 0;
const char* RenderLib::WINDOW_NAME = "Sacred project";

bool RenderLib::Init(int argc, char* argv[])
{
	std::cout << "	|-Initializing Render lib..." << '\n';

	// Initialization
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);   // window size

	glutInitWindowPosition(GLUT_SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL  

	window = glutCreateWindow(WINDOW_NAME);  // window's identifier

	std::cout << "		|---- Software Version: " << glGetString(GL_VERSION) << '\n';
	std::cout << "		|---- Vendor: " << glGetString(GL_VENDOR) << '\n';

	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE); // normalización de vectores
	glEnable(GL_CULL_FACE); //Para optimizar el renderizado de las nuevas entidades
	
	std::cout << "		|---- Initializing SDL2\n";
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);

	std::cout << "		|---- Initializing and loading Fonts\n";
	TextRenderer::InitTextRenderer();

	return true;
}

void RenderLib::Destroy()
{
	glutDestroyWindow(window);  // Destroy the context 
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	IMG_Quit();
}

void RenderLib::Display(Scene* _renderScene)   // double buffer
{
	//3D Render
	Prepare3DDraw();

	if (_renderScene != nullptr)
	{
		_renderScene->Render();
	}

	for (int i = 0; i < LogicLib::text3D.size(); ++i) {
		Draw3DText(LogicLib::text3D[i].position, LogicLib::text3D[i].color, LogicLib::text3D[i].text);
	}

	LogicLib::text3D.clear();
	

	//Interface render
	PrepareInterfaceDraw();

	if (_renderScene != nullptr)
	{
		_renderScene->RenderInterface();
	}

	Restore3DDraw();

	glutSwapBuffers();
}

void RenderLib::Draw3DText(glm::vec3 _position, glm::vec3 _color, std::string _text)
{	
	glColor3f(_color.x, _color.y, _color.z);
	glRasterPos3f(_position.x, _position.y, _position.z);

	int j = _text.size();
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, _text[i]);
	}
}

void RenderLib::Draw2DText()
{
	/*glFontBegin(&font);
	glScalef(8.0, 8.0, 8.0);
	glTranslatef(30, 30, 0);
	glFontTextOut("Test", 5, 5, 0);
	glFontEnd();
	glFlush();*/
}

void RenderLib::Prepare3DDraw()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderLib::Restore3DDraw()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void RenderLib::PrepareInterfaceDraw()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glClear(GL_DEPTH_BUFFER_BIT);
}