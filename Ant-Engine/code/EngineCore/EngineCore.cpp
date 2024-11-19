#include "EngineCore.h"

#include "RenderEngine/RenderLib.h"
#include "LogicEngine/LogicEngine.h"
#include "InputEngine/InputLib.h"
#include "PhysicEngine/PhysicLib.h"
#include "OnlineEngine/OnlineLib.h"
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

double EngineCore::m_FrameElapsedTime = 0.0;
std::chrono::steady_clock::time_point EngineCore::m_FrameStartTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point EngineCore::m_FrameEndTime = std::chrono::steady_clock::now();
float EngineCore::m_FramesPerSecond = 0.0;

Scene* EngineCore::m_CurrentScene = nullptr;
char EngineCore::m_ResourceFolder[MAX_PATH] = "\0";

int EngineCore::m_MaxFrameRate = 60;

glm::dvec2 mCoord;

void EngineCore::InitEngine(int argc, char* argv[])
{

	srand(time(NULL));
	
	strcpy_s(m_ResourceFolder, "resources\\");

	RenderLib::Init(argc, argv);
	LogicLib::Init();
	InputLib::Init();
	PhysicLib::Init();
	OnlineLib::Init();

	std::cout << "---- All core libs initialized successfully ----" << '\n';
	
	glutDisplayFunc(Render);
	glutIdleFunc(MainLoop);
	glutKeyboardFunc(HandleInput);

	//glutReshapeFunc(Resize);
	
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
}

void EngineCore::StartEngine(Scene* _scene) {
	m_CurrentScene = _scene;
	m_CurrentScene->Init();
	glutMainLoop();
}

void EngineCore::StopEngine() {

	PhysicLib::Destroy();

	if (m_CurrentScene != nullptr) {
		delete m_CurrentScene;
		m_CurrentScene = nullptr;
	}
}

void HandleInput(unsigned char _key, int _x, int _y) {
	InputLib::HandleInput(_key, _x, _y);
}

void MainLoop() {

	//startTime = glutGet(GLUT_ELAPSED_TIME); //Eso da el elapsedTime del renderizado, no del todal
	EngineCore::m_FrameStartTime = std::chrono::steady_clock::now();

	//HandleInput(); //Se encarga FreeGLUT del input <3
	LogicLib::Update(EngineCore::GetElapsedTime());
	LogicLib::PostUpdate(EngineCore::GetElapsedTime());
	Render();

	EngineCore::m_FrameEndTime = std::chrono::steady_clock::now();
	EngineCore::m_FrameElapsedTime = (std::chrono::duration_cast<std::chrono::milliseconds>(EngineCore::m_FrameEndTime - EngineCore::m_FrameStartTime).count()) / 1000.0;

	if (EngineCore::m_FrameElapsedTime < 1.f / EngineCore::m_MaxFrameRate)
	{
		double time = (1.f / EngineCore::m_MaxFrameRate) - EngineCore::m_FrameElapsedTime;
		Sleep(time * 1000);
		EngineCore::m_FrameElapsedTime += time;
	}

	if (EngineCore::GetElapsedTime() != 0) {
		EngineCore::m_FramesPerSecond = 1 / EngineCore::GetElapsedTime();
	}

	Text3D text; 
	text.position = glm::vec3(540.0f, 450.0f, 0.0f); 
	text.color = glm::vec3(0.0f, 0.0f, 0.0f); 
	text.text = "FPS: " + std::to_string(EngineCore::GetFPS()) + "(" + std::to_string(EngineCore::GetElapsedTime()) + "ms)";
	LogicLib::text3D.push_back(text);
}

void Render() 
{
	CustomRender(EngineCore::GetScene());
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


void Resize(int _newWidth, int _newHeight)
{
//	//// Resize Viewport 
//	//logicLib->GetCurrentViewport()->setSize(_newWidth, _newHeight);
//	//// Resize Scene Visible Area 
//	//logicLib->GetCurrentCamera()->setSize(logicLib->GetCurrentViewport()->getW(), logicLib->GetCurrentViewport()->getH());    // scale unchanged
}