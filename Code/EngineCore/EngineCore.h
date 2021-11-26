#pragma once
#include <chrono>
#include "..\Logic\Scenes\Scene.h"

static class EngineCore
{

public:
	static void InitEngine(int argc, char * argv[]);
	static void StartEngine(Scene* _scene);
	static void StopEngine();

	static void ExitApplication();

	inline static Scene* GetScene() { return scene; }

	static std::chrono::steady_clock::time_point startTime, endTime;
	static double elapsedTime;
	static float fps;



private:
	static Scene* scene;
};

