#include "RenderLib.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

int RenderLib::window = 0;
const char* RenderLib::WINDOW_NAME = "Ant project";

bool RenderLib::Init(int argc, char* argv[])
{
	std::cout << "Initializing Render lib..." << '\n';

	// Initialization
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);   // window size

	glutInitWindowPosition(GLUT_SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL  

	window = glutCreateWindow(WINDOW_NAME);  // window's identifier

	std::cout << glGetString(GL_VERSION) << '\n';
	std::cout << glGetString(GL_VENDOR) << '\n';

	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	//glEnable(GL_LIGHTING); //Activa la iluminación de OpenGL
	glEnable(GL_NORMALIZE); // normalización de vectores
	glEnable(GL_CULL_FACE); //Para optimizar el renderizado de las nuevas entidades
	glEnable(GL_TEXTURE_2D);
	
	return true;
}

void RenderLib::Destroy()
{
	glutDestroyWindow(window);  // Destroy the context 
}

void RenderLib::Display(Scene* _renderScene)   // double buffer
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera* camera = _renderScene->GetCamera();

	if (camera != nullptr) {

		for each (Entity * it in _renderScene->sceneObjects)
		{
			it->Render(camera->getViewMat());
		}
	}

	//Text3D text = LogicLib::text3D.begin();

	for (int i = 0; i < LogicLib::text3D.size(); ++i) {
		Draw3DText(LogicLib::text3D[i].position, LogicLib::text3D[i].color, LogicLib::text3D[i].text);
	}

	LogicLib::text3D.clear();

	glutSwapBuffers();
}

void RenderLib::Draw3DText(glm::vec3 _position, glm::vec3 _color, std::string _text) {
	glColor3f(_color.x, _color.y, _color.z);
	glRasterPos3f(_position.x, _position.y, _position.z);

	int j = _text.size();
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, _text[i]);
	}
}
