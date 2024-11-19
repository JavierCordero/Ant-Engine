#pragma once
#include <chrono>
#include "LogicEngine\Scene.h"

static class EngineCore
{

public:
	static void InitEngine(int argc, char * argv[]);
	static void StartEngine(Scene* _scene);
	static void StopEngine();

	static void ExitApplication();

	inline static Scene* GetScene() { return m_CurrentScene; }
	
	static char* GetResourceFolder() { return m_ResourceFolder; };

	static double GetFPS() { return m_FramesPerSecond; };

	static double GetElapsedTime() { return m_FrameElapsedTime; };

	static std::chrono::steady_clock::time_point m_FrameStartTime, m_FrameEndTime;
	static double m_FrameElapsedTime;
	static float m_FramesPerSecond;
	static int m_MaxFrameRate;

private:
	static Scene* m_CurrentScene;

	static char m_ResourceFolder[MAX_PATH];

};

