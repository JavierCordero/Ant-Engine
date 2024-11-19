#pragma once
#include "../../EngineCore/LogicEngine/Scene.h"
#include <thread>

class Sudoku;

class SacredWorldScene : public Scene
{
public:
	SacredWorldScene::SacredWorldScene();

	virtual void Update(float _elapsedTime);
	virtual void HandleInput(unsigned char _key);

private:
	Sudoku* m_Sudoku;

	int m_intensity = 0;

	float m_currentTime = 0.f;
};

