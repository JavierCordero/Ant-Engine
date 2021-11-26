#include "EngineCore.h"

#include "RenderLib.h"
#include "LogicLib.h"
#include "InputLib.h"
#include "PhysicLib.h"
#include <time.h>
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
#include <iostream>
#include <string>

void MainLoop();
void Render();
void CustomRender(Scene* _sceneToDisplay);
void HandleInput(unsigned char _key, int _x, int _y);

void Resize(int _newWidth, int _newHeight);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);

double EngineCore::elapsedTime = 0.0;
std::chrono::steady_clock::time_point EngineCore::startTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point EngineCore::endTime = std::chrono::steady_clock::now();
float EngineCore::fps = 0.0;

Scene* EngineCore::scene = nullptr;

glm::dvec2 mCoord;

void EngineCore::InitEngine(int argc, char* argv[])
{

	srand(time(NULL));

	RenderLib::Init(argc, argv);
	LogicLib::Init();
	InputLib::Init();
	PhysicLib::Init();

	std::cout << "All core libs initialized successfully!" << '\n';

	glutDisplayFunc(Render);
	glutIdleFunc(MainLoop);
	glutKeyboardFunc(HandleInput);

	//glutReshapeFunc(Resize);
	
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
}

void EngineCore::StartEngine(Scene* _scene) {
	scene = _scene;
	scene->Init();
	glutMainLoop();
}

void EngineCore::StopEngine() {

	PhysicLib::Destroy();

	if (scene != nullptr) {
		delete scene;
		scene = nullptr;
	}
}

void HandleInput(unsigned char _key, int _x, int _y) {
	InputLib::HandleInput(_key, _x, _y);
}

void MainLoop() {

	//startTime = glutGet(GLUT_ELAPSED_TIME); //Eso da el elapsedTime del renderizado, no del todal
	EngineCore::startTime = std::chrono::steady_clock::now();

	//HandleInput(); //Se encarga FreeGLUT del input <3
	LogicLib::Update(EngineCore::elapsedTime);
	LogicLib::PostUpdate(EngineCore::elapsedTime);
	Render();

	EngineCore::endTime = std::chrono::steady_clock::now();
	EngineCore::elapsedTime = (std::chrono::duration_cast<std::chrono::milliseconds>(EngineCore::endTime - EngineCore::startTime).count()) / 1000.0;

	if (EngineCore::elapsedTime != 0) {
		EngineCore::fps = 1 / EngineCore::elapsedTime;
	}

	Text3D text; text.position = glm::vec3(540.0f, 450.0f, 0.0f); text.color = glm::vec3(0.0f, 0.0f, 0.0f); text.text = "FPS: " + std::to_string(EngineCore::fps) + "(" + std::to_string(EngineCore::elapsedTime) + "ms)";
	LogicLib::text3D.push_back(text);

}

void Render() {
	Scene* scene = EngineCore::GetScene();
	if (scene) {
		CustomRender(EngineCore::GetScene());
	}
}

void CustomRender(Scene* _sceneToDisplay) {
	RenderLib::Display(_sceneToDisplay);
}

void EngineCore::ExitApplication() {

	RenderLib::Destroy();

	glutLeaveMainLoop();
}

//------------------------------------------------------

void motion(int x, int y) { //Movimiento del ratón

	glm::dvec2 mOffset = mCoord; // var. global
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	mOffset = (mCoord - mOffset) * 0.1; // sensitivity = 0.05
	EngineCore::GetScene()->GetCamera()->rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();

}

void mouse(int button, int state, int x, int y) { //coordenadas del ratón

	mCoord.x = x;
	mCoord.y = glutGet(GLUT_WINDOW_HEIGHT) - y;
}


//void Resize(int _newWidth, int _newHeight)
//{
//	//// Resize Viewport 
//	//logicLib->GetCurrentViewport()->setSize(_newWidth, _newHeight);
//	//// Resize Scene Visible Area 
//	//logicLib->GetCurrentCamera()->setSize(logicLib->GetCurrentViewport()->getW(), logicLib->GetCurrentViewport()->getH());    // scale unchanged
//}