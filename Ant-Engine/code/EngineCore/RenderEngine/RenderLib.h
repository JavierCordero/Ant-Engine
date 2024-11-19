#pragma once
#include "..\LogicEngine\Scene.h"
#include "..\EngineCore.h"
#include "..\LogicEngine\LogicEngine.h"
#include <string>

static class RenderLib
{
	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;
	static const char*  WINDOW_NAME;


public:
	
	static bool Init(int argc, char* argv[]);
	static void Destroy();
	static void Display(Scene* _renderScene);

	static void Draw3DText(glm::vec3 _position,	glm::vec3 _color, std::string _text);
	static void Draw2DText();

	static inline int GetWindowWidth() { return WINDOW_WIDTH; };
	static inline int GetWindowHeight() { return WINDOW_HEIGHT; };

private:

	static void PrepareInterfaceDraw();
	static void Prepare3DDraw();
	static void Restore3DDraw();
	
	static int window;
};

